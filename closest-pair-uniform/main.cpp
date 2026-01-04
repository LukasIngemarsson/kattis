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
@brief Finds the closest pair in the given set of points.

@param pts: The vector of points.

@return: A pair containing the two points that are closest to each other.

@note Time complexity: `Oam(n * log(n))`, where `n` is the number of points.
*/
pair<Point<double>, Point<double>> closest_pair(vector<Point<double>> pts) {
    /*
    The algorithm works as follows: 
    - First, we sort the points in ascending order.
    - We maintain a pair containing the closest point pair (so far),
        as well as the distance between this closest pair.
        - We initialize these using the first and second point in the sorted vector.
    - Then, for each point `pt1` after the first two points (2 <= i < n), we:
        - For each preceeding point `pt2` (i - 1 >= j >= 0):
            - Calculate the distance between `pt1` and `pt2`.
            - If this distance is smaller than the current minimum, we update the
                closest pair and closest distance.
            - Otherwise, if the difference in the x coordinates of the two points
                is greater than the current minimum distance, we can move on to 
                the next `pt1` (as the set of points is sorted, we know that no subsequent 
                point `pt2` will give a closer distance for the current `pt1`).
    */

    int n = pts.size();

    sort(pts.begin(), pts.end());

    pair<Point<double>, Point<double>> closest{pts[0], pts[1]}; 
    double min_dist = closest.first.dist_to(closest.second);
    for (int i = 2; i < n; ++i) {
        Point<double> pt1 = pts[i];

        for (int j = i - 1; j >= 0; --j) {
            Point<double> pt2 = pts[j];
            double dist = pt1.dist_to(pt2);

            if (dist < min_dist) {
                min_dist = dist;
                closest = {pt1, pt2};
            }
            else if ((pt1.x - pt2.x) > min_dist) {
                break;
            }
        }
    }

    return closest;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n) {
        vector<Point<double>> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i];

        auto [p1, p2] = closest_pair(pts);
        cout << fixed << setprecision(2) << p1.x << " " << p1.y << " " << p2.x << " " << p2.y << '\n';
    }

    return 0;
}
