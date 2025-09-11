#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define pii pair<int,int>
#define f first
#define s second
#define vi vector<int>
#define vll vector<ll>
#define SZ(a) ((int)(a).size())
#define ALL(v) (v).begin(), (v).end()
#define pb push_back
#define eb emplace_back
#define push emplace
#define lb(x, v) lower_bound(ALL(x), v)
#define ub(x, v) upper_bound(ALL(x), v)
#define re(x) reverse(ALL(x))
#define uni(x) x.resize(unique(ALL(x)) - (x).begin())
#define inf 1000000000
#define INF 1000000000000000000LL
#define mod 1000000007
#define MOD 998244353
#define get_bit(x, y) (((x) >> (y)) & 1)
#define mkp make_pair
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
void abc() {cerr << '\n';}
template <typename T, typename ...U> void abc(T a, U ...b) {
    cerr << a << ' ', abc(b...);
}
#ifdef debug
#define test(args...) abc("[" + string(#args) + "]", args)
#else
#define test(args...) void(0)
#endif
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }

const int MAXN = 2e5 + 5, MAXL = 30;

struct DSU {
    vi parent, rank, val;

    void init(int n, const vi &a) {
        parent.resize(n + 1);
        rank.assign(n + 1, 0);
        val.resize(n + 1);
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
            val[i] = a[i - 1];
        }
    }

    int find(int u) {
        return parent[u] == u ? u : parent[u] = find(parent[u]);
    }

    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) {
            val[u] = val[v];
            parent[v] = u;
        } else {
            if (rank[u] == rank[v]) rank[v]++;
            parent[u] = v;
        }
    }

    int get_val(int u) {
        return val[find(u)];
    }
};

int nextSmaller[MAXN];
vector<int> childList[MAXN];
vector<pii> queryList[MAXN];

void solve() {
    int n, q;
    cin >> n >> q;
    vi arr(n + 1), leftQ(q), rightQ(q);
    for (int i = 1; i <= n; i++) cin >> arr[i];
    for (int i = 0; i < q; i++) cin >> leftQ[i] >> rightQ[i];

    vector<vi> groupIdx(MAXL), groupVal(MAXL);
    for (int i = 1; i <= n; i++) {
        int v = arr[i];
        int L = 31 - __builtin_clz(v);
        if (L >= MAXL) L = MAXL - 1;
        groupIdx[L].pb(i);
        groupVal[L].pb(v);
    }

    vector<vll> prefixSum(MAXL);
    for (int L = 0; L < MAXL; L++) {
        int m = SZ(groupIdx[L]);
        prefixSum[L].assign(m + 1, 0);
        for (int i = 0; i < m; i++)
            prefixSum[L][i + 1] = prefixSum[L][i] + groupVal[L][i];
    }

    vector<pii> sortedLeft(q), sortedRight(q);
    for (int i = 0; i < q; i++) {
        sortedLeft[i] = {leftQ[i], i};
        sortedRight[i] = {rightQ[i], i};
    }
    sort(ALL(sortedLeft)), sort(ALL(sortedRight));

    vll accAnswer(q, 0), answer(q, 0);
    vector<char> isDone(q, 0);

    for (int L = 0; L < MAXL; L++) {
        int m = SZ(groupIdx[L]);
        if (!m) continue;

        auto &idx = groupIdx[L], &val = groupVal[L];
        vi lPos(q), rPos(q);

        int ptr = 0;
        for (auto &[a, i] : sortedLeft) {
            while (ptr < m && idx[ptr] < a) ptr++;
            lPos[i] = ptr;
        }

        ptr = 0;
        for (auto &[b, i] : sortedRight) {
            while (ptr < m && idx[ptr] <= b) ptr++;
            rPos[i] = ptr - 1;
        }

        for (int i = 1; i <= m; i++) {
            childList[i].clear();
            queryList[i].clear();
        }

        vi stk;
        stk.reserve(m + 2);
        stk.pb(0);
        for (int i = m; i >= 1; i--) {
            while (SZ(stk) > 1 && val[stk.back() - 1] >= val[i - 1]) stk.pop_back();
            nextSmaller[i] = stk.back();
            if (nextSmaller[i]) childList[nextSmaller[i]].pb(i);
            stk.pb(i);
        }

        for (int i = 0; i < q; i++) {
            int l = lPos[i] + 1, r = rPos[i] + 1;
            if (l <= r) queryList[r].eb(l, i);
        }

        DSU dsu;
        dsu.init(m, val);

        for (int i = 1; i <= m; i++) {
            for (int j : childList[i]) dsu.merge(j, i);
            for (auto &[l, qi] : queryList[i]) {
                if (isDone[qi]) continue;
                int mn = dsu.get_val(l);
                if (accAnswer[qi] + 1 < mn) {
                    isDone[qi] = 1;
                    answer[qi] = accAnswer[qi] + 1;
                } else {
                    accAnswer[qi] += prefixSum[L][rPos[qi] + 1] - prefixSum[L][lPos[qi]];
                }
            }
        }
    }

    for (int i = 0; i < q; i++) {
        if (!isDone[i]) answer[i] = accAnswer[i] + 1;
        cout << answer[i] << '\n';
    }
}

signed main() {
    IO;
    solve();
}

