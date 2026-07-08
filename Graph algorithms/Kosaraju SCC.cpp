// Template for finding SCC using Kosaruju's algorithm
#include <bits/stdc++.h>
using namespace std:

void dfs(int v, int z, bool t, bool vis[], int scc[], vector<int> &s, vector<int> g[]) { // z is the current SCC root
    vis[v] = true;
    for (int u : g[v])
        if (!vis[u])
            dfs(u,z,t,vis,scc,s,g);
    if (!t) // first run, filling the postorder stack
        s.push_back(v);
    else // second run, computing scc
        scc[v] = z;
}
void SCC(int n, int scc[], vector<int> g[]) { // given a graph (adjacency list), compute the SCC array
    vector<int> s; bool vis[n];
    fill(vis,vis+n,false);
    for (int i = 0; i < n; i++)
        if (!vis[i])
            dfs(i,i,0,vis,scc,s,g);
    vector<int> rev[n]; // reversed graph
    for (int i = 0; i < n; i++)
        for (int j : g[i])
            rev[j].push_back(i);
    fill(vis,vis+n,false);
    for (int i = n-1; i >= 0; i--)
        if (!vis[s[i]])
            dfs(s[i],n-i-1,1,vis,scc,s,rev);
}
