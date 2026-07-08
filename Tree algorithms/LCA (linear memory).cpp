// Calculating LCA with linear memory and precomputation time, query is still O(logn)
#include <bits/stdc++.h>
using namespace std;

const int maxn = (1<<19);
int n, parent[maxn], dist[maxn], jp[maxn];
vector<int> tree[maxn];

void dfs(int v, int p) { // precomputation
    parent[v] = p, dist[v] = dist[p]+1;
    if (v != 1)
        jp[v] = ((dist[p]+dist[jp[jp[p]]] == 2*dist[jp[p]]) ? jp[jp[p]] : p);
    for (int u : tree[v])
        if (u != p)
            dfs(u,v);
}
int jump(int v, int depth) { // jump form v to the given depth level
    while (dist[v] > depth)
        v = ((dist[jp[v]] < depth) ? parent[v] : jp[v]);
    return v;
}
int lca(int a, int b) { // LCA of a and b
    if (dist[a] < dist[b])
        swap(a,b);
    a = jump(a,dist[b]);
    while (a != b) {
        if (jp[a] == jp[b])
            a = parent[a], b = parent[b];
        else
            a = jp[a], b = jp[b];
    }
    return a;
}
