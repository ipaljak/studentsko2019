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

int get_size(int last_id) {
  int ret = 0;
  for (int i = 0; i < last_id; ++i)
    ret += cnt[v[i] - 'A'] - (cnt[v[i] - 'A'] % 3);
  ret += cnt[v[last_id] - 'A'];
  return ret;
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

  int last_id = 0, sol_size = get_size(0);
  for (int i = 1; i < (int) v.size(); ++i) {
    int curr_size = get_size(i);
    if (curr_size > sol_size) {
      sol_size = curr_size;
      last_id = i;
    }
  }

  for (int i = 0; i < last_id; ++i)
    cnt[v[i] - 'A'] -= cnt[v[i] - 'A'] % 3;

  for (int i = 0; i <= last_id; ++i)
    for (int j = 0; j < cnt[v[i] - 'A']; ++j)
      sol.push_back(v[i]);

  printf("%d", (int) sol.size());
  for (int i = 0; i < (int) sol.size(); ++i) {
    if (i % 3 == 0) printf("\n");
    printf("%c", sol[i]);
  }
  printf("\n");

  return 0;
}
