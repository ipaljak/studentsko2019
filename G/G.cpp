#include<bits/stdc++.h>

using namespace std;

const int MAXN = 1000005;

int n;
int v[2][MAXN];
int col[MAXN];

void spoji (int a, int b) {
    v[v[0][a] != 0][a] = b;
    v[v[0][b] != 0][b] = a;
}

void dfs (int x, int c) {
    col[x] = c;
    if (col[v[0][x]] == -1) dfs(v[0][x], !c);
    if (col[v[1][x]] == -1) dfs(v[1][x], !c);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i=0; i<n; i++) {
        int a, b;
        cin >> a >> b;
        spoji(a, b);
    }

    for (int i = 1; i <= n; i++) {
        spoji(2 * i - 1, 2 * i);
    }

    memset(col, -1, sizeof col);
    for (int i = 1; i <= 2 * n; i++) {
        if (col[i] == -1) dfs(i, 0);
    }

    for (int i = 1; i <= 2 * n; i++) {
        cout << (col[i] == 0 ? 'A' : 'B');
    }
    return 0;
}
