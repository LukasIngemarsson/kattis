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
@brief Calculates the area for a polygon with the given vector of vertices,
using the trapezoid formula. 

@param pts: A vector containing the polygon's vertices in CW or CCW order.

@return The polygon's signed area (< 0 means CW, >= 0 means CCW).

@note Time complexity: `O(n)`, where `n` is the number of vertices.
*/
template <typename T>
double polygon_area(const vector<Point<T>>& pts) {
    double res = 0;
    int n = pts.size();

    for (int i = 0; i < n; ++i) {
        Point<T> a = pts[i], b = pts[(i + 1) % n];
        res += (a.x - b.x) * (b.y + a.y);
    }
    return res / 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n) {
        vector<Point<int>> pts(n);
        for (int i = 0; i < n; ++i) {
            cin >> pts[i];
        }
        auto area = polygon_area(pts);
        cout << ((area < 0) ? "CW" : "CCW") << ' ' << fixed << setprecision(1) << abs(area) << '\n';
    }

    return 0;
}
