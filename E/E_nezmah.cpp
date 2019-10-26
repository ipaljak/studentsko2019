#include<bits/stdc++.h>

using namespace std;

typedef long long llint;

string s;
string st = "0123456789+-*/=";

llint broj (string s) {
    if (s.size() == 0) return 0;
    if (s[0] == '0') return 0;
    llint val = 0;
    for (auto c : s) {
        if (!('0' <= c && c <= '9')) return 0;
        val = val * 10 + c - '0';
    }
    if (!(1 <= val && val <= 1000000000)) return 0;
    return val;
}

bool ok (string s, int tip) {
    int oper = -1, eq = -1, len = s.size();
    for (int i = 0; i < len; i++) {
        if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/') oper = i;
        if (s[i] == '=') eq = i;
    }
    if (oper == -1 || eq == -1) return 0;
    if (oper > eq) return 0;
    llint a = broj(s.substr(0, oper));
    llint b = broj(s.substr(oper + 1, eq - 1 - oper));
    llint c = broj(s.substr(eq + 1, len - 1 - eq));
    if (a == 0 || b == 0 || c == 0) return 0;
    if (tip == 0) return 1;
    if (s[oper] == '+') return a + b == c;
    if (s[oper] == '-') return a - b == c;
    if (s[oper] == '*') return a * b == c;
    if (s[oper] == '/') return a == c * b;
}

void rjesi () {
    if (ok(s, 0)) {
        if (ok(s, 1)) {
            cout << "Tocno";
        } else {
            int len = s.size();
            bool naso = 0; string sol;
            for (int i = 0; i < len; i++) {
                for (int j = 0; j < len; j++) {
                    for (auto c1 : st) {
                        for (auto c2 : st) {
                            string tmp = s;
                            tmp[i] = c1; tmp[j] = c2;
                            if (ok(tmp, 1)) {
                                naso = 1;
                                sol = tmp;
                            }
                        }
                    }
                }
            }
            if (naso) {
                cout << "Netocno, umjesto " << s << " mogli ste ispisati " << sol;
            } else {
                cout << "Potpuno netocno";
            }
        }
    } else {
        cout << "Izraz nije ispravno formatiran";
    }
}

int main () {
    cin >> s;
    rjesi();
    return 0;
}
