// We are given a tree with n vertices. Each vertice has a color numbered from 1 to maxn.
// We want to compute the virtual tree for every color.
// You need to clear the vtree structure before every call of virtual_tree()

#include <bits/stdc++.h>
using namespace std;

const int maxn = (1<<19);
int n, cc[maxn], czas, pp[maxn], ord[maxn][2], odl[maxn], jp[maxn], root;
vector<int> tree[maxn], vc[maxn], vivi;
vector<pair<int,int>> vtree[maxn];

bool por(int &a, int &b) {
    return (ord[a][0] < ord[b][0]);
}
// linear memory LCA
void dfs(int v, int p) {
    pp[v] = p, ord[v][0] = czas++, odl[v] = odl[p]+1;
    if (v != 1)
        jp[v] = ((odl[p]+odl[jp[jp[p]]] == 2*odl[jp[p]]) ? jp[jp[p]] : p);
    for (int u : tree[v])
        if (u != p)
            dfs(u,v);
    ord[v][1] = czas++;
}
int jump(int v, int depth) {
    while (odl[v] > depth)
        v = ((odl[jp[v]] < depth) ? pp[v] : jp[v]);
    return v;
}
int lca(int a, int b) {
    if (odl[a] < odl[b])
        swap(a,b);
    a = jump(a,odl[b]);
    while (a != b) {
        if (jp[a] == jp[b])
            a = pp[a], b = pp[b];
        else
            a = jp[a], b = jp[b];
    }
    return a;
}
// creating the virtual tree for the given color
void virtual_tree(int color) {
    vivi.clear(); vector<int> pom;
    for (int v : vc[color])
        vivi.push_back(v);
    sort(vivi.begin(),vivi.end(),por);
    for (int i = 1; i < vc[color].size(); i++)
        vivi.push_back(lca(vivi[i-1],vivi[i]));
    sort(vivi.begin(),vivi.end(),por), pom.push_back(vivi[0]), root = vivi[0];
    for (int i = 1; i < vivi.size(); i++) {
        if (vivi[i-1] == vivi[i])
            continue;
        while (ord[vivi[i]][1] > ord[pom.back()][1])
            pom.pop_back();
        vtree[pom.back()].push_back({vivi[i],odl[vivi[i]]-odl[pom.back()]}), pom.push_back(vivi[i]);
    }
    pom.clear();
    for (int i = 0; i < vivi.size(); i++)
        if (i == 0 || vivi[i] != vivi[i-1])
            pom.push_back(vivi[i]);
    vivi.clear();
    for (int i = 0; i < pom.size(); i++)
        vivi.push_back(pom[i]);
}
