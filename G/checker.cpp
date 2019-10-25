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

const int MAXN = 5e5 + 10;

/**
 * The main checking function.
 * @param fin official input
 * @param foff official output
 * @param fout contestant's output
 */
void checker(ifstream& fin, ifstream& foff, ifstream& fout) {
  const string UNEXPECTED_ERROR = "Unexpected error - report via clarification request";
  const string WRONG = "Wrong answer";
  const string CORRECT = "Accepted";

  // Read official input
  int n;
  int x[MAXN], y[MAXN];

  if (!(fin >> n)) finish(0, UNEXPECTED_ERROR);
  for (int i = 0; i < n; ++i)
    if (!(fin >> x[i] >> y[i])) finish(0, UNEXPECTED_ERROR);

  // Read official output
  string official_out;

  if (!(foff >> official_out)) finish(0, UNEXPECTED_ERROR);

  // Read contestant's output
  string contestant_out;

  if (!(fout >> contestant_out)) finish(0, WRONG);

  string trash;
  if (fout >> trash) finish(0, WRONG);

  if ((int) contestant_out.size() != 2 * n) finish(0, WRONG);
  for (char c : contestant_out)
    if (c != 'A' && c != 'B') finish(0, WRONG);

  // neighbour check
  for (int i = 0; i < 2 * n; ++i) {
    int prv = (i - 1 + 2 * n) % (2 * n);
    int nxt = (i + 1) % (2 * n);
    if (contestant_out[prv] == contestant_out[i] &&
        contestant_out[i] == contestant_out[nxt]) finish(0, WRONG);
  }

  for (int i = 0; i < n; ++i)
    if (contestant_out[x[i] - 1] == contestant_out[y[i] - 1])
      finish(0, WRONG);

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
