bool inter(point a, point b, point c, point d) {
	if(min(a.y, b.y) <= max(c.y, d.y) and min(c.y, d.y) <= max(a.y, b.y) and
	   min(a.x, b.x) <= max(c.x, d.x) and min(c.x, d.x) <= max(a.x, b.x) and
	   cross(b - a, c - a) * cross(b - a, d - a) <= 0 and 
	   cross(d - c, a - c) * cross(d - c, b - c) <= 0) return 1;
	return 0;
}
