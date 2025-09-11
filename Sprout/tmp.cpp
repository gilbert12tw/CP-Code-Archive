#include<bits/stdc++.h>
using namespace std;

int A_MX = 100;

void printA(int a) {
    cout << a << '\n';
    a = 123;
}

int main() {
    int a = 10;
    cout << a << '\n';
    printA(-1);
}
