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

void gen_divs(int idx, ll div, const vector<pair<ll, int>>& pfs, vector<ll>& divs) {
    if (idx == pfs.size()) {
        divs.push_back(div);
        return;
    }

    auto [p, exp] = pfs[idx];
    for (int i = 0; i <= exp; ++i) {
        gen_divs(idx + 1, div, pfs, divs);
        div *= p;
    }
}

vector<ll> get_divs(const vector<pair<ll, int>>& pfs) {
    vector<ll> divs;
    gen_divs(0, 1, pfs, divs);
    return divs;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    ll N; cin >> N;

    auto primes = PrimeSieve(1e6).primes;
    auto divs = get_divs(prime_factorize(N, primes));

    sort(divs.begin(), divs.end());
    for (int i = 0; i < divs.size(); ++i) {
        if (i > 0) cout << " ";
        cout << divs[i] - 1;
    }
    cout << '\n';

    return 0;
}
