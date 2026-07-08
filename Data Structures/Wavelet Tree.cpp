// Solution to the kth smallest problem using a wavelet tree, complexity: O(nlogn + qlogn)
// tutorial on: https://rachitiitr.blogspot.com/2017/06/wavelet-trees-wavelet-trees-editorial.html
// problem link: https://judge.yosupo.jp/problem/range_kth_smallest
#include <bits/stdc++.h>
using namespace std;

const int baza = (1<<18);
vector<int> d[2*baza], ile[2*baza]; map<int,int> mp;
int n, q, cnt, a[baza], org[baza];
void build(int v, int l, int r) { // building the wavelet tree
    cnt = 0;
    for (int i : d[v]) {
        if (v < baza) {
            if (mp[a[i]] <= (l+r)/2)
                d[2*v].push_back(i), cnt++;
            else
                d[2*v+1].push_back(i);
        }
        ile[v].push_back(cnt);
    }
    if (v < baza)
        build(2*v,l,(l+r)/2), build(2*v+1,(l+r)/2+1,r);
}
int query(int l, int r, int k, int v) { // recursive procedure
    if (v >= baza)
        return org[v-baza];
    int ll = ((l > 0) ? ile[v][l-1] : 0), rr = ile[v][r];
    if (k <= rr-ll)
        return query(ll,rr-1,k,2*v);
    else
        return query(l-ll,r-rr,k-rr+ll,2*v+1);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> q; int l,r,k;
    for (int i = 0; i < n; i++)
        cin >> a[i], mp[a[i]] = 0, d[1].push_back(i);
    for (auto it = mp.begin(); it != mp.end(); it++)
        it->second = cnt, org[cnt++] = it->first; // scaling down the values
    build(1,0,baza-1);
    for (int i = 0; i < q; i++)
        cin >> l >> r >> k, cout << query(l,r-1,k+1,1) << endl;
    return 0;
}
