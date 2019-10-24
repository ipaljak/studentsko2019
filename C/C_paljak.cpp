#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 3e5 + 10;

char col[MAXN];

int n, q;
int points[MAXN], loga[2][MAXN]; // 0 crni, 1 zuti

void add(int t, int i, int val) {
  for (; i < MAXN; i += i & -i) loga[t][i] += val;
}

int sum(int t, int lo, int hi) {
  int ret = 0;
  for (; hi > 0; hi -= hi & -hi) ret += loga[t][hi];
  for (--lo; lo > 0; lo -= lo & -lo) ret -= loga[t][lo];
  return ret;
}

int main(void) {
  scanf("%d%d", &n, &q);
  scanf("%s", col);

  for (int i = 0; i < n; ++i) {
    points[i] = 1;
    add(col[i] == 'C', 1, 1);
  }

  llint ceh = 0;
  for (int i = 0; i < q; ++i) {
    int a, b; scanf("%d%d", &a, &b); --a;
    int t = col[a] == 'C';

    if (t)
      ceh += (llint) sum(!t, points[a], points[a] + b - 1);
    else
      ceh -= (llint) sum(!t, points[a] + 1, points[a] + b);

    add(t, points[a], -1); points[a] += b;
    add(t, points[a], +1);

    printf("%lld\n", ceh);
  }
  return 0;
}
