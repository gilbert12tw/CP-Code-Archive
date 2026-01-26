// Minimum Enclosing Circle (points only, unweighted)
// Expected O(n) randomized incremental (Welzl-style, iterative boundary).
static const double EPS = 1e-9;

struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double _x, double _y) : x(_x), y(_y) {}
    Point operator + (const Point& o) const { return {x + o.x, y + o.y}; }
    Point operator - (const Point& o) const { return {x - o.x, y - o.y}; }
    Point operator * (double k) const { return {x * k, y * k}; }
};
static inline double dot(const Point& a, const Point& b){ return a.x*b.x + a.y*b.y; }
static inline double cross(const Point& a, const Point& b){ return a.x*b.y - a.y*b.x; }
static inline double norm2(const Point& a){ return dot(a, a); }
static inline double dist(const Point& a, const Point& b){ return sqrt(norm2(a - b)); }

struct Circle {
    Point center; double radius;
    Circle() : center(), radius(-1) {}                    // invalid if radius < 0
    Circle(Point c, double r) : center(c), radius(r) {}
    bool valid() const { return radius >= -0.5; }
    bool contains(const Point& p, double e = EPS) const {
        return valid() && dist(center, p) <= radius + e;
    }
};

static inline Circle circleFromTwoPoints(const Point& a, const Point& b) {
    Point c = (a + b) * 0.5;
    return Circle(c, dist(a, b) * 0.5);
}

static inline Circle circleFromFarthestPair(const Point& a, const Point& b, const Point& c) {
    double dAB = dist(a, b), dAC = dist(a, c), dBC = dist(b, c);
    if (dAB >= dAC && dAB >= dBC) return circleFromTwoPoints(a, b);
    if (dAC >= dAB && dAC >= dBC) return circleFromTwoPoints(a, c);
    return circleFromTwoPoints(b, c);
}

static inline Circle circleFromThreePoints(const Point& a, const Point& b, const Point& c) {
    double D = 2.0 * cross(b - a, c - a);
    if (fabs(D) < EPS) return circleFromFarthestPair(a, b, c); 

    double A2 = norm2(a), B2 = norm2(b), C2 = norm2(c);
    double ux = ((B2 - A2) * (c.y - a.y) - (C2 - A2) * (b.y - a.y)) / D + a.x;
    double uy = ((C2 - A2) * (b.x - a.x) - (B2 - A2) * (c.x - a.x)) / D + a.y;
    Point o(ux, uy);
    return Circle(o, dist(o, a));
}

static Circle minimumEnclosingCircle(vector<Point> pts) {
    mt19937_64 rng(random_device{}());
    shuffle(pts.begin(), pts.end(), rng);

    Circle C; // invalid
    for (int i = 0; i < (int)pts.size(); ++i) {
        if (C.valid() && C.contains(pts[i])) continue;
        C = Circle(pts[i], 0.0);
        for (int j = 0; j < i; ++j) {
            if (C.contains(pts[j])) continue;
            C = circleFromTwoPoints(pts[i], pts[j]);
            for (int k = 0; k < j; ++k) {
                if (C.contains(pts[k])) continue;
                C = circleFromThreePoints(pts[i], pts[j], pts[k]);
            }
        }
    }
    return C;
}

/*** Example usage:
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<Point> pts(n);
    for (int i = 0; i < n; ++i) cin >> pts[i].x >> pts[i].y;
    Circle ans = minimumEnclosingCircle(pts);
    cout.setf(std::ios::fixed); cout << setprecision(10);
    cout << ans.radius << "\n" << ans.center.x << " " << ans.center.y << "\n";
    return 0;
}
***/

