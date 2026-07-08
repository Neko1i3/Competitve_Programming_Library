/*
Solution to the codeforces problem "Omsk Metro (hard version)" using centroid decomposition
link to the problem: https://codeforces.com/problemset/problem/1843/F2

We have to calculate min and max segment sum on many paths in a tree, all values are either -1 or 1
complexity: O(nlogn + qlogn)
*/
#include <bits/stdc++.h>
using namespace std;

const int M = 200007;
int n, q, val[M], ssize[M], p[M], cnt[M], sum[M], dp[M][20][5], cntr;
/*
dp[vertice][level]:
[0] predecessor in the centroid tree
[1] minimum prefix sum
[2] minimum segment sum
[3] maximum prefix sum
[4] maximum segment sum
*/
vector<int> tree[M];
vector<tuple<int,int,int>> query;
bool removed[M];
int centroid(int v, int m) { // find a centroid of a current subtree of size m
    ssize[v] = 1; bool uwu = true;
    for (int u : tree[v]) {
        if (u == p[v] || removed[u])
            continue;
        p[u] = v, centroid(u,m), ssize[v] += ssize[u]; // DFS procedure
        if (ssize[u] > m/2) // check if a child's subtree is too big
            uwu = false;
    }
    if (uwu && ssize[v] >= (m+1)/2) // check if v is a centroid
        cntr = v;
    return cntr;
}
void dfs(int v, int pv, int cntr) { // DFS for calculating various things, used inside the decomposition
    sum[v] = val[v]+sum[pv], dp[v][cnt[v]][0] = cntr;
    dp[v][cnt[v]][1] = min(dp[pv][cnt[pv]][1],sum[v]), dp[v][cnt[v]][3] = max(dp[pv][cnt[pv]][3],sum[v]);
    dp[v][cnt[v]][2] = min(dp[pv][cnt[pv]][2],sum[v]-dp[v][cnt[v]][3]), dp[v][cnt[v]][4] = max(dp[pv][cnt[pv]][4],sum[v]-dp[v][cnt[v]][1]);
    for (int u : tree[v])
        if (u != pv && !removed[u])
            dfs(u,v,cntr);
    cnt[v]++;
}
void process_subtree(int v) { // solving for the current centroid v
    sum[v] = val[v], dp[v][cnt[v]][0] = v;
    dp[v][cnt[v]][1] = val[v], dp[v][cnt[v]][2] = min(0,val[v]);
    dp[v][cnt[v]][3] = val[v], dp[v][cnt[v]][4] = max(0,val[v]);
    for (int u : tree[v])
        if (!removed[u])
            dfs(u,v,v); // going through every subtree if we split at v
    cnt[v]++;
}
void divide(int v, int m) { // the decomposition procedure
    int c = centroid(v,m);
    removed[c] = true, process_subtree(c); // solve for the current subtree
    for (int u : tree[c]) {
        if (removed[u])
            continue;
        p[u] = c;
        if (u != p[c]) // calculating the correct subtree size
            divide(u,ssize[u]);
        else
            divide(u,m-ssize[c]);
    }
}
void reset(int q) { // clearing after every test case
    for (int i = 0; i < q+7; i++)
        p[i] = 0, cnt[i] = 0, tree[i].clear(), removed[i] = false;
    query.clear();
}
void solve() {
    n = 1, cin >> q;
    int a,b,c;
    for (int i = 0; i < q; i++) {
        char z; cin >> z;
        if (z == '+')
            cin >> a >> val[++n], tree[a].push_back(n), tree[n].push_back(a);
        else
            cin >> a >> b >> c, query.push_back({a,b,c});
    }
    val[1] = 1, divide(1,n);
    for (auto qiqi : query) {
        a = get<0>(qiqi), b = get<1>(qiqi), c = get<2>(qiqi);
        int lca = 0;
        while (lca+1 < min(cnt[a],cnt[b]) && dp[a][lca+1][0] == dp[b][lca+1][0]) // naively processing LCA in the centroid decomposition tree
            lca++;
        if ((dp[a][lca][1]+dp[b][lca][1]-val[dp[a][lca][0]] <= c && dp[a][lca][3]+dp[b][lca][3]-val[dp[b][lca][0]] >= c) || (dp[a][lca][2] <= c && dp[a][lca][4] >= c) || (dp[b][lca][2] <= c && dp[b][lca][4] >= c))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    reset(q);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t; cin >> t;
    for (int i = 0; i < t; i++)
        solve();
    return 0;
}
