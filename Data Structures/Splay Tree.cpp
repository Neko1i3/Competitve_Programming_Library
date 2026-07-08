// Ordered Multiset implementation using a Splay Tree
// I cannot be bothered to translate this into English...
// problem link: https://judge.yosupo.jp/problem/ordered_set
/*
Lista rzeczy do zrobienia:

1. zamieniæ funkcjê splay na swego rodzaju reroot poddrzewa
2. lazy propagation + funkcja balance, reroot, reverse i czego sobie dusza za¿yczy...
3. zamieniæ rekurencjê na schodzenie w dó³ od korzenia
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = (1<<20), inf = 2000000000;
bool start = true;
struct splay_tree {
    int m = 1, x[maxn], y[maxn], s[maxn], h[maxn], w[maxn][2], rozm = 0;
    long long ss[maxn];
};
splay_tree spt;
void init(int n) {
    for (int i = 0; i < spt.m; i++)
        spt.x[i] = spt.y[i] = spt.s[i] = spt.h[i] = spt.w[i][0] = spt.w[i][1] = 0;
    if (start) {
        for (int i = spt.m; i < maxn; i++)
            spt.x[i] = spt.y[i] = spt.s[i] = spt.h[i] = spt.w[i][0] = spt.w[i][1] = 0;
        start = false;
    }
    spt.x[1] = n, spt.w[0][0] = spt.y[1] = spt.s[1] = spt.h[1] = spt.rozm = 1, spt.m = 2, spt.ss[1] = 1ll*n;
}
void mod(int v) {
    spt.s[v] = spt.y[v]+spt.s[spt.w[v][0]]+spt.s[spt.w[v][1]], spt.h[v] = max(spt.h[spt.w[v][0]],spt.h[spt.w[v][1]])+1, spt.ss[v] = 1ll*spt.x[v]*spt.y[v]+spt.ss[spt.w[v][0]]+spt.ss[spt.w[v][1]];
}
void splay(int v, int &p) {
    int l = spt.w[v][0], r = spt.w[v][1];
    if (abs(spt.h[l]-spt.h[r]) <= 1)
        return;
    if (spt.h[l] > spt.h[r]) {
        int a = spt.w[l][0], b = spt.w[l][1];
        if (spt.h[a] > spt.h[b])
            spt.w[v][0] = spt.w[l][1], spt.w[l][1] = v, p = l, mod(v), mod(l);
        else
            spt.w[l][1] = spt.w[b][0], spt.w[v][0] = spt.w[b][1], spt.w[b][0] = l, spt.w[b][1] = v, p = b, mod(v), mod(l), mod(b);
    }
    else {
        int a = spt.w[r][0], b = spt.w[r][1];
        if (spt.h[a] > spt.h[b])
            spt.w[r][0] = spt.w[a][1], spt.w[v][1] = spt.w[a][0], spt.w[a][0] = v, spt.w[a][1] = r, p = a, mod(v), mod(r), mod(a);
        else
            spt.w[v][1] = spt.w[r][0], spt.w[r][0] = v, p = r, mod(v), mod(r);
    }
}
void add(int v, int &p, int d) { // dodaje element
    if (spt.x[v] == d)
        spt.y[v]++, spt.rozm++;
    else if (spt.x[v] > d) {
        if (spt.w[v][0] == 0)
            spt.w[v][0] = spt.m, spt.x[spt.m] = d, spt.y[spt.m] = spt.s[spt.m] = spt.h[spt.m] = 1, spt.m++, spt.rozm++;
        else
            add(spt.w[v][0],spt.w[v][0],d);
    }
    else {
        if (spt.w[v][1] == 0)
            spt.w[v][1] = spt.m, spt.x[spt.m] = d, spt.y[spt.m] = spt.s[spt.m] = spt.h[spt.m] = 1, spt.m++, spt.rozm++;
        else
            add(spt.w[v][1],spt.w[v][1],d);
    }
    mod(v), splay(v,p);
}
void drop(int v, int z, int &p) {
    int l = spt.w[v][0], r = spt.w[v][1];
    if (spt.x[v] < spt.x[z]) {
        if (r != 0)
            drop(r,z,spt.w[v][1]);
        else
            spt.x[z] = spt.x[v], spt.y[z] = spt.y[v], p = l;
    }
    else {
        if (l != 0)
            drop(l,z,spt.w[v][0]);
        else
            spt.x[z] = spt.x[v], spt.y[z] = spt.y[v], p = r;
    }
    mod(v);
}
void take(int v, int &p, int d) { // wyjmuje element
    int l = spt.w[v][0], r = spt.w[v][1];
    if (spt.x[v] == d) {
        spt.rozm--;
        if (--spt.y[v] == 0) {
            if (max(l,r) == 0)
                p = 0;
            else if (l != 0)
                drop(l,v,spt.w[v][0]);
            else
                drop(r,v,spt.w[v][1]);
        }
    }
    else if (spt.x[v] > d)
        take(l,spt.w[v][0],d);
    else
        take(r,spt.w[v][1],d);
    mod(v), splay(v,p);
}
int ind(int v, int d) { // zwraca indeks szukanego elementu lub 0 je¿eli element nie istnieje
    if (v == 0 || spt.rozm == 0)
        return 0;
    if (spt.x[v] == d)
        return v;
    if (spt.x[v] > d)
        return ind(spt.w[v][0],d);
    else
        return ind(spt.w[v][1],d);
}
int cnt(int d) { // ile elementów jest niemniejszych od d
    int v = spt.w[0][0], wynik = 0;
    while (v != 0 && spt.rozm != 0) {
        if (spt.x[v] <= d)
            wynik += spt.s[spt.w[v][0]]+1, v = spt.w[v][1];
        else
            v = spt.w[v][0];
    }
    return wynik;
}
int up(int v, int d) { // pierwszy wiêkszy
    if (v == 0 || spt.rozm == 0)
        return -inf;
    if (spt.x[v] <= d)
        return up(spt.w[v][1],d);
    else {
        int z = up(spt.w[v][0],d), wynik = ((z > d) ? z : spt.x[v]);
        return ((wynik > d) ? wynik : -inf);
    }
}
int down(int v, int d) { // ostatni mniejszy
    if (v == 0 || spt.rozm == 0)
        return inf;
    if (spt.x[v] >= d)
        return down(spt.w[v][0],d);
    else {
        int z = down(spt.w[v][1],d), wynik = ((z < d) ? z : spt.x[v]);
        return ((wynik < d) ? wynik : inf);
    }
}
int ord(int v, int z) { // z-ty najmniejszy element
    int l = spt.w[v][0], r = spt.w[v][1];
    if (spt.y[v]+spt.s[l] >= z && spt.s[l] < z)
        return spt.x[v];
    else if (spt.s[l] >= z)
        return ord(l,z);
    else
        return ord(r,z-(spt.y[v]+spt.s[l]));
}
int prw(int v) {
    int l = spt.w[v][0], r = spt.w[v][1];
    if (l == 0 && r == 0)
        return v;
    else if (l > 0)
        return prw(l);
    else
        return prw(r);
}
int ost(int v) {
    int l = spt.w[v][0], r = spt.w[v][1];
    if (l == 0 && r == 0)
        return v;
    else if (r > 0)
        return prw(r);
    else
        return prw(l);
}
long long sum(int v, int z) { // suma pierwszych z elementów
    int l = spt.w[v][0], r = spt.w[v][1];
    if (spt.y[v]+spt.s[l] >= z && spt.s[l] < z)
        return 1ll*spt.x[v]*(z-spt.s[l]) + spt.ss[l];
    else if (spt.s[l] >= z)
        return sum(l,z);
    else
        return spt.ss[v]-spt.ss[r] + sum(r,z-(spt.y[v]+spt.s[l]));
}
void print() {
    cerr << "ROOT: " << spt.w[0][0] << " " << spt.rozm << endl;
    for (int i = 1; i < spt.m; i++)
        cerr << spt.x[i] << " " << spt.w[i][0] << " " << spt.w[i][1] << " " << spt.s[i] << endl;
}
void check(int v) {
    if (v == 0)
        return;
    assert(spt.s[spt.w[0][0]] == spt.rozm);
    assert(spt.w[v][0] == 0 || spt.x[v] > spt.x[spt.w[v][0]]);
    assert(spt.w[v][1] == 0 || spt.x[v] < spt.x[spt.w[v][1]]);
    assert(spt.s[v] == spt.s[spt.w[v][0]]+spt.s[spt.w[v][1]]+1);
    check(spt.w[v][0]), check(spt.w[v][1]);
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int n,q; cin >> n >> q;
    int a[n],t,x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (i == 0)
            init(a[0]);
        else if (ind(spt.w[0][0],a[i]) == 0)
            add(spt.w[0][0],spt.w[0][0],a[i]);
    }
    for (int i = 0; i < q; i++) {
        cin >> t >> x;
        if (t == 0 && ind(spt.w[0][0],x) == 0) {
            if (spt.rozm == 0)
                init(x);
            else
                add(spt.w[0][0],spt.w[0][0],x);
        }
        else if (t == 1 && ind(spt.w[0][0],x) != 0)
            take(spt.w[0][0],spt.w[0][0],x);
        else if (t == 2) {
            if (spt.rozm < x)
                cout << -1 << endl;
            else
                cout << ord(spt.w[0][0],x) << endl;
        }
        else if (t == 3)
            cout << cnt(x) << endl;
        else if (t == 4) {
            if (ind(spt.w[0][0],x) != 0)
                cout << x << endl;
            else {
                int odp = down(spt.w[0][0],x);
                cout << ((odp == inf) ? -1 : odp) << endl;
            }
        }
        else if (t == 5) {
            if (ind(spt.w[0][0],x) != 0)
                cout << x << endl;
            else {
                int odp = up(spt.w[0][0],x);
                cout << ((odp == -inf) ? -1 : odp) << endl;
            }
        }
    }
    return 0;
}
