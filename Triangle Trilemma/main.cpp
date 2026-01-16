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

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N; cin >> N;
    for (int t = 1; t <= N; ++t) {
        Point<int> A, B, C; cin >> A >> B >> C;

        bool pts_not_unique = A == B || A == C || B == C;
        bool pts_colinear = (B.y - A.y) * (C.x - B.x) == (C.y - B.y) * (B.x - A.x);
        if (pts_not_unique || pts_colinear) {
            cout << "Case #" << t << ": not a triangle\n";
            continue;
        }

        vector<pair<Point<int>, Point<int>>> vects;
        vects.push_back({B - A, C - A});
        vects.push_back({A - B, C - B});
        vects.push_back({A - C, B - C});

        string ang_type = "acute";
        string side_type = "scalene";
        unordered_set<double> side_lens;
        for (auto& [v1, v2] : vects) {
            if (v1.angle_with(v2) == M_PI_2) {
                ang_type = "right";
            }
            else if (v1.angle_with(v2) > M_PI_2) {
                ang_type = "obtuse";
            }
            side_lens.insert(v1.dist_to(v2));
        }
        if (side_lens.size() < 3) side_type = "isosceles";

        cout << "Case #" << t << ": " << side_type << " " << ang_type << " triangle\n";
    }

    return 0;
}
