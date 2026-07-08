// My solution to the codeforces problem "Frequency of String" (https://codeforces.com/contest/963/problem/D), using the Aho-Corasick algorithm.
#include <bits/stdc++.h>
using namespace std;

int q, n = 1, trie[1<<17][26], link[1<<17], skip[1<<17], out[1<<17], k[1<<17], d[1<<17];
vector<int> tab[1<<17];
void add(string &s, int i) { // adding the string s to the trie
    int v = 0;
    for (char c : s) {
        if (trie[v][c-'a'] == 0)
            trie[v][c-'a'] = n++;
        v = trie[v][c-'a'];
    }
    out[v] = i;
}
void build() { // completing the Aho-Corasick trie
    queue<int> q;
    for (int i = 0; i < 26; i++)
        if (trie[0][i] != 0)
            link[trie[0][i]] = 0, q.push(trie[0][i]);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (trie[v][i] == 0)
                trie[v][i] = trie[link[v]][i];
            else
                link[trie[v][i]] = trie[link[v]][i], skip[trie[v][i]] = ((out[link[trie[v][i]]] != 0) ? link[trie[v][i]] : skip[link[trie[v][i]]]), q.push(trie[v][i]);
        }
    }
}
void jump(int v, int x) {
    if (v == 0)
        return;
    if (out[v] != 0)
        tab[out[v]].push_back(x);
    jump(skip[v],x);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    string s,z;
    cin >> s >> q;
    for (int i = 1; i <= q; i++)
        cin >> k[i] >> z, d[i] = z.size(), add(z,i);
    build();
    int v = 0;
    for (int i = 0; i < s.size(); i++)
        v = trie[v][s[i]-'a'], jump(v,i);
    for (int i = 1; i <= q; i++) {
        if (k[i] > tab[i].size())
            cout << -1 << endl;
        else {
            int odp = 1000000000;
            for (int j = k[i]-1; j < tab[i].size(); j++)
                odp = min(odp,tab[i][j]-tab[i][j-k[i]+1]+d[i]);
            cout << odp << endl;
        }
    }
    return 0;
}
