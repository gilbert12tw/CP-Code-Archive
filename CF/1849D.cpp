#include<bits/stdc++.h>
#define loli
using namespace std;
typedef long long ll;
#define int ll
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

inline void solve() {
    int n; cin >> n;
    vector<int> a(n + 1), vis(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
   
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 2 && vis[i] == 0) {
            cnt++;
            int j = i;
            vis[i] = 1;
            while (j + 1 <= n && vis[j+1] == 0) {
                j++;
                vis[j] = 1;
                if (a[j] == 0) break;
            }
             
            j = i;
            while (j - 1 >= 1 && vis[j-1] == 0) {
                j--;
                vis[j] = 1;
                if (a[j] == 0) break;
            }

        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        int deg = 0;
        if (a[i] == 0) {
            if (i != 1 && (a[i-1] == 1 && vis[i-1] == 0)) deg++;
            if (i != n && (a[i+1] == 1 && vis[i+1] == 0)) deg++;
            if (deg == 0) {
                vis[i] = 1;
                cnt++;
            }
            if (deg == 1) q.push(i);
        }
    }

    while (!q.empty()) {
        int x = q.front(); q.pop();
        if (vis[x]) continue;
        if (x != 1 && a[x-1] == 1 && vis[x-1] == 0) {
            vis[x] = 1;
            cnt++;
            while (x - 1 >= 1 && a[x-1] == 1 && vis[x-1] == 0) {
                vis[--x] = 1;
            }
            if (x - 1 >= 1 && vis[x - 1] == 0) {
                q.push(x-1);
            }
        } else if (x != n && a[x+1] == 1 && vis[x+1] == 0) {
            vis[x] = 1;
            cnt++;
            while (x + 1 <= n && a[x+1] == 1 && vis[x+1] == 0) {
                vis[++x] = 1;
            }
            if (x + 1 <= n && vis[x + 1] == 0) {
                q.push(x+1);
            }
        } else {
            vis[x] = 1;
            cnt++;
        }
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) continue;
        if (vis[i] == 0) {
            cnt++;
            int j = i;
            vis[i] = 1;
            while (j + 1 <= n && vis[j+1] == 0) {
                j++;
                vis[j] = 1;
                if (a[j] == 0) break;
            }
        }
    }

    cout << cnt;
}

signed main() {
	IO;	
	solve();	
}
