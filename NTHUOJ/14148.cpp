#include<bits/stdc++.h>
using namespace std;

int n, k;
int *a, *tmp;

// quick select
int qs(int l, int r, int k) {
    if (l == r) return a[l];
    int piviot = a[(l + r) >> 1];
    int pl = l, pr = r, cnt = 0, pid = -1;
    for (int i = l; i <= r; i++) {
        if (a[i] <= piviot) {
            cnt++;
            if (a[i] == piviot) pid = pl;
            tmp[pl++] = a[i];
        } else {
            tmp[pr--] = a[i];
        }
    }
    swap(tmp[pl-1], tmp[pid]);
    if (cnt == k) return piviot;
    memcpy(a + l, tmp + l, (r - l + 1) * 4);
    if (cnt > k) return qs(l, l + cnt - 1, k);
    return qs(l + cnt, r, k - cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> k;
    a = new int[n];
    tmp = new int[n];
    for (int i = 0; i < n; i++) cin >> a[i];
    k = n - k + 1;
    cout << qs(0, n - 1, k) << '\n';
}

