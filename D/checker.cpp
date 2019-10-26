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

#define X first
#define Y second
#define PB push_back
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define TRACE(x) cout << #x << " = " << x << endl
#define _ << " _ " <<

using namespace std;


typedef pair < int, bool > pib;
typedef long long llint;

const int N = 2e5 + 500;
const int LOG = 20;

int n, k, S[N], D[N];			 // unos
int tlo[N], grun[N], loga[N];    // racunanje Grundy-a
int inp[N];						 // ispis
vector < int >  v;

bool cmp(const int &A, const int &B){
	if(S[A] != S[B]) 
		return S[A] < S[B];
	if(D[A] == D[B])
		return A > B;
	return D[A] > D[B];
}

void add(int x,int y){ x += 10;
	for(; x < N; x += x & -x)
		loga[x] = max(loga[x], y + 1);
}

int get(int x){ x += 10;
	int ret = 0;
	for(; x ; x -= x & -x)
		ret = max(loga[x], ret);
	return ret - 1;
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
  int n, k;
  int tr1, tr2;

  if (!(fin >> n >> k)) finish(0, UNEXPECTED_ERROR);
  for (int i = 0; i < n; ++i){
    if (!(fin >> S[i] >> D[i])) finish(0, UNEXPECTED_ERROR);
  }
  for(int i = 0;i < k;i++){
    if (!(fin >> inp[i])) finish(0, UNEXPECTED_ERROR);  	
  	inp[i]--;
  }
  string off_out, trash;
  string con_out;
  if(!(foff >> off_out)) finish(0, UNEXPECTED_ERROR);  
  if (!(fout >> con_out)) finish(0, WRONG);
//  cout << con_out << endl;
  if(fout >> trash) finish(0, WRONG);
  for(int i = 0;i < n;i++){
		D[n + i] = S[i], S[n + i] = D[i];
		v.PB(i); v.PB(n + i);
	}
	sort(v.begin(), v.end(), cmp);
	for(int i = 0;i < 2 * n;i++){
		grun[v[i]] = get(D[v[i]] - 1) + 1;
		if(v[i] < n)
			add(D[v[i]], grun[v[i]]);
	}
	if(con_out == "nemoguce"){
		if(off_out != "nemoguce")
			finish(0, WRONG);
		finish(1, CORRECT);
	}
  if((int)con_out.size() != k) finish(0, WRONG);
  int cur = 0;
	for(int i = 0;i < k;i++){
		if(con_out[i] != '0' && con_out[i] != '1')
			finish(0, WRONG);
		if(con_out[i] == '0') cur ^= grun[inp[i]];
		else cur ^= grun[inp[i] + n]; 
	}
//	printf("CUR = %d\n", cur);
	if(cur)
  	finish(1, WRONG);		
  finish(1, CORRECT);
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
