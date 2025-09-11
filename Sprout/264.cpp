#include<iostream>
using namespace std;

int a[10000 + 5];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > 0) a[i] = 0;
    }

    for (int i = n - 1; i >= 0; i--) {
        cout << a[i] << '\n';
    }
}
