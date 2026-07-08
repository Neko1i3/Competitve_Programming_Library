// Solution to the classic farthest pair of points problem, using two-pointers on the convex hull.
#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,long long,long long> tp; // structure for a single point: (i,x,y)

int kier(tp a, tp b, tp c) { // determining relative angles using vector product
    long long v = get<1>(a)*(get<2>(b)-get<2>(c))+get<1>(b)*(get<2>(c)-get<2>(a))+get<1>(c)*(get<2>(a)-get<2>(b));
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}
bool cw(tp a, tp b, tp c) {
    return kier(a,b,c) < 0;
}
long long dist(tp a, tp b) { // (squared) distance between points
    return (get<1>(a)-get<1>(b))*(get<1>(a)-get<1>(b))+(get<2>(a)-get<2>(b))*(get<2>(a)-get<2>(b));
}
void convex_hull(vector<tp>& v) { // convex hull implementation
    tp p0 = *min_element(v.begin(), v.end(), [](tp a, tp b) {
        return make_pair(get<2>(a),get<1>(a)) < make_pair(get<2>(b),get<1>(b));
    });
    sort(v.begin(), v.end(), [&p0](const tp& a, const tp& b) { // anglesort
        int o = kier(p0,a,b);
        if (o == 0)
            return dist(p0,a) < dist(p0,b);
        return o < 0;
    });
    vector<tp> st; // classic algorithm for finding the convex hull using a stack
    for (int i = 0; i < v.size(); i++) {
        while (st.size() > 1 && !cw(st[st.size()-2], st.back(), v[i]))
            st.pop_back();
        st.push_back(v[i]);
    }
    v = st;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n,j = 1;
    cin >> n;
    vector<tp> v;
    long long a,b,ans = 0;
    for (int i = 0; i < n; i++)
        cin >> a >> b, v.push_back({i,a,b});
    convex_hull(v);
    for (int i = 0; i < n; i++) { // two pointers procedure to find the farthest pair of points
        while (dist(v[i],v[(j+1)%n]) > dist(v[i],v[j%n]))
            j++;
        ans = max(ans,dist(v[i],v[j%n]));
    }
    cout << ans << endl;
    return 0;
}
