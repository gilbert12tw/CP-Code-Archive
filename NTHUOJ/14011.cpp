#include<bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

class Linked_list {
private:
  static const int mxL = 2e6 + 5;
  int tot_id, cursor;
  class Node {
  public:
    char c;
    int nxt, prv;
    Node(): nxt(0), prv(0) {}
  } list[mxL];

  inline int new_node(char c) {
    list[++tot_id].c = c;
    return tot_id;
  }

public:
  Linked_list(): tot_id(0), cursor(0) {}

  inline void add_char(char c) {
    int node_id = new_node(c);
    list[node_id].nxt = list[cursor].nxt;
    list[node_id].prv = cursor;
    list[list[cursor].nxt].prv = node_id;
    list[cursor].nxt = node_id;
    cursor = node_id;
  }

  inline void backspace() {
    if (cursor == 0) return;
    list[list[cursor].prv].nxt = list[cursor].nxt;
    list[list[cursor].nxt].prv = list[cursor].prv;
    cursor = list[cursor].prv;
  }

  inline void move(int n) {
    if (n > 0) {
      while (list[cursor].nxt && n > 0) {
        n--;
        cursor = list[cursor].nxt;
      }
    } else if (n < 0) {
      n = -n;
      while (cursor && n > 0) {
        n--;
        cursor = list[cursor].prv;
      }
    }
  }

  inline void print() {
    int hd = list[0].nxt;
    while (hd != 0) {
      cout << list[hd].c;
      hd = list[hd].nxt;
    }
    cout << '\n';
  }
};

inline void solve() {
  string opr;
  Linked_list llist;
  while (cin >> opr) {
    string input;
    int n;
    if (opr == "Type") {
      cin >> input;
      for (char c : input) llist.add_char(c);
    } else if (opr == "Move") {
      cin >> n;
      llist.move(n);
    } else if (opr == "Backspace") {
      llist.backspace();
    } else { // Print
      llist.print();
    }
  } 
}

signed main() {
	IO;	
	solve();	
}
