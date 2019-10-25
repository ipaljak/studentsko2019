#include<bits/stdc++.h>

using namespace std;

int n, br;
char kraj;
string s, sol;

int main () {
    cin >> n;
    int r = (n + 2) / 3;
    for (int i = 0; i < r; i++) {
        string t; cin >> t;
        s += t;
    }
    int p = 0;
    while (p < n) {
        if (p + 2 < n && s[p] == s[p + 1] && s[p] == s[p + 2]) {
            sol += s[p]; sol += s[p]; sol += s[p];
            p += 3;
            br = 0;
        } else if (p + 1 < n && s[p] == s[p + 1]) {
            br = 2;
            kraj = s[p];
            p += 2;
        } else {
            if (br == 0) {
                br = 1;
                kraj = s[p];
            }
            p += 1;
        }
    }
    for (int i = 0; i < br; i++) sol += kraj;
    int len = sol.size();
    cout << len << '\n';
    for (int i = 0; i < len; i += 3) {
        cout << sol.substr(i, 3) << '\n';
    }
    return 0;
}
