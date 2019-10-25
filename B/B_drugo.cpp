#include<bits/stdc++.h>

using namespace std;

const int MAXN = 40005;
const int SIZ = 300;
const int INF = 1000000007;

int n, q, ofs = 1, curr_lef, curr_rig;
int p[MAXN], lef[MAXN], rig[MAXN], qs[MAXN], sol[MAXN];
int ll[4 * MAXN], rr[4 * MAXN], t[4 * MAXN];

bool cmp (int a, int b) {
    if (lef[a] / SIZ != lef[b] / SIZ) return lef[a] < lef[b];
    return rig[a] < rig[b];
}

void update (int pos, int val) {
    pos += ofs;
    if (val == 0) {
        ll[pos] = INF; rr[pos] = -INF;
    } else {
        ll[pos] = rr[pos] = pos;
    }
    pos >>= 1;
    while (pos > 0) {
        ll[pos] = min(ll[pos * 2], ll[pos * 2 + 1]);
        rr[pos] = max(rr[pos * 2], rr[pos * 2 + 1]);
        t[pos] = min(ll[pos * 2 + 1] - rr[pos * 2], min(t[pos * 2], t[pos * 2 + 1]));
        pos >>= 1;
    }
}

void ltol () {curr_lef--; update(p[curr_lef], 1);}
void rtor () {curr_rig++; update(p[curr_rig], 1);}
void ltor () {update(p[curr_lef], 0); curr_lef++;}
void rtol () {update(p[curr_rig], 0); curr_rig--;}

void rjesi () {
    curr_lef = curr_rig = 1;
    update(p[1], 1);
    for (int i = 0; i < q; i++) {
        int ind = qs[i];
        while (lef[ind] < curr_lef) ltol();
        while (curr_rig < rig[ind]) rtor();
        while (curr_lef < lef[ind]) ltor();
        while (rig[ind] < curr_rig) rtol();
        sol[ind] = t[1];
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    while (ofs < n + 1) ofs *= 2;
    for (int i = 0; i < 2*ofs; i++) {
        t[i] = INF; ll[i] = INF; rr[i] = -INF;
    }
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < q; i++) {
        cin >> lef[i] >> rig[i];
        qs[i] = i;
    }
    sort(qs, qs + q, cmp);
    rjesi();
    for (int i = 0; i < q; i++) {
        cout << sol[i] << '\n';
    }
    return 0;
}
