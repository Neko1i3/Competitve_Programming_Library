// Computing LCA using binary lifting for an arbitrary tree, O(nlogn) memory
#include <bits/stdc++.h>
using namespace std;

const int maxn = (1<<19);
int n, dist[maxn], jp[maxn][19]; // distance from the root, jump-pointers array
vector<int> tree[maxn];
void dfs(int v, int p) { // precomputation
    dist[v] = dist[p]+1, jp[v][0] = p;
    for (int i = 1; i < 19; i++)
        jp[v][i] = jp[jp[v][i-1]][i-1];
    for (int u : tree[v])
        if (u != p)
            dfs(u,v);
}
int lca(int a, int b) { // binary lifting LCA
    if (dist[a] < dist[b])
        swap(a,b);
    for (int i = 18; i >= 0; i--)
        if (dist[jp[a][i]] >= dist[b])
            a = jp[a][i];
    if (a == b)
        return a;
    for (int i = 18; i >= 0; i--)
        if (jp[a][i] != jp[b][i])
            a = jp[a][i], b = jp[b][i];
    return jp[a][0];
}
