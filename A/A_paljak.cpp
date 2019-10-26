#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1e5 + 10;

struct edge {
  int a, b, w;
  edge(int _a, int _b, int _w) : a(_a), b(_b), w(_w) {}
  friend bool operator<(const edge &a, const edge &b) {
    return a.w > b.w;
  }
};

int n;
int sz[MAXN], dad[MAXN];

vector<edge> e;

inline void init() {
  for (int i = 0; i < n; ++i) {
    sz[i] = 1;
    dad[i] = i;
  }
}

int find_set(int a) {
  if (a == dad[a]) return a;
  return dad[a] = find_set(dad[a]);
}

void unite(int a, int b) {
  int pa = find_set(a), pb = find_set(b);
  if (pa == pb) return;
  dad[pa] = pb;
  sz[pb] += sz[pa];
}

int main(void) {
  scanf("%d", &n); init();
  for (int i = 0; i < n - 1; ++i) {
    int a, b, w;
    scanf("%d%d%d", &a, &b, &w); --a; --b;
    e.emplace_back(a, b, w);
  }

  sort(e.begin(), e.end());

  llint sol = 0;
  for (const auto &ei : e) {
    unite(ei.a, ei.b);
    int pa = find_set(ei.a);
    sol = max(sol, (llint) (sz[pa] - 1) * ei.w);
  }

  printf("%lld\n", sol);
  return 0;
}
