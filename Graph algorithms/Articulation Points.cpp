// Solution to the problem "Blokada" from the XV Polish OI
// Main part of the solution is finding articulation points of a graph, here I'm using Tarjan's algorithm
#include <bits/stdc++.h>
using namespace std;

int t = 0;
void dfs(int v, int p, int tin[], int low[], long long ssize[], long long cnt[], bool visited[], int n, vector<int> G[]) {
    visited[v] = true;
    tin[v] = low[v] = t++;
    long long children = 0, cnt2 = 0; // number of children in the DFS tree, number of vertices dependent on v
    for (int u : G[v]) {
        if (u == p)
            continue;
        else if (visited[u])
            low[v] = min(low[v],tin[u]);
        else {
            dfs(u,v,tin,low,ssize,cnt,visited,n,G);
            ssize[v] += ssize[u];
            low[v] = min(low[v],low[u]);
            if (low[u] >= tin[v] && p != 0) {
                cnt2 += ssize[u];
                cnt[v] += ssize[u]*(n-ssize[u]-1);
            }
            children++;
        }
    }
    cnt[v] += (n-cnt2-1)*cnt2;
    if (p == 0 && children > 1) { // if the root (v == 1) is an articulation point
        for (int u : G[v])
            cnt[v] += ssize[u]*(n-ssize[u]-1);
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<int> G[n+1]; // the given graph as an adjacency list
    for (int i = 0; i < m; i++) {
        int a,b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    int tin[n+1], low[n+1]; // times of entry, the low function
    long long ssize[n+1], cnt[n+1]; // DFS-subtree size, the answer array
    bool visited[n+1]; // visited array
    for (int v = 1; v <= n; v++) { // initialization
        low[v] = 1000000000;
        ssize[v] = 1;
        cnt[v] = 2*(n-1);
        visited[v] = false;
    }
    dfs(n,0,tin,low,ssize,cnt,visited,n,G); // solving in one DFS
    for (int i = 1; i <= n; i++)
        cout << cnt[i] << endl;
    return 0;
}
