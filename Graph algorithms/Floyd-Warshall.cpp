// Finding the minimum average of weights on a path using the Floyd-Warshall algorithm
#include <bits/stdc++.h>
using namespace std;

const int inf = 1000000000;
bool is_neg(double x, int n, int m, tuple<int,int,double> G[]) { // looking for a negative cycle using Floyd-Warshall
    double dp[n+1][n+1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            dp[i][j] = inf;
        dp[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
        dp[get<0>(G[i])][get<1>(G[i])] = x-get<2>(G[i]);
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++)
                if (dp[i][k] != inf && dp[k][j] != inf && dp[i][j] > dp[i][k]+dp[k][j])
                    dp[i][j] = dp[i][k]+dp[k][j];
        }
    }
    for (int i = 1; i <= n; i++)
        if (dp[i][i] < 0)
            return true;
    return false;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    tuple<int,int,double> G[m];
    for (int i = 0; i < m; i++)
        cin >> get<0>(G[i]) >> get<1>(G[i]) >> get<2>(G[i]);
    double p = 0, k = 100000, eps = pow(10,-7);
    while (k-p >= eps) { // binary searching the answer
        double s = (p+k)/2;
        if (is_neg(s,n,m,G))
            p = s+eps;
        else
            k = s;
    }
    cout << fixed << setprecision(7) << p << endl;
    return 0;
}
