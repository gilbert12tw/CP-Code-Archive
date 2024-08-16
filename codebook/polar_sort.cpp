int sgn(point a) {
	if (a.X >= 0 and a.Y >= 0) return 1;
	if (a.X <= 0 and a.Y >= 0) return 2;
	if (a.X <= 0 and a.Y <= 0) return 3;
	return 4;
}

bool cmp(point a, point b) {
	if (sgn(a) == sgn(b)) return cross(a - o, b - o) >= 0;
	return sgn(a) < sgn(b);
}
