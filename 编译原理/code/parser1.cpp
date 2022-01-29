// 将中缀表达式 1+2-3 翻译成后缀表达式 12+3-


#include <cassert>
#include <stdio.h>
#include <iostream>

using namespace std;

class Parser {
private:
  char lookahead;

public:
  
  Parser() {
    lookahead = getchar();
  }

  void expr() {
    term();
    while (true) {
      if (lookahead == '+') {
	match('+'); term(); cout << '+';
      } else if (lookahead == '-') {
	match('-'); term(); cout << '-';
      } else {
	return;
      }
    }
  }

  bool isDigit(char c) {
    return (c >= '0' && c <= '9');
  }

  void term() {
    if (isDigit(lookahead)) {
      cout << lookahead; match(lookahead);
    } else {
      assert(false);
    }
  }

  void match(char t) {
    if (lookahead == t) {
      lookahead = getchar();
    } else {
      assert(false);
    }
  }
  
};


int main() {
  Parser* parser = new Parser;
  parser->expr();
  cout << endl;
}
