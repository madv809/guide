#include<bits/stdc++.h>

#define LL long long
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
//#define LL int

using namespace std;
const int mxn = 5e1 + 5;
const int MOD = 1e9 + 7;
const LL MODL = 1e9 + 7;
const int BASE = 100000000;
const int INF = 1e9 + 8;
const int T = 800;
struct BigN
{
    int n;
    int a[8];

    BigN()
    {
        FOR(i, 0, 8) a[i] = 0;
        n = 0;
    }
    void resize (int x) {for (int i = 0; i < x; ++i) a[i] = 0; n = x;}
    void trim() {while (n > 1 && a[n - 1] == 0) --n;}
    void normalize()
    {
        for (int i = 0; i < n - 1; ++i)
        {
            a[i + 1] += a[i]/BASE;
            a[i] %= BASE;
        }
        trim();
    }

    int &operator [] (int i) {return a[i];}
    const int operator [] (int i) const {return a[i];}
    void operator = (int x)
    {
        a[0] = x;
        n = 1;
    }
    void operator = (const BigN &A)
    {
        n = A.n;
        for (int i = 0; i < n; ++i) a[i] = A[i];
    }

    void operator++()
    {
        ++n;
        ++a[0];
        normalize();
    }

    void operator += (const BigN &A)
    {
        FOR(i, 0, A.n) a[i] += A[i];
        n = max(n, A.n) + 1;
        normalize();
    }

    void operator -= (const BigN &A)
    {
        FOR(i, 0, A.n)
        {
            a[i] -= A[i];
            if (a[i] < 0)
            {
                --a[i + 1];
                a[i] += BASE;
            }
        }
        normalize();
    }
};

bool operator > (const BigN &A, const BigN &B)
{
    if (A.n != B.n) return (A.n > B.n);
    for (int i = A.n - 1; i >= 0; --i) if (A[i] != B[i]) return (A[i] > B[i]);
    return 0;
}

istream &operator >> (istream &cin, BigN &A)
{
    string s;
    cin >> s;
    int k = s.length(), x;
    A = 0; A.resize(k/8 + 1);
    for (int i = 0; i < k; ++i)
    {
        x = (k - 1 - i)/8;
        A[x] = A[x]*10 + (s[i] - '0');
    }
    A.normalize();
    return cin;
}

ostream &operator << (ostream &cout, const BigN &A)
{
    printf("%d", A[A.n - 1]);
    for (int i = A.n - 2; i >= 0; --i) printf("%08d", A[i]);
    return cout;
}

// phần ở trên là code bignum, code chính bắt đầu từ đây

bool panlin(int mask)
{
    if (mask == 0 || mask == 1) return 1;
    return ((mask&(mask - 1)) == 0);
}

string set_char;
BigN dp[mxn][mxn][(1 << 5)][(1 << 5)], f[mxn][mxn][(1 << 5)][(1 << 5)], g[mxn][mxn][(1 << 5)], t;
char res[mxn];
int pos[mxn], n, k;
signed main()
{
    //freopen("D:\\test.txt", "r", stdin);
    //freopen("D:\\test2.txt", "w", stdout);
    cin >> n >> k; cin >> set_char; cin >> t;
    int nn = set_char.length();
    sort(set_char.begin(), set_char.end());
    int pow_nn = (1 << nn);
    FOR(mask, 0, pow_nn)
    {
        dp[0][0][mask][0] = 1;
        f[0][0][mask][0] = 1;
    }

    REP(i, 1, n) REP(j, 0, i) FOR(mask, 0, pow_nn) FOR(cur_mask, 0, pow_nn) FOR(k, 0, nn)
    {
        if (panlin((cur_mask^mask)))
        {
            if (j > 0)
            dp[i][j][mask][cur_mask] += dp[i - 1][j - 1][mask][(cur_mask^(1 << k))];
        }
        else dp[i][j][mask][cur_mask] += dp[i - 1][j][mask][(cur_mask^(1 << k))];
        f[i][j][mask][cur_mask] += dp[i - 1][j][mask][(cur_mask^(1 << k))];
    }

    REP(i, 1, n) RED(j, i, 0) FOR(mask, 0, pow_nn)
    {
        g[i][j][mask] = g[i][j + 1][mask];
        FOR(cur_mask, 0, pow_nn)
            g[i][j][mask] += f[i][j][mask][cur_mask];
    }
    FOR(mask, 0, pow_nn)
        g[0][0][mask] = 1;

    //FOR(mask, 0, (1 << nn))
    //cout << f[n - 1][7][1][mask] << endl; return 0;

    int mask = 0, leng = n, cur_k = 0;
    while(leng > 0)
    {
        bool okk = 0; // dùng để so test với trình trâu chứ không có gì đặc biệt
        FOR(j, 0, nn)
        {
            bool ok = panlin((mask^(1 << j)));
            if (leng == n || leng == 1) ok = 0;
            if (t > g[leng - 1][max(0, k - cur_k - ok)][(mask^(1 << j))])
                t -= g[leng - 1][max(0, k - cur_k - ok)][(mask^(1 << j))];
            else
            {
                res[leng] = set_char[j];
                mask ^= (1 << j);
                cur_k += ok;
                --leng;
                okk = 1;
                break;
            }
        }
        if (!okk) {cout << "out of size"; return 0;} // dùng để so test với trình trâu chứ không có gì đặc biệt
    }
    RED(i, n, 1) cout << res[i]; cout << endl;
    //cout << set_char;
}
