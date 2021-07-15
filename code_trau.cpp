#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, a, b) for (int i = (a); i <= (b); ++i)
#define FOD(i, a, b) for (int i = (a) - 1; i >= (b); --i)
#define RED(i, a, b) for (int i = (a); i >= (b); --i)
#define X first
#define Y second

using namespace std;
const int BASE = 100000000;
const int INF = 1e9 + 8;
const int T = 800;
vector<string> res;
vector<char> tmp;
string s;
int cnt[355], n, k, t, nn;

void check()
{
    int ok = 0; ++cnt[tmp[0]];
    for (int i = 1; i < (int)(tmp.size()); ++i)
    {
        ++cnt[tmp[i]];
        int odd = 0;
        REP(i, 1, 300) if (cnt[i]&1) ++odd;
        if (i == (int)(tmp.size()) - 1)
        {
            if (odd == 0 || odd == 1) continue;
            return;
        }
        if (odd == 0 || odd == 1) ++ok;
    }
    REP(i, 0, 300) cnt[i] = 0;
    if (ok >= k)
    {
        string ss = "";
        for (char x : tmp) ss += x;
        res.push_back(ss);
    }
}

void solve(int i)
{
    if (i >= n) {check(); return;}
    FOR(j, 0, nn)
    {
        tmp.push_back(s[j]);
        solve(i + 1);
        tmp.pop_back();
    }
}

int main()
{
    freopen("D:\\test.txt", "r", stdin);
    freopen("D:\\test_ans.txt", "w", stdout);
    cin >> n >> k;
    cin >> s;
    cin >> t;

    nn = s.length();
    solve(0);
    sort(res.begin(), res.end());
    if (t > res.size()) cout << "out of size";
    else cout << res[t - 1] << endl;
    /*for (int i = 0; i < (int)(res.size()); ++i)
        cout << res[i] << endl;*/
}
