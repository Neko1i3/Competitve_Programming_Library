// Implementation of a XOR basis
#include <bits/stdc++.h>
using namespace std;

int reduce(int x, int b[]) {
    for (int i = 29; i >= 0; i--)
        if (x&(1<<i))
            x ^= b[i];
    return x;
}
void add(int x, int b[]) {
    int r = reduce(x,b);
    if (r == 0)
        return;
    for (int i = 29; i >= 0; i--) {
        if (r&(1<<i)) {
            b[i] = r;
            break;
        }
    }
}
void unify(int b1[], int b2[]) { // merge b2 into b1
    for (int i = 0; i < 30; i++)
        add(b2[i],b1);
}
int maks(int b[]) { // maximum value stored in b
    int x = 0;
    for (int i = 29; i >= 0; i--)
        x = max(x,x^b[i]);
    return x;
}

