// Solution to a codeforces problem "Sea, You & copriMe" (https://codeforces.com/problemset/problem/2131/H)
// Great example of using the inclusion-exclusion principle
#include <bits/stdc++.h>
using namespace std;

const int M = 1000000;
vector<int> pd[M+1]; // list of prime divisors for every number up to M
void solve() {
    int n,m; cin >> n >> m;
    int a[n+1], cnt[m+1], ans[4];
    long long sum = 0; vector<int> v[3];
    fill(cnt,cnt+m+1,0);
    for (int i = 1; i <= n; i++) { // finding an arbitrary coprime pair
        cin >> a[i]; int x = i-1, y = pd[a[i]].size(), z[1<<y]; z[0] = 1;
        for (int mask = 1; mask < (1<<y); mask++) { // divisor of a[i] in a bitmask form
            int b = __builtin_ctz(mask); z[mask] = z[mask^(1<<b)]*pd[a[i]][b]; // z[mask] is the actual divisor
            x -= ((__builtin_popcount(mask)&1) ? cnt[z[mask]] : -cnt[z[mask]]); // x is how many coprime pairs a[i] makes up (with j < i)
            cnt[z[mask]]++;
        }
        if (x > 0)
            sum += x, ans[1] = i; // sum is the total numbers of coprimme pairs in a
    }
    if (sum == 0) {
        cout << 0 << endl;
        return;
    }
    for (int i = 1; i < ans[1]; i++) // we try forcefully matching ans[0] with ans[1]
        if (__gcd(a[i],a[ans[1]]) == 1)
            ans[0] = i;
    for (int i = 1; i <= n; i++) {
        if (i == ans[0] || i == ans[1])
            continue;
        if (__gcd(a[i],a[ans[0]]) == 1 && __gcd(a[i],a[ans[1]]) == 1)
            v[2].push_back(i);
        else if (__gcd(a[i],a[ans[0]]) == 1)
            v[0].push_back(i);
        else if (__gcd(a[i],a[ans[1]]) == 1)
            v[1].push_back(i);
    }
    if (sum-1 > v[0].size() + v[1].size() + 2*v[2].size()) { // check if we can search for the second pair after discarding ans[0] and ans[1]
        // we do the same algorithm for finding an arbitrary coprime pair (with 2 elements now blocked)
        fill(cnt,cnt+m+1,0); int cnt = 0;
        for (int i = 1; i <= n; i++) {
            if (i == ans[0] || i == ans[1])
                continue;
            int x = cnt++, y = pd[a[i]].size(), z[1<<y]; z[0] = 1;
            for (int mask = 1; mask < (1<<y); mask++) {
                int b = __builtin_ctz(mask); z[mask] = z[mask^(1<<b)]*pd[a[i]][b];
                x -= ((__builtin_popcount(mask)&1) ? cnt[z[mask]] : -cnt[z[mask]]);
                cnt[z[mask]]++;
            }
            if (x > 0) {
                for (int j = 1; j < i; j++) {
                    if (j == ans[0] || j == ans[1])
                        continue;
                    if (__gcd(a[j],a[i]) == 1)
                        ans[2] = j;
                }
                cout << ans[0] << " " << ans[1] << " " << ans[2] << " " << i << endl;
                return;
            }
        }
    }
    else { // we have to split ans[0] and ans[1]
        while (!v[2].empty()) {
            if (v[0].size() <= v[1].size())
                v[0].push_back(v[2].back());
            else
                v[1].push_back(v[2].back());
            v[2].pop_back();
        }
        if (v[0].empty() || v[1].empty())
            cout << 0 << endl;
        else
            cout << ans[0] << " " << v[0].back() << " " << ans[1] << " " << v[1].back() << endl;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    for (int i = 2; i <= M; i++) // precomputing prime divisors
        if (pd[i].empty())
            for (int j = i; j <= M; j += i)
                pd[j].push_back(i);
    int t; cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
