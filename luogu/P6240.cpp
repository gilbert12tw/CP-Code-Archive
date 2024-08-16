#include<bits/stdc++.h>
//#define loli
using namespace std;
typedef long long ll;
#define pii pair<int, int>
#define X first
#define Y second
#define F first
#define S second
#define SZ(a) ((int)a.size())
#define ALL(v) v.begin(), v.end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - x.begin())
#define inf 1000000000
#define INF 1000000000000000000
#define mod 1000000007
#define get_bit(x, y) ((x>>y)&1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cout << endl;}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cout << a << ' ', abc(b...);
}
template <typename T> void printv(T l, T r) {
    for (; l != r; ++l) cout << *l << " \n"[l + 1 == r];
}
template <typename A, typename B> istream& operator >> (istream& o, pair<A, B> &a) {
    return o >> a.X >> a.Y;
}
template <typename A, typename B> ostream& operator << (ostream& o, pair<A, B> a) {
    return o << '(' << a.X << ", " << a.Y << ')';
}
template <typename T> ostream& operator << (ostream& o, vector<T> a) {
    bool is = false;
    if (a.empty()) return o << "{}";
    for (T i : a) {o << (is ? ' ' : '{'), is = true, o << i;}
    return o << '}';
}
#ifdef loli
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif

const int mxN = 40005, mxM = 2e5 + 5;
int n, m;
int ql[mxM], qr[mxM], qt[mxM], qans[mxM];
int h[mxN], w[mxN];
int dpl[mxN][201], dpr[mxN][201];
int qid[mxM], qtmp[mxM];

void dq(int l, int r, int L, int R) {
    if (L > R) return;
    if (l == r) {
        for (int j = L; j <= R; j++) {
            int i = qid[j];
            if (qt[i] >= h[l])
                qans[i] = w[l];
        }
        return;
    }
    int mid = (l + r) >> 1;

    for (int i = mid; i >= l; i--) {
        for (int j = 0; j <= 200; j++) {
            if (i == mid) 
                dpl[i][j] = (j >= h[i] ? w[i] : 0);
            else {
                dpl[i][j] = dpl[i+1][j];
                if (j >= h[i]) 
                    dpl[i][j] = max(dpl[i][j], dpl[i+1][j-h[i]] + w[i]);
            }
            if (j) 
                dpl[i][j] = max(dpl[i][j], dpl[i][j-1]);
        }
    }
    for (int i = mid+1; i <= r; i++) {
        for (int j = 0; j <= 200; j++) {
            if (i == mid+1) 
                dpr[i][j] = (j >= h[i] ? w[i] : 0);
            else { 
                dpr[i][j] = dpr[i-1][j];
                if (j >= h[i]) 
                    dpr[i][j] = max(dpr[i][j], dpr[i-1][j-h[i]] + w[i]);
            }
            if (j) 
               dpr[i][j] = max(dpr[i][j], dpr[i][j-1]);
        }
    }

    int lcnt = L, rcnt = R;
    for (int j = L; j <= R; j++) {
        int i = qid[j];
        if (qr[i] <= mid) {
            qtmp[lcnt++] = i;
            continue;
        }
        if (ql[i] > mid) {
            qtmp[rcnt--] = i;
            continue;
        }
        test(l, r, i);
        for (int j = 0; j <= qt[i]; j++) {
            qans[i] = max(qans[i], dpl[ql[i]][j] + dpr[qr[i]][qt[i]-j]);
        }
    }
    for (int i = L; i <= R; i++) qid[i] = qtmp[i];

    dq(l, mid, L, lcnt-1);
    dq(mid+1, r, rcnt+1, R);
}

inline void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 0; i < m; i++) {
        cin >> ql[i] >> qr[i] >> qt[i];
        qid[i] = i;
    }
    
    dq(1, n, 0, m-1);

    for (int i = 0; i < m; i++)
        cout << qans[i] << '\n';
}

signed main() {
	IO;	
	solve();	
}
