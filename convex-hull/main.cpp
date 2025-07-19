// Author: Lukas Ingemarsson
#include <bits/stdc++.h>
using namespace std;

/* 2D point class. Defaults to (0, 0) if x and y are not provided. */
template<typename T>
struct Point {
    T x, y;

    Point (T x = 0, T y = 0) : x(x), y(y) {}

    /* Addition. */
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }

    /* Subtraction. */
    Point operator-(const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    /* Multiplication (w/ point on left side). */
    Point operator*(T scalar) const {
        return Point(x * scalar, y * scalar);
    }

    /* Multiplication (w/ point on right side). */
    friend Point operator*(T scalar, const Point& p) {
        return Point(p.x * scalar, p.y * scalar);
    }

    /* Division. */
    Point operator/(T scalar) const {
        return Point(x / scalar, y / scalar);
    }

    /* Dot product. */
    T dot(const Point& other) const {
        return x * other.x + y * other.y;
    }

    /* Cross product. */
    T cross(const Point& other) const {
        return x * other.y - y * other.x;
    }

    /* Norm. */
    double norm() const {
        return sqrt(x * x + y * y);
    }

    /* Distance to another point. */
    double dist_to(const Point& other) const {
        return (*this - other).norm();
    }

    /* Angle with another point. */
    double angle_with(const Point& other) const {
        double dot_prod = this->dot(other);
        double norm_prod = this->norm() * other.norm();
        return acos(dot_prod / norm_prod); // radians
    }

    /* Angle with origin. */
    double angle() const {
        return atan2(y, x);
    }

    bool operator<(const Point& other) const {
        if (x == other.x) return y < other.y;
        return x < other.x;
    }

    bool operator>(const Point& other) const {
        if (x == other.x) return y > other.y;
        return x > other.x;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    friend istream& operator>>(istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
};

/*
@brief Finds the convex hull for the given set of points, using the
Monotone Chain algorithm.

@param pts: The vector of points.

@return A vector containing the points in the convex hull in CCW order.

@note Time complexity: `O(n * log(n))`, where `n` is the number of points.
*/
template <typename T>
vector<Point<T>> convex_hull(vector<Point<T>> pts) {
    /*
    The algorithm works as follows: 
    - First, we sort the set of points in ascending order,
        and remove any duplicate points.
    - After this, if there are two points or less, we can stop early,
        as the given set is the convex hull itself in CCW order.
    - We initialize a vector to store the convex hull, with
        the size `2n` (to fit the maximum intermediate state size during
        the algorithm), as well as a counter `k` to keep track of the number
        of points currently added to the hull.
    - Then, we start by constructing the lower hull.
        - For each point from left to right (0 <= i < n):
            - As long as we have at least two points in the hull (k >= 2), 
                and the cross product between the latest added line segment
                and the line segment formed by the current point and the 
                second-to-last point added to the hull, is not positive 
                (which would indicate a turn that is not to the left), 
                we discard the point that was last added to the hull.
    - Next, we construct the upper hull. 
        - The logic remains the same as for the lower hull, expect that
            we iterate through the points from right to left (n - 2 >= i >= 0), 
            excluding the rightmost point which was just added in the lower hull.
    - The convex hull result vector will contain a duplicate of the leftmost 
        starting point, as it is processed in both the upper and lower hull,
        thus we have to resize the result vector to remove it (as well as to
        truncate the buffer assigned at initialization).
    - The convex hull will inherently be in CCW order once the algorithm is finished.
    */

    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    int n = pts.size();

    if (n <= 2) return pts;

    vector<Point<T>> res(2 * n);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && (res[k-1] - res[k-2]).cross(pts[i] - res[k-2]) <= 0) --k;
        res[k++] = pts[i];
    }
    int lhk = k; // lower hull last index
    for (int i = n - 2; i >= 0; --i) {
        while (k > lhk && (res[k-1] - res[k-2]).cross(pts[i] - res[k-2]) <= 0) --k;
        res[k++] = pts[i];
    }
    
    res.resize(k - 1);

    return res;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n) {
        vector<Point<int>> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i];

        auto res = convex_hull(pts);
        cout << res.size() << '\n';
        for (auto& pt : res) {
            cout << pt.x << " " << pt.y << '\n';
        }
    }

    return 0;
}
