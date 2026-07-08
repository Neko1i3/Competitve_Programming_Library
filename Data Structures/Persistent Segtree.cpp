// Persistent Segment Tree implementation
// problem link: https://www.spoj.com/problems/PSEGTREE/
#include <bits/stdc++.h>
using namespace std;

const int base = (1<<17), M = 100000;
int n, q, a[M+1], root[M+1], m = 2*base, cnt;
struct node {
    long long s = 0;
    int ver = 0, l = 0, r = 0;
};
node pst[21*M];
void init() { // build a regular segment tree over array a (version 0)
    root[0] = 1;
    for (int i = 1; i <= n; i++)
        pst[i+base].s = 1ll*a[i];
    for (int i = base-1; i > 0; i--)
        pst[i].s = pst[2*i].s + pst[2*i+1].s, pst[i].l = 2*i, pst[i].r = 2*i+1;
}
void add(int i, int x, int pv) { // make a new version from pv where element i is incremented by x
    int v = m, u = root[pv];
    vector<int> ind; root[++cnt] = m++;
    for (int j = 16; j >= 0; j--) {
        ind.push_back(v), pst[v].ver = cnt;
        if (i&(1<<j))
            pst[v].l = pst[u].l, pst[v].r = m, v = m++, u = pst[u].r;
        else
            pst[v].l = m, pst[v].r = pst[u].r, v = m++, u = pst[u].l;
    }
    pst[v].s = pst[u].s+x, pst[v].ver = cnt;
    while (!ind.empty())
        pst[ind.back()].s = pst[pst[ind.back()].l].s + pst[pst[ind.back()].r].s, ind.pop_back();
}
long long sum(int x, int y, int v, int l, int r) { // query
    if (r < x || l > y)
        return 0;
    if (x <= l && r <= y)
        return pst[v].s;
    else
        return sum(x,y,pst[v].l,l,(l+r)/2) + sum(x,y,pst[v].r,(l+r)/2+1,r);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n; int t,x,y,z;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    init(), cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> t >> x >> y >> z;
        if (t == 1)
            add(y,z,x);
        else
            cout << sum(y,z,root[x],0,base-1) << endl;
    }
    return 0;
}
