#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 1000000009;
int n, m, h[1050005], len;
long long f[1050005], g[1050005];
#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin >> n;
    len = 1 << n;
    for (int i = 0; i < len; i++) cin >> f[i];
    for (int i = 0; i < len; i++) cin >> g[i];
    for (int i = 0; i < len; i++) {
        register __int128 p = 0;
        for (register int j = i; j; j = (j - 1) & i) {
            p += f[j] * g[i - j];
        }
        p += f[0] * g[i];
        h[i] = p;
    }
    for (int i = 0; i < len; i++) cout << h[i] << ' ';
}
