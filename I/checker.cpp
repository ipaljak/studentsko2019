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

inline int ceil(int a, int b) {
  return (a + b - 1) / b;
}

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

/**
 * Checks if string b is a subsequence of string a.
 */
bool check_subsequence(const string &a, const string &b) {
  int a_ptr = 0;
  for (char b_char : b) {
    while (a_ptr < (int) a.size() && a[a_ptr] != b_char) ++a_ptr;
    if (a_ptr >= a.size()) return false;
    ++a_ptr;
  }
  return true;
}

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
  string pics;

  if (!(fin >> n)) finish(0, UNEXPECTED_ERROR);
  for (int i = 0; i < ceil(n, 3); ++i) {
    string row;
    if (!(fin >> row)) finish(0, UNEXPECTED_ERROR);
    for (int j = 0; j < (int) row.size(); ++j)
      pics.push_back(row[j]);
  }

  // Read official output
  int official_out;
  string official_pics;

  if (!(foff >> official_out)) finish(0, UNEXPECTED_ERROR);
  for (int i = 0; i < ceil(official_out, 3); ++i) {
    string row;
    if (!(foff >>row)) finish(0, UNEXPECTED_ERROR);
    for (int j = 0; j < (int) row.size(); ++j)
      official_pics.push_back(row[j]);
  }

  // Read contestant's output
  int contestant_out;
  string contestant_pics;

  int contestant_cnt[26];
  memset(contestant_cnt, 0, sizeof contestant_cnt);

  if (!(fout >> contestant_out)) finish(0, WRONG);

  // Number of remaining pics doesn't match the official output.
  if (contestant_out != official_out) finish(0, WRONG);

  for (int i = 0; i < ceil(contestant_out, 3); ++i) {
    string row;
    if (!(fout >> row)) finish(0, WRONG);

    // Check if each row has the right amount of pictures
    if (i < contestant_out / 3 || contestant_out % 3 == 0) {
      if (row.size() != 3) finish(0, WRONG);
    } else {
      if (row.size() != contestant_out % 3) finish(0, WRONG);
    }

    for (int j = 0; j < (int) row.size(); ++j)
      contestant_pics.push_back(row[j]);
  }

  string trash;
  if (fout >> trash) finish(0, WRONG);

  // The total amount of pictures should correspond to the output
  if (contestant_pics.size() != contestant_out) finish(0, WRONG);

  // contestant pictures should form a subsequence of the original array
  if (!check_subsequence(pics, contestant_pics)) finish(0, WRONG);

  bool block_check = true;
  for (int i = 0; i < 26; ++i) {
    if ('A' + i == contestant_pics.back()) continue;
    block_check &= contestant_cnt[i] % 3 == 0;
  }

  if (!block_check) finish(0, WRONG);
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
