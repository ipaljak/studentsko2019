#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const int MAXN = 1e5 + 10;

int n;
int cnt[26];

vector<char> v, sol;

inline int ceil(int a, int b) {
  return (a + b - 1) / b;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < ceil(n, 3); ++i) {
    char x[5];
    scanf("%s", x);
    for (int j = 0; j < strlen(x); ++j) {
      ++cnt[x[j] - 'A'];
      v.push_back(x[j]);
    }
  }

  v.erase(unique(v.begin(), v.end()), v.end());
  for (int i = 0; i < v.size() - 1; ++i)
    cnt[v[i] - 'A'] -= cnt[v[i] - 'A'] % 3;

  for (char c : v)
    for (int i = 0; i < cnt[c - 'A']; ++i)
      sol.push_back(c);

  printf("%d", (int) sol.size());
  for (int i = 0; i < (int) sol.size(); ++i) {
    if (i % 3 == 0) printf("\n");
    printf("%c", sol[i]);
  }
  printf("\n");

  return 0;
}
