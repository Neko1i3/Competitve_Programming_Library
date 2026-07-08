// Very basic combinatorics with modular arithmetic
#include <bits/stdc++.h>
using namespace std;

const int M = 1000000;
const long long mod = 998244353;
long long fact[M+1], inv[M+1];
long long fastexp(long long a, long long b) { // a to the power of b using fast exponentiation (with modulo)
    long long ans = 1;
    for (int i = 29; i >= 0; i--) {
        ans = (ans*ans)%mod;
        if (b&(1ll<<i))
            ans = (ans*a)%mod;
    }
    return ans;
}
long long newt(int a, int b) { // Newton's binomial - choose a out of b objects
    return ((fact[a]*fein[b])%mod*fein[a-b])%mod;
}
long long stbars(int a, int b) { // stars and bars for a objects, b bins
    return newt(a+b-1,a);
}
long long catalan(int n) { // n-th Catalan number
    return (newt(2*n,n)*fastexp(n+1,mod-2))%mod;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    fact[0] = inv[0] = 1;
    for (int i = 1; i <= M; i++)
        fact[i] = (fact[i-1]*i)%mod, inv[i] = fastexp(fact[i],mod-2); // precomputation of factorials and modular inverses
    return 0;
}
