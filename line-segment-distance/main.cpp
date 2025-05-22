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

    friend istream& operator>>(std::istream& is, Point& p) {
        is >> p.x >> p.y;
        return is;
    }

    friend ostream& operator<<(std::ostream& os, const Point& p) {
        os << '(' << p.x << ", " << p.y << ')';
        return os;
    }
};

#define EPS 1e-9
typedef Point<double> P;

/* Checks if the given point lies on the given line segment. */
bool on_segment(const P& s, const P& e, const P& p) {
    // check if `p` is colinear with segment `s->e`
    if (abs((e - s).cross(p - s)) > EPS) return false;

    // check if `p` lies on the segment `s->e`
    return (p - s).dot(p - e) <= EPS;
}

int sgn(double d) {
    return (d > EPS) - (d < -EPS);
}

/*
@brief Finds the intersection point/segment between two line segments, if one exists.

@param s1: Start point of the first segment.
@param e1: End point of the first segment.
@param s2: Start point of the second segment.
@param e2: End point of the second segment.

@return A vector containing:
    - Nothing, if no intersection exists.
    - One point, if the segments intersect in a single point.
    - Two points, representing the start and end of the intersecting segment,
        if the segments overlap over a length.
*/
vector<P> line_seg_intersect(const P& s1, const P& e1, const P& s2, const P& e2) {
    /*
    The algorithm works as follows: 
    - First, we calculate the cross product between the respective line segments'
        vector and the vector that their respective starting point creates with
        the other segments' start and end point. This tells us which "side" the
        start and end point of each line segment is on relative to the other line
        segment (positive = "left", negative = "right", zero = "colinear").
    - If the start and end point of the respective line segments lie on different
        sides of the other line segment, we can determine that the lines intersect
        at a single point (as they cross each other).
    - Otherwise, we check if the respective segments' start and end point lie on
        the other segment. This can be none, a single point, or two points (i.e., 
        a line segment) if the lines overlap over a length.
    */

    double o1 = (e2 - s2).cross(s1 - s2);
    double o2 = (e2 - s2).cross(e1 - s2);
    double o3 = (e1 - s1).cross(s2 - s1);
    double o4 = (e1 - s1).cross(e2 - s1);

    if (sgn(o1) * sgn(o2) < 0 && sgn(o3) * sgn(o4) < 0) {
        P intersect_pt = (s1 * o2 - e1 * o1) / (o2 - o1);
        return { intersect_pt };
    }

    set<P> intersect_pts;
    if (on_segment(s2, e2, s1)) intersect_pts.insert(s1);
    if (on_segment(s2, e2, e1)) intersect_pts.insert(e1);
    if (on_segment(s1, e1, s2)) intersect_pts.insert(s2);
    if (on_segment(s1, e1, e2)) intersect_pts.insert(e2);

    return vector<P>(intersect_pts.begin(), intersect_pts.end());
}

/* Calculates the minimum distance from the given line segment to the given point. */
double line_seg_dist_to_pt(const P& s, const P& e, const P& p) {
    P seg_vect = e - s;

    double seg_len_sq = seg_vect.dot(seg_vect);

    // check if the segment is simply a point (length == 0)
    if (seg_len_sq < EPS * EPS) return (p - s).norm();

    // calculate the projection parameter `t` of point `p` onto the infinite
    // line that is colinear with segment `s->e`, and clamp the value between
    // 0 and 1 (as we can only select a point that lies on the segment)
    double t = max(0.0, min(1.0, (p - s).dot(seg_vect) / seg_len_sq));
    P closest_pt = s + t * seg_vect;

    return (p - closest_pt).norm();
}

/*
@brief Calculates the shortest distance between two line segments.

@param s1: Start point of the first segment.
@param e1: End point of the first segment.
@param s2: Start point of the second segment.
@param e2: End point of the second segment.

@return The minimum Euclidian distance between any point on the first segment
        and any point on the second segment.
*/
double line_seg_dist(const P& s1, const P& e1, const P& s2, const P& e2) {
    /*
    It works as follows:
    - First, we check if the line segments intersect, as that would mean
        that their minimum distance is zero.
    - Otherwise, we know that the shortest distance must be from a start
        or end point of one line segment to the other segment, so we simply
        calculate these distances and take the minimum value as our answer.
    */

    if (line_seg_intersect(s1, e1, s2, e2).size() > 0) return 0.0;

    double d1 = line_seg_dist_to_pt(s1, e1, s2);
    double d2 = line_seg_dist_to_pt(s1, e1, e2);
    double d3 = line_seg_dist_to_pt(s2, e2, s1);
    double d4 = line_seg_dist_to_pt(s2, e2, e1);

    return min({d1, d2, d3, d4});
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int n; cin >> n;
    while (n--) {
        P s1, e1, s2, e2;
        cin >> s1 >> e1 >> s2 >> e2;

        cout << fixed << setprecision(2) << line_seg_dist(s1, e1, s2, e2) << '\n';
    }

    return 0;
}
