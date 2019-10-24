#include <bits/stdc++.h>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

typedef long long llint;

const string sym = "0123456789+-*/=";

string s, orig;

bool is_oper(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool bounds(llint x) {
  return x >= 1LL && x <= 1000000000LL;
}

bool check_format() {
  int oper_pos = -1, oper_cnt = 0, eq_pos = -1, eq_cnt = 0;
  for (int i = 0; i < s.size(); ++i) {
    if (is_oper(s[i])) { oper_pos = i; oper_cnt++; }
    if (s[i] == '=') { eq_pos = i; eq_cnt++; }
  }

  if (oper_cnt != 1 || eq_cnt != 1 || eq_pos < oper_pos) return false;

  string a = s.substr(0, oper_pos);
  string b = s.substr(oper_pos + 1, eq_pos - oper_pos - 1);
  string c = s.substr(eq_pos + 1);

  if (a.empty() || b.empty() || c.empty()) return false;
  if (a[0] == '0' || b[0] == '0' || c[0] == '0') return false;
  if (a.size() > 10 || b.size() > 10 || c.size() > 10) return false;

  llint A = stoll(a), B = stoll(b), C = stoll(c);
  if (!bounds(A) || !bounds(B) || !bounds(C)) return false;

  return true;
}

bool is_correct() {
  assert(check_format());
  int oper_pos = -1, eq_pos = -1;
  for (int i = 0; i < s.size(); ++i) {
    if (is_oper(s[i])) oper_pos = i;
    if (s[i] == '=') eq_pos = i;
  }

  string a = s.substr(0, oper_pos);
  string b = s.substr(oper_pos + 1, eq_pos - oper_pos - 1);
  string c = s.substr(eq_pos + 1);

  llint A = stoll(a), B = stoll(b), C = stoll(c);
  char oper = s[oper_pos];

  if (oper == '+') return A + B == C;
  if (oper == '-') return A - B == C;
  if (oper == '*') return A * B == C;
  if (oper == '/') return A == B * C;

  assert(false);
  return false;
}

int main(void) {
  cin >> s;
  orig = s;

  if (!check_format()) {
    cout << "Izraz nije ispravno formatiran\n";
    return 0;
  }

  if (is_correct()) {
    cout << "Tocno\n";
    return 0;
  }

  for (int i = 0; i < s.size(); ++i) {
    for (int j = 0; j < s.size(); ++j) {
      for (char ci : sym) {
        for (char cj : sym) {
          s[i] = ci; s[j] = cj;
          if (check_format() && is_correct()) {
            cout << "Netocno, umjesto " << orig << " mogli ste ispisati " << s
                 << "\n";
            return 0;
          }
          s = orig;
        }
      }
    }
  }

  cout << "Potpuno netocno\n";
  return 0;
}
