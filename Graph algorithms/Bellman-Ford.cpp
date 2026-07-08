// Shortest paths using the Bellman-Ford algorithm in O(V*E) for every query
#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,q;
    cin >> n >> m >> q;
    tuple<int, int, int> G[m]; // weighted graph, kept as a list of edges
    for (int i = 0; i < m; i++)
        cin >> get<0>(G[i]) >> get<1>(G[i]) >> get<2>(G[i]);
    for (int i = 0; i < q; i++) {
        int u,v,predecessors[n+1],dist[n+1];
        cin >> u >> v; // query for the shortest path from u to v
        for (int i = 1; i <= n; i++)
            dist[i] = inf;
        dist[u] = 0;
        for (int i = 0; i < n-1; i++) { // classic Bellman-Ford
            for (auto k : G) {
                if (dist[get<0>(k)] != inf && dist[get<0>(k)] + get<2>(k) < dist[get<1>(k)]) { // relaxation
                    dist[get<1>(k)] = dist[get<0>(k)] + get<2>(k);
                    predecessors[get<1>(k)] = get<0>(k);
                }
            }
        }
        if (dist[v] == inf) // when there's no path from u to v
            cout << "NIE" << endl;
        else { // finding the shortest path
            predecessors[u] = 0;
            vector<int> path;
            int x = v;
            while (x != 0) {
                path.push_back(x);
                x = predecessors[x];
            }
            cout << dist[v] << " " << path.size() << " ";
            for (int i = path.size()-1; i > -1; i--)
                cout << path[i] << " ";
            cout << endl;
        }
    }
    return 0;
}
