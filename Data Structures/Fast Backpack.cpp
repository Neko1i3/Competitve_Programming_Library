// Solution to problem "Drwale" from XXX Polish OI
// We want to split a set of numbers into two as evenly as possible (regarding the sum of numbers)
// The model solution is a backpack with optimizations (2+1, bitset shift) with a complexity of O(n**(3/2) / 64)
#include <bits/stdc++.h>
using namespace std;

bitset<2500001> bp; // our backpack
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,x,avg,ans = 0;
    cin >> n;
    priority_queue<int,vector<int>,greater<int>> q; // priority queue for the 2+1 trick
    vector<int> v;
    for (int i = 0; i < n; i++)
        cin >> x, ans += x, v.push_back(x);
    sort(v.begin(),v.end());
    avg = v.back(), ans = (ans-avg)/2, v.pop_back();
    while (!v.empty())
        q.push(v.back()), v.pop_back();
    while (q.size() >= 3) { // merging
        int a,b,c;
        a = q.top(), q.pop();
        b = q.top(), q.pop();
        c = q.top(), q.pop();
        if (a == b && b == c)
            q.push(a), q.push(b+c);
        else
            v.push_back(a), q.push(b), q.push(c);
    }
    while (!q.empty())
        v.push_back(q.top()), q.pop();
    bp[0] = 1;
    for (int d : v)
        bp |= (bp << d); // bitset backpack
    while (bp[ans] == 0)
        ans--; // finding the answer
    cout << ans+avg << endl;
    return 0;
}
