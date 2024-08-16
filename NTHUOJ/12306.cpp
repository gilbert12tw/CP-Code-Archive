#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include<algorithm>
#include<queue>
#include<map>
#include<set>
#include<bitset>
#include<cstring>
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

int L, HP, MHP, MDMG;
int atk[30], heal[30];

struct State {
    int level;
    int MonsterHP;
    int PlayerHP;
    State(int l, int mhp, int php): level(l), MonsterHP(mhp), PlayerHP(php) {}
    State(): level(1), MonsterHP(0), PlayerHP(0) {}
};

int dis_table[16][301][401];
int set_dis(State x, int val) {
    if (dis_table[x.level][x.PlayerHP][x.MonsterHP] != -1) return 0;
    dis_table[x.level][x.PlayerHP][x.MonsterHP] = val; 
    return 1;
}

int get_dis(State x) {
    if (dis_table[x.level][x.PlayerHP][x.MonsterHP] == -1) return 0;
    return dis_table[x.level][x.PlayerHP][x.MonsterHP]; 
}

inline void solve() {
    cin >> L >> HP >> MHP >> MDMG;
    for (int i = 1; i <= L; i++) 
        cin >> atk[i] >> heal[i];

    memset(dis_table, -1, sizeof dis_table);
    State cur = State(1, MHP, HP);
    queue<State> q;
    q.push(cur);
    set_dis(cur, 0);

    while (!q.empty()) {
        cur = q.front(); q.pop();

        if (cur.MonsterHP <= atk[cur.level]) {
            cout << get_dis(cur) + 1 << '\n';
            return;
        }
        
        State nxt;
        int d = get_dis(cur);
        
        // attack
        nxt = cur; 
        nxt.MonsterHP -= atk[nxt.level];
        nxt.PlayerHP -= MDMG;
        if (nxt.PlayerHP > 0 && set_dis(nxt, d + 1)) { // not in map yet
            q.push(nxt);
        }

        // heal
        nxt = cur;
        nxt.PlayerHP = min(HP, nxt.PlayerHP + heal[nxt.level]);
        nxt.PlayerHP -= MDMG;
        if (nxt.PlayerHP > 0 && set_dis(nxt, d + 1)) { // not in map yet
            q.push(nxt);
        }
 
        // level up
        if (nxt.level == L) continue;
        nxt = cur;
        nxt.level += 1;
        nxt.PlayerHP -= MDMG;
        if (nxt.PlayerHP > 0 && set_dis(nxt, d + 1)) { // not in map yet
            q.push(nxt);
        }
    }
    cout << -1 << '\n';
}

signed main() {
	IO;	
	solve();	
}
