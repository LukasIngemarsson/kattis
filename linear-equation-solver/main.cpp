#include <bits/stdc++.h>
using namespace std;

typedef vector<double> vd;
#define EPS 1e-9

/*
@brief Solves a linear equation system for a given left-side matrix `A` and right-side vector `b`, 
using Gauss Elimination.

@param A: A matrix containing the coeffiecients of the left-side of the equation system.
@param b: A vector containing the coeffiecients of the right-side of the equation system.

@return A pair containing 
1. an integer representing the solvability of the system
(0 = inconsistent, 1 = single solution, 2 = multiple solutions), and 
2. A vector containing the solution in case 1, otherwise it is empty.

@note Time complexity: `O(min(n, m) * n * m)`, where `n` is the number of equations 
and `m` is the number of variables. If `n` = `m`, it is `O(n^3)`.
*/
pair<int, vd> solve_linear_eq(vector<vd> A, vd b) {
    int n = A.size(), m = A[0].size();
    vector<int> pivot_rows(m, -1); // stores the index of the pivot row for each column

    /*
    Manually solving an equation system with many variables and equations is impractical, 
    and thus a programmatic implementation of Gauss Eliminimation can be very helpful.

    It works as follows:
    Starting from the top left of the matrix, we look for the value in the column with
    the highest absolute value to turn into a pivot element. Then, we swap the corresponding row
    with the current row, and subtract the product of the current row and each factor needed to turn 
    all other values in the column to zero. This is then repeated for subsequent rows and columns,
    until the bottom and/or the right of the matrix is reached. After this, we simply iterate through 
    each column, and extract the values of the (solvable) variables by dividing the right side value 
    with the pivot element. If a column is missing a pivot element, the equation has multiple solutions. 
    If the sum of a row that is produced by plugging in the extracted variable values does not match the 
    right side value, then the system is deemed inconsistent.
    */

    for (int r = 0, c = 0; r < n && c < m; ++c) {
        // select the row with the largest absolute value
        int sel = r;
        for (int i = r + 1; i < n; ++i) {
            if (abs(A[i][c]) > abs(A[sel][c])) {
                sel = i;
            }
        }
        if (abs(A[sel][c]) < EPS) continue;

        // swap selected row with the current row
        for (int i = c; i < m; ++i) {
            swap(A[sel][i], A[r][i]);
        }
        swap(b[sel], b[r]);
        pivot_rows[c] = r;

        // turn the elements in the current column to zeros, except for the pivot element
        for (int i = 0; i < n; ++i) {
            if (i == r) continue;

            double k = A[i][c] / A[r][c];
            A[i][c] = 0; // set manually for preciseness
            for (int j = c + 1; j < m; ++j) {
                A[i][j] -= A[r][j] * k;
            }
            b[i] -= b[r] * k;
        }
        ++r;
    }

    vd x(m);
    for (int i = 0; i < m; ++i) {
        if (pivot_rows[i] == -1) continue;
        
        x[i] = b[pivot_rows[i]] / A[pivot_rows[i]][i];
    }
    
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += x[j] * A[i][j];
        }

        if (abs(sum - b[i]) > EPS) {
            return {0, vd()};
        }
    }
    for (int i = 0; i < m; ++i) {
        if (pivot_rows[i] == -1) {
            return {2, vd()};
        }
    }

    return {1, x};
}

/*
void print_matrix(vector<vd>& A, vd& b) {
    cout << "Matrix:\n";
    cout << setprecision(3);
    for (int i = 0; i < A.size(); ++i) {
        for (int j = 0; j < A[0].size(); ++j) {
            cout << A[i][j] << '\t';
        }
        cout << "| " << b[i] << '\n';
    }
    cout << setprecision(6);
}
*/

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n != 0) {
        vector<vd> A(n, vd(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> A[i][j];
            }
        }
        vd b(n);
        for (int i = 0; i < n; ++i) {
            cin >> b[i];
        }

        pair<int, vd> ans = solve_linear_eq(A, b);
        int code = ans.first;
        vd x = ans.second;

        if (code == 0) {
            cout << "inconsistent";
        }
        else if (code == 1) {
            for (double d : x) {
                cout << d << " ";
            }
        }
        else {
            cout << "multiple";
        }
        cout << '\n';
    }

    return 0;
}
