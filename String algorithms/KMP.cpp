// KMP implementation + finding all pattern occurences in the string s
#include <bits/stdc++.h>
using namespace std;

void LPS(string pat, int m, int lps[]) { // computing the LPS array
    int dl = 0, i = 1; lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[dl])
            lps[i] = ++dl, i++;
        else {
            if (dl != 0)
                dl = lps[dl-1];
            else
                lps[i] = dl, i++;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int m,n; string pat,s;
    cin >> m >> n >> pat >> s;
    int lps[m], j = 0, res = 0, i = 0;
    LPS(pat,m,lps);
    while (i < n) { // classic KMP implementation
        if (pat[j] == s[i])
            j++, i++;
        if (j == m)
            cout << i-j+1 << endl, j = lps[j-1], res++;
        else if (i < n && pat[j] != s[i]) {
            if (j != 0)
                j = lps[j-1];
            else
                i++;
        }
    }
    return 0;
}
