#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

/* 
@brief Sieve of Erathostenes. Finds all prime numbers from 1 up to
a given upper bound `n`.

@note Time complexity (initialization): `O(n * log(log(n)))`, 
where `n` is the upper bound.
*/
struct PrimeSieve {
    vector<bool> v; // stores if a number is prime or not
    vector<ll> primes;

    PrimeSieve(ll n) : v(n + 1, true) {
        /*
        The algorithm works as follows:
        - We maintain a 1-indexed boolean vector which contains 
            if a number is prime or not, for each number in our sequence.
            - Each number is initialized as prime/true, apart from 0 and 1.
        - For each number from 2 to `n`, we:
            - Check if it has been marked as non-prime, and if it has not, 
                then it is prime, and we can then mark each multuple of
                the number up to `n` as non-prime.
        */

        v[0] = false, v[1] = false;
        for (ll i = 2; i <= n; ++i) {
            if (v[i]) {
                primes.push_back(i);
                for (ll j = i * i; j <= n; j += i) {
                    v[j] = false;
                }
            }
        }
    }
};

vector<pair<ll, int>> prime_factorize(ll n, const vector<ll>& primes) {
    vector<pair<ll, int>> pfs;

    for (ll p : primes) {
        if (p * p > n) break;

        if (n % p == 0) {
            int exp = 0;
            while (n % p == 0) {
                n /= p;
                ++exp;
            }
            pfs.emplace_back(p, exp);
        }
    }
    if (n > 1) pfs.emplace_back(n, 1);

    return pfs;
}

void gen_divisors(int idx, ll div, const vector<pair<ll, int>>& pfs, vector<ll>& divs) {
    if (idx == pfs.size()) {
        divs.push_back(div);
        return;
    }

    auto [p, exp] = pfs[idx];
    for (int i = 0; i <= exp; ++i) {
        gen_divisors(idx + 1, div, pfs, divs);
        div *= p;
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    /*
    For an endpoint (x, y), we have N = x + y - gcd(x, y),
    where the GCD is to negate the double-counting of lattice points.

    If we let g = gcd(x, y), then we can rewrite the eq. as
    N = x + y - g = x'g + y'g - g = g(x' + y' - 1) <=> x' + y' = N / g + 1,
    where x' and y' are coprime, since we factored out the GCD. It is
    also apparent that g is a divisor of N.

    In other words, we are looking for x', y' that solve the above eq.

    Let a = N / g + 1. This gives the equation x' + y' = a, which can be solved
    by looking for integers 1 <= x' < a such that gcd(x', a - x') = 1 (coprime),
    since y = a - x' (thus we do not have to look for both explicitly). Furthermore,
    we can simplify gcd(x', a - x') = gcd(x', a), since any common divisor of x' and
    a - x' must also divide their sum x' + (a - x') = a.

    Since N / g simply gives the co-divisor for a given divisor, and we will
    iterate over all divisors anyways, we can skip this operation and just
    use a = g + 1 instead (which means that we calculate the solution for
    the co-divisor of each divisor; which still gives the complete answer).

    Algorithm:
    - To check for prime factors more efficiently, precompute a Prime Sieve
        with an upper bound that is sqrt(N_limit) = sqrt(10^14) = 10^7, and 
        simply check for any larger prime afterwards (which can be at most one)
    - Calculate the prime factors of N, and use them to generate all its divisors
    - For each divisor:
        - Calculate the prime factors of a = div + 1
        - Count the number of integers x' that are coprime to a (using Euler's 
            totient function), and add them to a running sum (which in the end 
            will contain our answer)
    */

    PrimeSieve ps(1e7);

    int T; cin >> T;
    while (T--) {
        ll N; cin >> N;

        auto pfs = prime_factorize(N, ps.primes);
        vector<ll> divs;
        gen_divisors(0, 1, pfs, divs);
        
        ll ans = 0;
        for (ll div : divs) {
            ll a = div + 1;
            auto pfs = prime_factorize(a, ps.primes);

            for (auto [p, _] : pfs) {
                a -= a / p;
            }
            ans += a;
        }
        cout << ans << '\n';
    }

    return 0;
}
