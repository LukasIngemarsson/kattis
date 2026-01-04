#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/*
A class for rational numbers, supporting common arithmetic 
operations and comparison operators. Initialization defaults
to numerator = 0 and denominator = 1.
*/
struct RationalArithmetic {
    ll n, d;

    RationalArithmetic() : n(0), d(1) {}
    
    RationalArithmetic(ll n, ll d) : n(n), d(d) {
        normalize();
    }

    /* Finds the greatest commmon divisor (GCD) for two integers. */
    ll gcd(ll a, ll b) {
        return b == 0 ? a : gcd(b, a % b);
    }

    /* Normalizes the rational number, i.e., divides it by the factors 
    shared by the numerator and denominator. */
    void normalize() {
        ll g = gcd(abs(n), abs(d));
        n /= g; 
        d /= g;
        if (d < 0) {
            n *= -1;
            d *= -1;
        }
    }

    /* --- Operations --- */

    RationalArithmetic operator+(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d + other.n * d, d * other.d);
    }

    RationalArithmetic operator-(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d - other.n * d, d * other.d);
    }

    RationalArithmetic operator*(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.n, d * other.d);
    }

    RationalArithmetic operator/(const RationalArithmetic& other) const {
        return RationalArithmetic(n * other.d, d * other.n);
    }

    /* --- Comparison operators --- */

    bool operator<(const RationalArithmetic& other) const {
        return n * other.d < other.n * d;
    }

    bool operator>(const RationalArithmetic& other) const {
        return n * other.d > other.n * d;
    }

    bool operator<=(const RationalArithmetic& other) const {
        return n * other.d <= other.n * d;
    }
    
    bool operator>=(const RationalArithmetic& other) const {
        return n * other.d >= other.n * d;
    }

    bool operator==(const RationalArithmetic& other) const {
        return n * other.d == other.n * d;
    }

    bool operator!=(const RationalArithmetic& other) const {
        return n * other.d != other.n * d;
    }

    /* --- Input and output --- */

    friend istream& operator>>(istream& in, RationalArithmetic& r) {
        in >> r.n >> r.d;
        r.normalize();
        return in;
    }

    friend ostream& operator<<(ostream& out, const RationalArithmetic& r) {
        out << r.n << " / " << r.d;
        return out;
    }
};

void test_comp_ops() {
    cout << "\ncomparison operators test\n";
    
    vector<RationalArithmetic> v;
    v.emplace_back(1, 4);
    v.emplace_back(1, 7);
    v.emplace_back(1, 2);
    v.emplace_back(1, 6);
    v.emplace_back(1, 3);
    v.emplace_back(1, 5);

    cout << "before: ";
    for (auto& ra : v) {
        cout << ra.n / (double) ra.d << " ";
    }
    cout << '\n';

    sort(v.begin(), v.end());

    cout << "after: ";
    for (auto& ra : v) {
        cout << ra.n / (double) ra.d << " ";
    }
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int num_ops; cin >> num_ops;
    while (num_ops--) {
        RationalArithmetic a, b;
        char op;
        cin >> a >> op >> b;
        
        switch (op) {
            case '+':
                cout << a + b;
                break;
            case '-':
                cout << a - b;
                break;
            case '*':
                cout << a * b;
                break;
            case '/':
                cout << a / b;
                break;
        }
        cout << '\n';
    }

    // test_comp_ops();

    return 0;
}
