ll cross(const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
}

inline int get_region(const point &p) {
    if (p.x > 0 || (p.x == 0 && p.y > 0)) return 0;
    return 1;
}

bool cmp(const point &a, const point &b) {
    int ra = get_region(a), rb = get_region(b);
    if (ra != rb) return ra < rb;
    return cross(a, b) < 0; // clockwise
}
