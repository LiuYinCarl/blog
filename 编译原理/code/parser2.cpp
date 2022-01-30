#include <cassert>
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>

using namespace std;


bool isDigit(char c) {
  return (c >= '0' && c <= '9');
}

bool isLetter(char c) {
  return (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z');
}


enum Tag {
  NUM = 256,
  ID = 257,
  TRUE = 258,
  FALSE = 259,
};


class Token;
class Num;


class Token {
public:
  int tag;

public:
  Token(int t) {
    tag = t;
  }
};


class Num : public Token {
public:
  int value;

public:
  Num(int v) : Token(NUM) {
    value = v;
  }
};


// 用于保留字和标志符
class Word : public Token {
public:
  string lexme;

public:
  Word(Tag t, string s) : Token(t) {
    lexme = s;
  }

  Word(const Word& w) : Token(w.tag) {
    lexme = w.lexme;
  }

  Word& operator=(const Word& w) {
    lexme = w.lexme;
    tag = w.tag;
    return *this;
  }
};


class Lexer {
public:
  int line = 1;

private:
  char peek = ' ';
  map<string, Word> words;

public:
  void reserve(Word t) {
    words.insert({t.lexme, t});
  }

  Lexer() {
    reserve(Word(TRUE, "true"));
    reserve(Word(FALSE, "false"));
  }

  Token scan() {
    for (; ; peek = getchar()) {
      if (peek == ' ' || peek == '\t') {
	continue;
      } else if (peek == '\n') {
	line = line + 1;
      } else {
	break;
      }
    }

    if (isDigit(peek)) {
      int v = 0;
      do {
	v = 10 * v + (peek - '0');
	peek = getchar();
      } while (isDigit(peek));

      return Num(v);
    }

    if (isLetter(peek)) {
      string buff;
      do {
	buff += peek;
	peek = getchar();
      } while (isLetter(peek) || isDigit(peek));

      string s = buff;
      auto iter = words.find(s);
      if (iter != words.end()) {
	return iter->second;
      } else {
	Word w = Word(ID, s);
	words.insert({s, w});
	return w;
      }
    }
    Token t = Token(peek);
    peek = ' ';
    return t;
  }


  void printWords() {
    cout << "------------------------" << endl;
    for (auto word : words) {
      cout << word.second.lexme << " " << word.second.tag << endl;
    }
    cout << "-------------------------" << endl;
  }
  
};


class Env {
private:
  map<string, Symbol*> table;

protected:
  Env* prev;

public:
  void put(string s, Symbol* sym) {
    table.insert({s, sym});
  }

  Symbol* get(string s) {
    for (Env* e = this; e != null; e = e->prev) {
      auto iter = e->table.find(s);
      if (iter != e->table.end()) {
	return iter.second;
      }
    }
    return nullptr;
  }
};



int main() {
  freopen("./code.txt", "r", stdin);
  
  Lexer lex;
  while (true) {
    lex.printWords();
    Token t = lex.scan();
    if (t.tag == '\n' || t.tag == ' ')
      break;
  }

}
