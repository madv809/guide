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
const int mxn = 1e9 + 5;
const int ntest = 1000;
mt19937 radd(time(NULL));

LL rad(LL l, LL h) // hàm random các giá trị trong đoạn [l, h]
{
    LL x = (LL)radd();
    return (l + x%(h - l + 1));
}


const string code_chuan = "D:\\code\\bin\\Debug\\code.exe";
const string code_trau =  "D:\\code_trau\\bin\\Debug\\code_trau.exe";
const string test_chuan = "D:\\test2.txt";
const string test_trau = "D:\\test_ans.txt";
const string test_input = "D:\\test.txt";
ofstream f;
set<LL> s;
int main()
{
    srand(time(NULL));
    REP(i, 1, ntest)
    {
        f.open(test_input, ios::out);
        // viết code sinh test ở đây
        s.clear();
        LL n = rad(3, 5), k = rad(4, 8);
        f << n << ' ' << k << endl;
        REP(i, 1, n)
        {
            LL x = 96LL + rad(0, 24);
            while(s.find(x) != s.end())x = 96LL + rad(0, 24);
            s.insert(x);
            f << char(x);
        }
        f << endl;
        f << rad(1, 10);
        //
        f.close();
        system((code_chuan).c_str()); // chạy code "chuẩn"
        system((code_trau).c_str()); // chạy code trâu

        // xong rồi so sánh 2 kết quả với nhau
         if (system(("fc " + test_chuan + ' ' + test_trau).c_str()) != 0)
        {
            cout << ": WRONG!\n";
            return 0;
        }
        cout << ": CORRECT!\n";
    }
}
