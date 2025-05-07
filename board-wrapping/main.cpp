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

    friend istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator<<(std::ostream& os, const Point& p) {
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
vector<Point<double>> convex_hull(vector<Point<double>> pts) {
    sort(pts.begin(), pts.end());
    pts.erase(unique(pts.begin(), pts.end()), pts.end());

    int n = pts.size();

    if (n <= 2) return pts;

    vector<Point<double>> res(2 * n);
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

/* 
@brief Calculates the area for a polygon with the given vector of vertices. 

@param pts: A vector containing the polygon's vertices.

@return The polygon's signed area.

@note Time complexity: `O(n)`, where `n` is the number of vertices.
*/
double polygon_area(const vector<Point<double>>& pts) {
    double res = 0;
    int n = pts.size();

    for (int i = 0; i < n; ++i) {
        Point<double> a = pts[i], b = pts[(i + 1) % n];
        res += (a.x - b.x) * (b.y + a.y);
    }
    return res / 2;
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int N; cin >> N;
    while (N--) {
        int n; cin >> n;

        vector<Point<double>> pts(4 * n);
        double board_area = 0;
        for (int i = 0; i < n; ++i) {
            double x, y, w, h, v;
            cin >> x >> y >> w >> h >> v;

            board_area += w * h;

            v *= M_PI / 180;
            Point<double> c(x, y);
            Point<double> h_vect((h / 2) * sin(v), (h / 2) * cos(v));
            Point<double> w_vect((w / 2) * -cos(v), (w / 2) * sin(v));

            pts[4*i] = c - h_vect - w_vect;
            pts[4*i+1] = c - h_vect + w_vect;
            pts[4*i+2] = c + h_vect - w_vect;
            pts[4*i+3] = c + h_vect + w_vect;
        }

        cout << fixed << setprecision(1);
        cout << 100 * board_area / abs(polygon_area(convex_hull(pts))) << " %\n";
    }

    return 0;
}
