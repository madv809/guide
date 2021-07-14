#include<bits/stdc++.h>

//#define LL long long
#define ULL unsigned long long
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define FOD(i, a, b) for (int i = (a) - 1; i >= (b); --i)
#define RED(i, a, b) for (int i = (a); i >= (b); --i)
#define X first
#define Y second
#define pb(a) push_back(a);
#define pii pair<int, int>
#define pLi pair<LL, int>
#define piL pair<int, LL>
#define pLL pair<LL, LL>
#define ar array
#define ef else if
//#define lb lower_bound
#define one "bridge"
#define two "penguins"
#define lb long double
//#define double long double
//#define int LL
#define LL int

using namespace std;
const int mxn = 3e5 + 1;
const int MOD = 1e9 + 7;
const LL MODL = 1e9 + 7;
const int BASE = 10000;
const int INF = 1e9 + 8;
struct node
{
    LL val;
    node *ptr[27];
    node()
    {
        FOR(i, 0, 27) ptr[i] = NULL;
        val = 0;
    }
} *root;
string c[mxn];
vector<int> s[mxn], s2;
LL dp[mxn], f[mxn], g[mxn];
int cnt[mxn], p[mxn], n, m;

LL get(const int &i)
{
    node *u = root;
    int pos = 0, nn = (int)(c[i].length()) - 1, nx;
    LL res = 0;
    while(pos < nn)
    {
        nx = (int)(c[i][pos] - 'A');
        if (u->ptr[nx] == NULL) return res;
        u = u->ptr[nx];
        res = max(res, u->val);
        ++pos;
    }
    return res;
}

void update(const int &i)
{
    node *u = root;
    int pos = 0, nn = (int)(c[i].length()), nx;
    while(pos < nn)
    {
        nx = (int)(c[i][pos] - 'A');
        if (u->ptr[nx] == NULL) u->ptr[nx] = new node();
        u = u->ptr[nx];
        ++pos;
    }
    u->val = max(u->val, dp[i]);
}

signed main()
{
    //freopen("D:\\test.txt", "r", stdin);
    //freopen("D:\\test2.txt", "w", stdout);
    cin >> n >> m;
    REP(i, 1, n)
    {
        cin >> c[i];
        scanf("%d", &p[i]);
    }
    int x, y;
    REP(i, 1, m)
    {
        scanf("%d%d", &x, &y);
        s[x].pb(y); s[y].pb(x);
        ++cnt[x]; ++cnt[y];
    }
    int T = (int)(sqrt(2.0*m));
    REP(i, 1, n)
    {
        if (cnt[p[i]] > T) s2.pb(p[i]);
        sort(s[i].begin(), s[i].end());
    }

    root = new node();
    for (int i = n; i >= 1; --i)
    {
        dp[i] = max((LL)(p[i]), get(i) + (LL)(p[i]));
        dp[i] = max(dp[i], f[p[i]] + (LL)(p[i]));
        for (int x : s2)
        {
            auto it = lower_bound(s[x].begin(), s[x].end(), p[i]);
            if (it == s[x].end() || *it != p[i]) continue;
            dp[i] = max(dp[i], g[x] + (LL)(p[i]));
        }
        update(i);
        if (cnt[p[i]] <= T)
        {
            for (int x : s[p[i]])
                f[x] = max(f[x], dp[i]);
        }
        else g[p[i]] = max(g[p[i]], dp[i]);
    }
    LL res = 0;
    REP(i, 1, n) res = max(res, dp[i]);
    cout << res;
}
