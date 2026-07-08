// Given a graph, find its arbitrary Minimum Spanning Tree
// Here I'm using Kruskal's algorithm
#include <bits/stdc++.h>
using namespace std;

int f(int x, int uf[][2]) { // Find in O(alpha(n))
    if (uf[x][0] != x)
        uf[x][0] = f(uf[x][0],uf);
    return uf[x][0];
}
void unify(int a, int b, int uf[][2]) { // Union in O(1)
    if (uf[a][1] <= uf[b][1])
        uf[a][0] = b, uf[b][1] += ((uf[a][1] == uf[b][1]) ? 1 : 0);
    else
        uf[b][0] = a;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,m; cin >> n >> m;
    tuple<int,int,int> edg[m]; // list of edges
    for (int i = 0; i < m; i++)
        cin >> get<1>(edg[i]) >> get<2>(edg[i]) >> get<0>(edg[i]);
    int uf[n+1][2]; vector<pair<int,int>> mst[n+1]; // Union-Find array, structure to hold the MST
    for (int i = 1; i <= n; i++)
        uf[i][0] = i, uf[i][1] = 0;
    sort(edg,edg+m);
    for (int i = 0; i < m; i++) { // classic Kruskal implementation
        int u = get<1>(edg[i]), v = get<2>(edg[i]), c = get<0>(edg[i]);
        if (f(u,uf) != f(v,uf))
            mst[u].push_back({v,c}), mst[v].push_back({u,c}), unify(f(u,uf),f(v,uf),uf);
    }
    return 0;
}
