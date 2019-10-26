#include<bits/stdc++.h>

using namespace std;

#define X first
#define Y second

typedef long long llint;
typedef pair <int, int> pi;
typedef pair <llint, llint> pii;

const int MAXN = 200005;

int n;
int h[MAXN], par[MAXN];
llint sol[MAXN];
vector <int> v[MAXN];
pii hull[MAXN];

void build_tree () {
    vector <pi> st;
    st.push_back({0, 0});
    for (int i = 1; i <= n; i++) {
        while (st.back().first >= h[i]) st.pop_back();
        par[i] = st.back().second;
        v[par[i]].push_back(i);
        st.push_back({h[i], i});
    }
}

inline llint f (pii p, int t) {
    return p.first * t + p.second;
}

inline bool ccw (pii a, pii b, pii c) {
    return a.X * (b.Y - c.Y) + b.X * (c.Y - a.Y) + c.X * (a.Y - b.Y) >= 0;
}

int ubaci (int x, int pos) {
    pii tmp = {h[x], -1LL * h[x] * par[x]};
    int lo = 0, hi = pos - 1;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (ccw(hull[mid], hull[mid + 1], tmp)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return hi + 1;
}

llint upit (int x, int pos) {
    int lo = 0, hi = pos;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (f(hull[mid], x) >= f(hull[mid + 1], x)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    return f(hull[lo], x);
}

void solve (int x, int pos) {
    pos = ubaci(x, pos);
    pii bk = hull[pos];
    hull[pos] = {h[x], -1LL * h[x] * par[x]};
    sol[x] = upit(x, pos);

    for (auto sus : v[x]) {
        solve(sus, pos + 1);
    }
    hull[pos] = bk;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }
    build_tree();
    solve(0, 0);
    for (int i = 1; i <= n; i++) {
        sol[i] = max(sol[i], sol[i - 1]);
        cout << sol[i] << " ";
    }
    return 0;
}
