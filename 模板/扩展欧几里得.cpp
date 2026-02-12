#include <bits/stdc++.h>
using namespace std;
#define int long long
struct GCD
{
    int gcd_ans;
    int x;
    int y;
};

GCD ex_gcd(int a, int b, int x, int y)
{
    if (b == 0)
    {
        return (GCD){a, 1, 0};
    }
    GCD last = ex_gcd(b, a % b, x, y);
    int next_x, next_y;
    next_x = last.y;
    next_y = last.x - (a / b) * last.y;
    return (GCD){last.gcd_ans, next_x, next_y};
}
int ans_x, ans_y;
void Exgcd(int a, int b, int &x, int &y)
{
    if (!b)
    {
        x = 1;
        y = 0;
        return;
    }
    Exgcd(b, a % b, x, y);
    int tmp = x;
    x = y;
    y = tmp - (a / b) * y;
}
signed main()
{
    int a, b;
    cin >> a >> b; // ax+by=(a,b);

    GCD re = ex_gcd(a, b, ans_x, ans_y);
    cout << re.x << " " << re.y << endl;
    cout << re.x * a + re.y * b << endl;
    Exgcd(a, b, ans_x, ans_y);
    cout << ans_x << " " << ans_y << endl;
    return 0;
}
