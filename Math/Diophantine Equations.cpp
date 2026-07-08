// Solving linear diophantine equations (ax + by = c)
// tutorial on: https://cp-algorithms.com/algebra/linear-diophantine-equation.html
#include <bits/stdc++.h>
using namespace std;

int GCD(int a, int b, int& x, int& y) { // extended euclidean GCD
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    int x1, y1, d = GCD(b,a%b,x1,y1);
    x = y1, y = x1-y1*(a/b);
    return d;
}
bool solve(int a, int b, int c, int &x0, int &y0) { // finding one solution, we assume a,b != 0
    int g = GCD(abs(a),abs(b),x0,y0);
    if (c%g != 0)
        return false; // no solutions
    x0 *= c/g, y0 *= c/g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true; // (x0,y0) is a valid solution
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int a,b,c,x,y; // we aim to find x and y satisfying ax + by = c
    cin >> a >> b >> c;
    if (solve(a,b,c,x,y))
        cout << x << " " << y << endl;
    else
        cout << "NIE" << endl; // no solutions
    // all possible solutions will be of form: (x + k*(b/g), y - k*(a/g))
    return 0;
}
