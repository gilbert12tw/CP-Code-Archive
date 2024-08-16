inline bool cmp(array<int, 3> a, array<int, 3> b){
    if(a[0] / bsz == b[0] / bsz) {
        if ((a[0] / bsz) & 1) return a[1] < b[1];
        else return a[1] > b[1];
    }
    return a[0] < b[0];
}

inline void add(int pos){
    now = now + mp[sum[pos] ^ k];
    mp[sum[pos]]++;
}

inline void del(int pos){
    mp[sum[pos]]--;
    now = now - mp[sum[pos] ^ k];
}

void MO(){
    bsz = max(sqrt(n), n / sqrt(m));
    sort(all(v), cmp);
    int l = 1, r = 0;
    for(int i = 0; i < m; i++){
        while(l > v[i][0]) add(--l);
        while(l < v[i][0]) del(l++);
        while(r < v[i][1]) add(++r);
        while(r > v[i][1]) del(r--);
    }
}
