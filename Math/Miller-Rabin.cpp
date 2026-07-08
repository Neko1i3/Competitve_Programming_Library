// Miller-Rabin primality test, deterministic for numbers up to 10e18
// tutorial on: https://cp-algorithms.com/algebra/primality_tests.html
// problem link: https://judge.yosupo.jp/problem/primality_test
#include <bits/stdc++.h>
using namespace std;
using u128 = __uint128_t;
const u128 i128 = 1;

long long fastexp(long long a, long long b, long long mod) { // computing a to the power of b
    long long x = 1; a %= mod;
    for (int i = 59; i >= 0; i--) {
        x = (i128*x*x)%mod;
        if (b&(1ll<<i))
            x = (i128*x*a)%mod;
    }
    return x;
}
bool czy(long long n, long long a, long long d, int s) {
    long long x = fastexp(a,d,n);
    if (x == 1 || x == n-1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (i128*x*x)%n;
        if (x == n-1)
            return false;
    }
    return true;
}
bool prime(long long n) { // is n a prime number
    if (n < 2)
        return false;
    int s = 0; long long d = n-1;
    while (d%2 == 0)
        d /= 2, s++;
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == 1ll*a)
            return true;
        if (czy(n,1ll*a,d,s))
            return false;
    }
    return true;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int q; cin >> q;
    long long n;
    for (int i = 0; i < q; i++)
        cin >> n, cout << ((prime(n)) ? "Yes" : "No") << endl;
    return 0;
}
