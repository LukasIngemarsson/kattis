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
@brief Checks if the given point is inside the given polygon or not, using the
Winding Number algorithm (angle version).

@param p: The point.
@param polygon: A vector containing the vertices of the polygon, in CW or CCW order.

@return An integer where -1 = out, 0 = on, and 1 = in.

@note Time complexity: `O(n)`, where `n` is the number of vertices.
*/
template <typename T>
int inside_polygon(const Point<T>& p, const vector<Point<T>> polygon) {
    /* 
    The algorithm works as follows:
    - First, we check if the point lies on the boundary of the polygon.
        - For each pair of adjacent vertices in the polygon, we:
            - Check if the vectors that they respectively form with
                the given point are colinear, and if they are, we check:
                - If the given point lies between the two vertices, i.e.,
                    on the line segment formed by the vertices (which would
                    mean that the point lies on the boundary).
    - If it is not on the boundary of the polygon, we:
        - For each pair of adjacent vertices in the polygon:
            - Calculate the angle that they respectively form with the given point.
            - Calculate the difference between these two angles, normalize it 
                to lie between (-PI, PI], and add it to a running sum.
        - In the end, if the running sum is (close to) +-2 * PI, the point lies
            inside the polygon, but if it is (close to) zero it lies on the outside.
    */

    int num_verts = polygon.size();

    for (int i = 0; i < num_verts; ++i) {
        Point<T> a = polygon[i];
        Point<T> b = polygon[(i + 1) % num_verts];

        if ((b - a).cross(p - a) == 0) {
            bool between_x = p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x);
            bool between_y = p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y);

            if (between_x && between_y) return 0;
        }
    }

    double ang = 0;
    for (int i = 0; i < num_verts; ++i) {
        Point<T> a = polygon[i];
        Point<T> b = polygon[(i + 1) % num_verts];

        double theta1 = (a - p).angle();
        double theta2 = (b - p).angle();
        double theta_diff = theta2 - theta1;

        while (theta_diff > M_PI) {
            theta_diff -= 2 * M_PI;
        }
        while (theta_diff <= -M_PI) {
            theta_diff += 2 * M_PI;
        }
        ang += theta_diff;
    }

    // (here we use simply compare the angle to PI, as
    // this is halfway between the two numbers to measure,
    // which clearly separates the two cases while allowing for 
    // floating point errors)
    return (abs(ang) < M_PI) ? -1 : 1; 
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n != 0) {
        vector<Point<int>> polygon(n);
        for (int i = 0; i < n; ++i) cin >> polygon[i];

        int m; cin >> m;
        while (m--) {
            Point<int> p; cin >> p;
            int ans = inside_polygon(p, polygon);

            if (ans == -1) {
                cout << "out\n";
            }
            else if (ans == 0) {
                cout << "on\n";
            }
            else {
                cout << "in\n";
            }
        }
    }
    return 0;
}
