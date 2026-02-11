#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e7 + 5;
int n;
bool is_prime[N];  // is_prime[i]表示i是否为质数
vector<int> prime; // 存储质数
// 线性筛法 求[1,n]内质数
// 线性筛的核心优势在于每个合数只会被其最小的质因子标记一次
void find_prime(int upper)
{ // upper 为上界
    for (int i = 2; i <= upper; i++)//
    {
        if (!is_prime[i])
        {
            prime.push_back(i);
        }
        for (int j : prime)
        {
            if (i * j > upper)
            {
                break; // 防止越界
            }
            is_prime[i * j] = true; 
            if (i % j == 0)
            {
                break;
            }
            // i % j == 0
            // 换言之，i 之前被 j 筛过了
            // 由于 prime 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定会被
            // j 的倍数筛掉，就不需要在这里先筛一次，所以这里直接 break
            // 掉就好了
        };
    }
}

signed main()
{
    cin >> n;
    find_prime(n);
    for (int i : prime)
    { // 遍历prime数组
        cout << i << " ";
    }
    return 0;
}
