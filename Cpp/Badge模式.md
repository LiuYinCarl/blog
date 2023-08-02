# Badge 模式

在看 folly 的代码时，看到了一个比较有意思的设计，叫做 Badge 模式，这个模式比较适合用在被管理类在管理类上进行自动注册和自动反注册。

## 介绍

Badge 模式是对 friend 类的一种抽象，可以更严格的控制类的访问权限。

举一个例子，在游戏中需要设计两个类，一个是 `class Player` 另一个是 `class PlayerMgr`，想要在 `class Player` 构造的时候将自身注册到 `class PlayerMgr`，在 `class Player` 析构的时候从 `class PlayerMgr` 中取消注册。

最简单的方案如下：

```c++
class Player {};

class PlayerMgr {
public:
    void register_player(Player&);
    void unregister_player(Player&);
};
```

然后，在构造出 `Player` 对象的地方调用 `register_player` 函数，在释放 `Player` 对象的地方调用
`unregister_player`。这种方案看起来很直观，但是存在一个严重的问题，那就是没办法保证对于一个 `Player` 对象，只会调用一次 `register_player` 和 `unregister_player`。在这个方案中，任何人只要
能拿到 `PlayerMgr` 对象和 `Player` 对象，就可以任意调用这两个函数。

为了解决上面的问题，提出方案二：

```c++
class Player {
public:
    Player() {
        player_mgr.register_player(*this);
    }
    ~Player() {
        player_mgr.unregister_player(*this);
    }
};

class PlayerMgr {
private:
    friend class Player;
    void register_player(Player&);
    void unregister_player(Player&);
};
```

这个方案将 `class Player` 变成 `class PlayerMgr` 的友元类。在 `class Player` 的构造函数中调用
`register_player`，在 `class Player` 的析构函数中调用 `unregister_player`。通过将 `register_player` 和 `unregister_player` 设置为 `private`，避免了其他地方随意调用注册和反注册函数的问题。但是，友元类的做法又给了 `class Player` 类对 `class PlayerMgr` 完全的访问权限，`class Player` 很可能会滥用这一访问权限。

为了解决友元类访问权限过高的问题，提出方案三：

```c++
template<typename T>
class Badge {
private:
    friend T;
    Badge() {};
};

class Player {
public:
    Player() {
        player_mgr.register_player(Badge(), *this);
    }
    ~Player() {
        player_mgr.unregister_player(Badge(), *this);
    }
};

class PlayerMgr {
public:
    void register_player(Badge<Player>, Player&);
    void unregister_player(Badge<Player>, Player&);
};
```

在这个方案中，增加了 `class Badge` 并且将它的构造函数设置为 `private`，这样子只有它的友元类 `class T` 才可以构造出一个 `Badge` 对象，在这个例子中，它的友元类就是 `class Player`。在
`class PlayerMgr` 中，`register_player` 和 `unregister_player` 增加了一个类型为 `Badge<Player>` 的参数，这就要求调用函数的时候提供一个 `class Badge` 的实例，这个例子中只有 `class Player` 才可以构造 `class Badge` 的实例。`class Badge` 实现为一个空类，是因为在这里并不需要它进行什么操作，只是利用它来禁止非 `Player` 对象调用 `register_player` 和 `unregister_player` 函数。

方案三最终实现了只有 `class Player` 才能调用 `register_player` 和 `unregister_player` 函数，并且 `class Player` 不能访问 `class PlayerMrg` 的非公有属性的需求。

下面是方案三的一个完整的小例子。

```c++
// main.h
template<typename T>
class Badge {
  friend T;
  Badge() {}
};

class Player {
 public:
  Player();
  ~Player();
};

class PlayerMgr {
 private:
  PlayerMgr() {}

 public:
  static PlayerMgr& getIns() {
    static PlayerMgr ins;
    return ins;
  };

  void register_player(Badge<Player>, Player&);
  void unregister_player(Badge<Player>, Player&);
};
```

```c++
// main.cpp
#include <iostream>
#include "main.h"

void PlayerMgr::register_player(Badge<Player> f, Player& player) {
  std::cout << "register player" << std::endl;
}

void PlayerMgr::unregister_player(Badge<Player> f, Player& player) {
  std::cout << "unregister player" << std::endl;
}

Player::Player()  {
  PlayerMgr::getIns().register_player(Badge<Player>(), *this);
}

Player::~Player() {
  PlayerMgr::getIns().unregister_player(Badge<Player>(), *this);
}

int main() {
  Player();
  Player();
}
```

编译执行

```bash
$ g++ main.cpp -std=c++98
$ ./a.out
register player
unregister player
register player
unregister player
```

## 参考资料

1. [Serenity C++ patterns: The Badge](https://awesomekling.github.io/Serenity-C++-patterns-The-Badge/)
2. [folly Badge.h](https://github.com/facebook/folly/blob/main/folly/lang/Badge.h)