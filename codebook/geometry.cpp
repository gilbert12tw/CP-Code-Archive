struct PT {
    int x,y;
    PT(){}
    PT(const int&x,const int&y):x(x),y(y){}
    PT operator+(const PT &b)const{
        return PT(x+b.x,y+b.y);
    }
    PT operator-(const PT &b)const{
        return PT(x-b.x,y-b.y);
    }
    PT operator*(const int &b)const{
        return PT(x*b,y*b);
    }
    PT operator/(const int &b)const{
        return PT(x/b,y/b);
    }
    bool operator==(const PT &b)const{
        return x==b.x&&y==b.y;
    }
    int dot(const PT &b)const{
        return x*b.x+y*b.y;
    }
    int cross(const PT &b)const{
        return x*b.y-y*b.x;
    }
    int abs2()const{//向量長度的平方
        return dot(*this);
    }
};

// p2 in p1 -> p3
int btw(const PT &p1, const PT &p2, const PT &p3) {
    if ((p1 - p2).cross(p3 - p2) == 0 &&
            min(p1.x, p3.x) <= p2.x && p2.x <= max(p1.x, p3.x) &&
            min(p1.y, p3.y) <= p2.y && p2.y <= max(p1.y, p3.y)) return 1;
    return 0;
}

int sgn(int x) {
    if (x > 0) return 1;
    else if (x == 0) return 0;
    return -1;
}

int inter(const PT &a, const PT &b, const PT &c, const PT &d) {
    if(min(a.y, b.y) <= max(c.y, d.y) and min(c.y, d.y) <= max(a.y, b.y) and
            min(a.x, b.x) <= max(c.x, d.x) and min(c.x, d.x) <= max(a.x, b.x) and
            sgn((b - a).cross(c - a)) * sgn((b - a).cross(d - a)) <= 0 and
            sgn((d - c).cross(a - c)) * sgn((d - c).cross(b - c)) <= 0) return 1;
    return 0;
}

int area(const PT &a, const PT &b, const PT &c) {
    return abs((a-b).cross(c-b));
}
