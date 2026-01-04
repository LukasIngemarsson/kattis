#include <bits/stdc++.h>
using namespace std;

/* 
@brief Sieve of Erathostenes. Finds all prime numbers from 1 up to
a given upper bound `n`.

@note Time complexity (initialization): `O(n * log(log(n)))`, 
where `n` is the upper bound.
*/
struct PrimeSieve {
    int num_primes = 0;
    vector<bool> v; // stores if a number is prime or not

    PrimeSieve(int n) : v(n + 1, true) {
        /*
        The algorithm works as follows:
        - We maintain a 1-indexed boolean vector which contains 
            if a number is prime or not, for each number in our sequence.
            - Each number is initialized as prime/true, apart from 0 and 1.
        - For each number from 2 to `n`, we:
            - Check if it has been marked as non-prime, and if it has not, 
                then it is prime, and we can then mark each multuple of
                the number up to `n` as non-prime.
        - Once the algorithm is finished, the boolean vector can be used to
            query if a number is prime, for any number in the sequence. 
        */

        v[0] = false, v[1] = false;
        int sqrt_n = floor(sqrt(n));
        for (int i = 2; i <= n; ++i) {
            if (v[i]) {
                ++num_primes;
                if (i > sqrt_n) continue;

                // we can start from i^2 since smaller multiples of i 
                // necessarily must have been marked by smaller prime factors
                for (int j = i * i; j <= n; j += i) {
                    v[j] = false;
                }
            }
        }
    }

    int get_num_primes() { return num_primes; }

    /*
    @brief Returns if the given number is prime or not.

    @param The number to check.

    @return A boolean value representing if the number is prime.

    @note Time complexity: `O(1)`.
    */
    bool is_prime(int i) { return v[i]; }
};

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n, q; 
    cin >> n >> q;
    PrimeSieve ps(n);
    cout << ps.get_num_primes() << '\n';
    while (q--) {
        int x; cin >> x;
        cout << (int)ps.is_prime(x) << '\n';
    }

    return 0;
}
