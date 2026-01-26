#include <bits/stdc++.h>
using namespace std;

using ld = long double;
const ld EPS = 1e-9;

struct Point {
    ld x, y;
};

struct Circle {
    Point center;
    ld radius_sq; 
};

ld dist_sq(const Point& a, const Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

Circle circle_from_two_points(const Point& p1, const Point& p2) {
    Point center = {(p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0};
    return {center, dist_sq(p1, center)};
}

Circle circle_from_three_points(const Point& a, const Point& b, const Point& c) {
    ld D = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    if (std::abs(D) < EPS) {
        ld d_ab = dist_sq(a, b), d_bc = dist_sq(b, c), d_ca = dist_sq(c, a);
        if (d_ab >= d_bc && d_ab >= d_ca) return circle_from_two_points(a, b);
        if (d_bc >= d_ab && d_bc >= d_ca) return circle_from_two_points(b, c);
        return circle_from_two_points(c, a);
    }
    Point center;
    center.x = ((a.x * a.x + a.y * a.y) * (b.y - c.y) + (b.x * b.x + b.y * b.y) * (c.y - a.y) + (c.x * c.x + c.y * c.y) * (a.y - b.y)) / D;
    center.y = ((a.x * a.x + a.y * a.y) * (c.x - b.x) + (b.x * b.x + b.y * b.y) * (a.x - c.x) + (c.x * c.x + c.y * c.y) * (b.x - a.x)) / D;
    return {center, dist_sq(a, center)};
}

Circle min_enclosing_circle(std::vector<Point>& points) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(points.begin(), points.end(), g);

    if (points.empty()) return {{0, 0}, 0};
    if (points.size() == 1) return {points[0], 0};

    Circle c = circle_from_two_points(points[0], points[1]);

    for (size_t i = 2; i < points.size(); ++i) {
        if (dist_sq(points[i], c.center) <= c.radius_sq + EPS) continue;

        c = {points[i], 0}; 
        c = circle_from_two_points(points[0], points[i]);
        
        for (size_t j = 1; j < i; ++j) {
            if (dist_sq(points[j], c.center) <= c.radius_sq + EPS) continue;

            c = circle_from_two_points(points[i], points[j]);
            for (size_t k = 0; k < j; ++k) {
                if (dist_sq(points[k], c.center) <= c.radius_sq + EPS) continue;
                c = circle_from_three_points(points[i], points[j], points[k]);
            }
        }
    }
    return c;
}

int main() {
    int n;
    cin >> n;
    vector<Point> pt(n);
    for (auto &i : pt) cin >> i.x >> i.y;
    Circle ans = min_enclosing_circle(pt);
    cout << fixed << setprecision(10);
    cout << sqrt(ans.radius_sq) << '\n';
    cout << ans.center.x << ' ' << ans.center.y << '\n';
}
