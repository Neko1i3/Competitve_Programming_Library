// Custom bitset (no fixed size, but works really slowly)
#include <bits/stdc++.h>
using namespace std;
#define Bitset vector<unsigned long long>

void init(Bitset &bs, int n) { // creates an empty bitset of size n
    for (int i = 0; i < (n+63)/64; i++)
        bs.push_back(0);
}
void set_on(Bitset &bs, int i) { // set on the i-th bit
    bs[i>>6] |= (1ull<<(i&63));
}
void set_off(Bitset &bs, int i) { // set off the i-th bit
    bs[i>>6] &= ~(1ull<<(i&63));
}
void flip_bit(Bitset &bs, int i) { // flips the i-th bit
    bs[i>>6] ^= (1ull<<(i&63));
}
int bit_value(Bitset &bs, int i) { // returns the value of the i-th bit
    return ((bs[i>>6]&(1ull<<(i&63))) ? 1 : 0);
}
void init_string(Bitset &bs, string &s) { // creates a bitset from a binary string s
    int n = s.size();
    init(bs,n);
    for (int i = 0; i < n; i++) {
        if (s[i] == '1')
            set_on(bs,i);
        else
            set_off(bs,i);
    }
}
int bit_count(Bitset &bs) { // popcount
    int wynik = 0;
    for (int i = 0; i < bs.size(); i++)
        wynik += __builtin_popcountll(bs[i]);
    return wynik;
}
int first_bit(Bitset &bs) { // first bit set as 1 or -1 if there are none
    for (int i = 0; i < bs.size(); i++)
        if (bs[i] > 0)
            return i*64 + __builtin_ctzll(bs[i]);
    return -1;
}
int last_bit(Bitset &bs) { // last bit set as 1 or -1 if there are none
    for (int i = bs.size()-1; i >= 0; i--)
        if (bs[i] > 0)
            return (bs.size()-1-i)*64 + __builtin_clzll(bs[i]);
    return -1;
}
Bitset bitset_not(Bitset &bs, int n) { // bitset negation of a given bitset
    Bitset x;
    for (int i = 0; i < bs.size()-1; i++)
        x.push_back(~bs[i]);
    x.push_back(bs.back()^(ULLONG_MAX>>(64-(n&63))));
    return x;
}
Bitset bitset_and(Bitset &a, Bitset &b) { // AND of bitsets a,b
    Bitset x; assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++)
        x.push_back(a[i]&b[i]);
    return x;
}
Bitset bitset_or(Bitset &a, Bitset &b) { // OR of bitsets a,b
    Bitset x; assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++)
        x.push_back(a[i]|b[i]);
    return x;
}
Bitset bitset_xor(Bitset &a, Bitset &b) { // XOR of bitsets a,b
    Bitset x; assert(a.size() == b.size());
    for (int i = 0; i < a.size(); i++)
        x.push_back(a[i]^b[i]);
    return x;
}
Bitset shift_left(Bitset &bs, int k) { // left-shift a bitset by k positions
    Bitset x;
    for (int i = 0; i < bs.size(); i++)
        if (i >= k/64)
            x.push_back(bs[i]);
    while (x.size() < bs.size())
        x.push_back(0);
    k &= 63, x[0] >>= k;
    for (int i = 1; i < x.size(); i++)
        x[i-1] |= (x[i]<<(64-k)), x[i] >>= k;
    return x;
}
Bitset shift_right(Bitset &bs, int k, int n) { // right-shift a bitset by k positions
    Bitset x;
    for (int i = 0; i < k/64; i++)
        x.push_back(0);
    for (int i = 0; x.size() < bs.size(); i++)
        x.push_back(bs[i]);
    k &= 63, x.back() <<= k;
    for (int i = x.size()-1; i >= 0; i--)
        x[i+1] |= (x[i]>>(64-k)), x[i] <<= k;
    x.back() &= (1ull>>(64-(n&63)));
    return x;
}
void print(Bitset &bs) { // print out the given bitset
    for (int i = 0; i < bs.size(); i++)
        for (int j = 0; j < 64; j++)
            cerr << ((bs[i]&(1ull<<j)) ? '1' : '0');
    cerr << endl;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    return 0;
}
