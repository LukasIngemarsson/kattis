// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/* A class for modular arithmetic operations. */
struct ModularArithmetic {
    ll m; // the modulus

    ModularArithmetic(ll m) : m(m) {}

    void set_mod(ll m) { this->m = m; };
    
    /* Modular addition. */
    ll add(ll a, ll b) {
        // apply mod on both integers first to avoid integer overflow when adding
        return (a % m + b % m) % m;
    }

    /* Modular subtraction. */
    ll sub(ll a, ll b) {
        // add `m` to ensure proper modulus behavior for negative values
        return ((a % m - b % m) + m) % m;
    }

    /* Modular multiplication. */
    ll mult(ll a, ll b) {
        return ((a % m) * (b % m)) % m;
    }

    /* Modular exponentation. Time complexity: `O(log(n))`.*/
    ll pow(ll a, ll n) {
        a %= m;
        ll res = 1;
        while (n > 0) {
            if (n % 2 != 0) {
                res = res * a % m;
            }
            a = a * a % m;
            n /= 2;
        }
        return res;
    }

    /* Extended GCD. Finds the GCD for two given integers, while also finding 
    a way to represent the GCD in terms of the two integers (saved in-place in 
    coefficients `x` and `y`). Time complexity: `O(log(min(a, b)))`. */
    ll ext_gcd(ll a, ll b, ll& x, ll& y) {
        if (b == 0) {
            x = 1, y = 0;
            return a;
        }
        
        ll x1, y1;
        ll d = ext_gcd(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }

    /* Modular inverse. Time complexity: `O(log(m))`. */
    ll inv(ll a) {
        ll x, y;
        ll g = ext_gcd(a, m, x, y);
        if (g != 1) return -1; // modular inverse does not exist
        return (x % m + m) % m; // add m to handle potential negative `x`
    }

    /* Modular division. Time complexity: `O(log(m))`. */
    ll div(ll a, ll b) {
        ll inv_b = inv(b);
        if (inv_b == -1) return -1;
        return mult(a, inv_b);
    }

    /* Bit-wise modulus multiplication to avoid integer overflow. Time complexity: `O(log(b))`. */
    ll bw_mult(ll a, ll b) {
        ll res = 0;
        a %= m;
        b %= m;
        while (b > 0) {
            if (b & 1) {
                res = (res + a) % m;
            }
            a = (a << 1) % m;
            b >>= 1;
        }
        return res;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll n;
    int t;
    while (cin >> n >> t && (n || t)) {
        ModularArithmetic ma(n);

        while (t--) {
            ll x, y;
            char op;
            cin >> x >> op >> y;

            switch (op) {
                case '+':
                    cout << ma.add(x, y);
                    break;
                case '-':
                    cout << ma.sub(x, y);
                    break;
                case '*':
                    cout << ma.mult(x, y);
                    break;
                case '/':
                    cout << ma.div(x, y);
                    break;
            }
            cout << '\n';
        }
    }

    return 0;
}
