#include<bits/stdc++.h>
using namespace std;

int cnt[6] = {};

int main () {
    for (int i = 0;i < 4; ++i) {
        int x;
        cin >> x;
        cnt[x] = 1;
    }
    for (int i = 1;i <= 5; ++i) {
        if (cnt[i] == 0) {
            cout << i << "\n";
        }
    }
    return 0;
}
