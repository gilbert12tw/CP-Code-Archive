#include<bits/stdc++.h>
using namespace std;
#define IO ios_base::sync_with_stdio(0); cin.tie(0);

class Stack {
private:
    int tp = 0;
    int *stk;
public:
    Stack(int n) { tp = 0; stk = new int[n+1]{}; }
    ~Stack() { delete [] stk; }
    void push(int x) { stk[tp++] = x; }
    bool empty() { return tp == 0; }
    void clear() { tp = 0; }
    int pop() { 
        assert(!empty());
        return stk[tp--]; 
    }
    int top() { 
        assert(!empty());
        return stk[tp-1]; 
    }
};

signed main() {
    IO;	
    string s;
    int T; cin >> T;
    getline(cin, s);
    while (T--) {
        getline(cin, s);
        int n = s.size();
        bool *valid = new bool[n+1]{};
        for (int i = 0; i < n; i++) valid[i] = 0;
        Stack stk(n);
        for (int i = 0; i < n; i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                if (!stk.empty()) {
                    valid[stk.top()] = valid[i] = 1;
                    stk.pop();
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (valid[i]) {
                cout << s[i];
            } else {
                cout << "()";
            }
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            if (valid[i]) cout << s[i];
        }
        cout << '\n';
        delete [] valid;
    }
}
