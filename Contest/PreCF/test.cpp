#include <bits/stdc++.h>
#ifdef LOCAL
#include "dbg.hpp"
#endif
#ifndef dbg
#define dbg(...)
#endif

using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 100100;
int n;
long long x[MAXN];
char d[MAXN];

int f(char c) {
    if (c == 'U' || c == 'R')
        return 1;
    if (c == 'D' || c == 'L')
        return -1;
    assert(false && "Unreachable");
}

int g(char c) {
    if (c == 'U' || c == 'D')
        return 1;
    if (c == 'R' || c == 'L')
        return -1;
    assert(false && "Unreachable");
}

struct segment {
    long long x1, y1, x2, y2;
} segments[MAXN];

void build(int l) {
    long long xcur = 0, ycur = 0;
    for (int i = 1; i <= l; ++i) {
        if (g(d[i]) == 1) // Vertical
        {
            long long newy = ycur + x[i] * f(d[i]);
            segments[i] = {xcur, min(ycur, newy), xcur, max(ycur, newy)};
            ycur = newy;
        } else // Horizontal
        {
            long long newx = xcur + x[i] * f(d[i]);
            segments[i] = {min(xcur, newx), ycur, max(newx, xcur), ycur};
            xcur = newx;
        }
    }
}

void flip() {
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 'U')
            d[i] = 'R';
        else if (d[i] == 'D')
            d[i] = 'L';
        else if (d[i] == 'L')
            d[i] = 'D';
        else if (d[i] == 'R')
            d[i] = 'U';
    }
}

bool isect(int i, int j) {
    segment si = segments[i], sj = segments[j];
    if (si.x2 < sj.x1 || sj.x2 < si.x1)
        return false;
    if (si.y2 < sj.y1 || sj.y2 < si.y1)
        return false;
    return true;
}

int h() {
    struct event {
        long long x;
        int type;
        int segmentId;
        long long y1, y2;
        event(long long x, int type, int id, long long y1, long long y2)
            : x(x), type(type), segmentId(id), y1(y1), y2(y2) {}
        bool operator<(const event &o) const {
            if (x != o.x)
                return x < o.x;
            return type < o.type;
        }
    };

    const int QUERY = 0, ADD = -1, REMOVE = 1;
    vector<int> ans = {n, n};
    for (int rev = 0; rev < 2; ++rev) {
        vector<event> events;
        events.reserve(2 * n);

        build(n);
        for (int i = 1; i <= n; ++i) {
            if (g(d[i]) == 1) // Vertical
            {
                events.emplace_back(segments[i].x1, QUERY, i, segments[i].y1,
                        segments[i].y2);
            } else // Horizontal
            {
                events.emplace_back(segments[i].x1, ADD, i, segments[i].y1, 0);
                events.emplace_back(segments[i].x2, REMOVE, i, segments[i].y1, 0);
            }
        }

        sort(all(events));
        map<long long, int> m;
        for (event &e : events) {
            // dbg(e.x, e.type, e.segmentId, e.y1, e.y2);
            if (e.type == ADD) {
                m[e.y1] = e.segmentId;
            } else if (e.type == QUERY) {
                if (m.empty())
                    continue;
                auto it1 = m.lower_bound(e.y1);
                if (it1 == m.end())
                    continue;
                while (it1 != m.end() && it1->first <= e.y2) {
                    if (isect(e.segmentId, it1->second) &&
                            abs(e.segmentId - it1->second) != 1) {
                        ans[rev] = min(ans[rev], e.segmentId - 1);
                        break;
                    }
                    it1 = next(it1);
                }
            } else if (e.type == REMOVE) {
                if (m.find(e.y1) != m.end())
                    m.erase(m.find(e.y1));
            }
        }

        flip();
    }
    return max(ans[0], ans[1]);
}

int hh() {
    int ret = n;
    for (int rev = 0; rev < 2; ++rev) {
        vector<tuple<long long, long long, int>> v;
        v.reserve(n);

        build(n);
        for (int i = 1; i <= n; ++i) {
            if (g(d[i]) == 1) // Vertical
                v.emplace_back(segments[i].x1, segments[i].y1, i);
        }

        sort(all(v));

        for (int i = 1; i < sz(v); ++i) {
            int id1 = get<2>(v[i]);
            int id2 = get<2>(v[i - 1]);
            if (isect(id1, id2)) {
                ret = min(ret, max(id1, id2));
            }
        }

        flip();
    }

    return ret;
}

bool ok(int l) {
    build(l);
    for (int i = 1; i + 1 < l; ++i)
        if (isect(i, l))
            return false;
    return true;
}

int bs(int k) {
    int bg = 0, nd = x[k], md;
    while (bg < nd) {
        md = (bg + nd) >> 1;
        x[k] = md;
        if (ok(k))
            bg = md + 1;
        else
            nd = md;
    }
    return bg;
}

void solve_case() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> d[i] >> x[i];
        if (i > 1 && d[i] == d[i - 1]) {
            x[i - 1] += x[i];
            n--;
            i--;
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (g(d[i]) == g(d[i - 1]) && d[i] != d[i - 1]) {
            n = i - 1;
            break;
        }
    }

    n = hh();
    x[n] = bs(n);

    long long ans = 0;
    int k = h();
    for (int i = 1; i <= k; ++i)
        ans += x[i];
    // dbg(k);
    if (k == n) {
        cout << ans << '\n';
        return;
    }

    cout << ans + bs(k + 1) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false), cin.tie(NULL);
    cout << setprecision(15) << fixed;
    int t = 1;
    // cin >> t;
    while (t--)
        solve_case();
}
