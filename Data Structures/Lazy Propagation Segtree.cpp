// Solution to a simple problem of range addition + range minimum using a segment tree
#include <bits/stdc++.h>
using namespace std;

void push(int v, long long d[][2]) { // push down the lazy value
    if (d[v][1] == 0)
        return;
    d[2*v][0] += d[v][1], d[2*v+1][0] += d[v][1];
    d[2*v][1] += d[v][1], d[2*v+1][1] += d[v][1];
    d[v][1] = 0;
}
void upd(int a, int b, long long x, int v, int l, int r, long long d[][2]) { // add x on the [a,b] range
    if (r < a || l > b)
        return;
    if (l >= a && r <= b)
        d[v][0] += x, d[v][1] += x;
    else {
        push(v,d);
        upd(a,b,x,2*v,l,(l+r)/2,d);
        upd(a,b,x,2*v+1,(l+r)/2+1,r,d);
        d[v][0] = min(d[2*v][0],d[2*v+1][0]);
    }
}
long long mini(int a, int b, int v, int l, int r, long long d[][2]) { // compute minimum on the [a,b] range
    if (r < a || l > b)
        return 1000000000000000000;
    if (l >= a && r <= b)
        return d[v][0];
    else {
        push(v,d);
        return min(mini(a,b,2*v,l,(l+r)/2,d),mini(a,b,2*v+1,(l+r)/2+1,r,d));
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,m,a,b;
    cin >> n >> m;
    long long baza = pow(2,ceil(log2(n+1))), d[2*baza][2], x; // dynamic alloc because I was young and foolish
    for (int i = 0; i < 2*baza; i++)
        d[i][0] = d[i][1] = 0;
    for (int i = 0; i < m; i++) {
        string s;
        cin >> s >> a >> b;
        if (s == "budowa") { // update
            cin >> x;
            if (a <= b)
                upd(a,b,x,1,0,baza-1,d);
            else
                upd(1,b,x,1,0,baza-1,d), upd(a,n,x,1,0,baza-1,d);
        }
        else { // query
            if (a <= b)
                cout << mini(a,b,1,0,baza-1,d) << endl;
            else
                cout << min(mini(1,b,1,0,baza-1,d),mini(a,n,1,0,baza-1,d)) << endl;
        }
    }
    return 0;
}
