// PAZI OVO NIJE OK ZA CMS EVALUATOR
//
// Checker to be used by HSIN evaluator.
//
// Usage: [checker] [input] [official_output] [contestant_output]
//
// Score (real between 0.0 and 1.0) written on stdout.
// Textual description of the result written on stderr.

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

typedef long long llint;

/**
 * @param p fraction of points awarded to the contestant.
 * @pararm m error message displayed to the contestant.
 */
void finish(double p, const string& m);

vector<string> split(const string &a, const string& delim) {
  vector<string> ans;
  int ptr = 0;
  for (size_t f_pos; (f_pos = a.find(delim, ptr)) != string::npos; ) {
    ans.push_back(a.substr(ptr, f_pos - ptr));
    ptr = f_pos + delim.size();
  }
  ans.push_back(a.substr(ptr));
  return ans;
}

const string sym = "0123456789+-*/=";

const string UNEXPECTED_ERROR = "Unexpected error - report via clarification request";
const string WRONG = "Wrong answer";
const string CORRECT = "Accepted";

bool is_oper(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

bool bounds(llint x) {
  return x >= 1LL && x <= 1000000000LL;
}

bool check_expression(const string &in_expr, const string &user_expr) {
  if (in_expr.size() != user_expr.size()) return false;
  for (char c : user_expr)
    if (find(sym.begin(), sym.end(), c) == sym.end())
      return false;

  int diff_cnt = 0;
  for (int i = 0; i < (int) in_expr.size(); ++i)
    diff_cnt += in_expr[i] != user_expr[i];

  if (diff_cnt > 2) return false;

  int oper_pos = -1, oper_cnt = 0, eq_pos = -1, eq_cnt = 0;
  for (int i = 0; i < user_expr.size(); ++i) {
    if (is_oper(user_expr[i])) { oper_pos = i; oper_cnt++; }
    if (user_expr[i] == '=') { eq_pos = i; eq_cnt++; }
  }

  if (oper_cnt != 1 || eq_cnt != 1 || eq_pos < oper_pos) return false;

  string a = user_expr.substr(0, oper_pos);
  string b = user_expr.substr(oper_pos + 1, eq_pos - oper_pos - 1);
  string c = user_expr.substr(eq_pos + 1);

  if (a.empty() || b.empty() || c.empty()) return false;
  if (a[0] == '0' || b[0] == '0' || c[0] == '0') return false;
  if (a.size() > 10 || b.size() > 10 || c.size() > 10) return false;

  llint A = stoll(a), B = stoll(b), C = stoll(c);
  if (!bounds(A) || !bounds(B) || !bounds(C)) return false;

  char oper = user_expr[oper_pos];
  if (oper == '+') return A + B == C;
  if (oper == '-') return A - B == C;
  if (oper == '*') return A * B == C;
  if (oper == '/') return A == B * C;

  finish(0, UNEXPECTED_ERROR);
  return false;
}

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream& fin, ifstream& foff, ifstream& fout) {

  // Read official input
  string expr;

  if (!(fin >> expr)) finish(0, UNEXPECTED_ERROR);

  // Read official output
  vector<string> official_out;

  string official_first;
  if (!(foff >> official_first)) finish(0, UNEXPECTED_ERROR);
  official_out.push_back(official_first);

  if (official_first != "Tocno" &&
      official_first != "Izraz" &&
      official_first != "Netocno," &&
      official_first != "Potpuno") finish(0, UNEXPECTED_ERROR);

  map<string, int> m;
  m["Tocno"] = 0;
  m["Izraz"] = 3;
  m["Netocno,"] = 6;
  m["Potpuno"] = 1;

  for (int i = 0; i < m[official_first]; ++i) {
    string word;
    if (!(foff >> word)) finish(0, UNEXPECTED_ERROR);
    official_out.push_back(word);
  }

  // Read contestant's output
  vector<string> contestant_out;

  for (int i = 0; i < (int) official_out.size(); ++i) {
    string word;
    if (!(fout >> word)) finish(0, WRONG);
    contestant_out.push_back(word);
  }

  string trash;
  if (fout >> trash) finish(0, WRONG);

  // Trivijala, samo usporedi vektore
  if (official_first != "Netocno,") {
    for (int i = 0; i < (int) official_out.size(); ++i)
      if (official_out[i] != contestant_out[i])
        finish(0, WRONG);
    finish(1, CORRECT);
  }

  // Inace sve treba biti identicno osim zadnjeg elementa za kojeg custom check.
  for (int i = 0; i < (int) official_out.size() - 1; ++i)
      if (official_out[i] != contestant_out[i])
        finish(0, WRONG);

  if (!check_expression(expr, contestant_out.back())) finish(0, WRONG);
  finish(1, CORRECT);

  // The function MUST terminate before this line via finish()!
}

void finish(double p, const string& m) {
  cout << p << endl;
  cout << m << endl;
  exit(0);
}

int main(int argc, char *argv[])
{
  assert(argc == 4);

  ifstream fin(argv[1]);
  ifstream foff(argv[2]);
  ifstream fout(argv[3]);

  assert(!fin.fail() && !fout.fail());
  checker(fin, foff, fout);
  assert(false); // checker must terminate via finish() before exiting!

  return 0;
}
