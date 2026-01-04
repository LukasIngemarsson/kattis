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
@brief Finds the maximum number of colinear points in given set.

@param The set of points.

@return The maximum number of colinear points.

@note Time complexity: `O(n ^ 2 * log(n))`, where `n` is the 
number of points in the set.
*/
template <typename T>
int max_num_colinear_pts(const vector<Point<T>>& pts) {
    /*
    It works as follows:
    - For each point in the set, we:
        - Set the point as origin.
        - Calculate the angle that each other point creates with
            the current origin/reference point.
        - We store these angles in a vector and sort it in ascending order.
        - Then, we iterate through the angles and maintain a counter
            for the longest streak of consecutive items with the same
            angle to the reference point.
    - The longest streak that we have found after performing these
        steps for all points, is the answer.
    */

    int n = pts.size();

    if (n == 1) return 1;

    int max_cnt = 1;
    for (int i = 0; i < n; ++i) {
        Point<T> o = pts[i];

        vector<double> angs;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;

            double a = atan2(pts[j].y - o.y, pts[j].x - o.x);
            if (a < 0) a += M_PI; // normalize angle to be within [0, PI)
            angs.push_back(a);
        }
        sort(angs.begin(), angs.end());

        int cnt = 1;
        double cur_ang = angs.front();
        for (int j = 1; j < angs.size(); ++j) {
            if (angs[j] != cur_ang) {
                max_cnt = max(max_cnt, cnt);
                cur_ang = angs[j];
                cnt = 1;
            }
            else {
                ++cnt;
            }
        }
        max_cnt = max(max_cnt, cnt);
    }

    return max_cnt + 1; // +1 to account for the origin / reference point itself
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n;
    while (cin >> n && n != 0) {
        vector<Point<int>> pts(n);
        for (int i = 0; i < n; ++i) cin >> pts[i];
        
        cout << max_num_colinear_pts(pts) << '\n'; 
    }

    return 0;
}
