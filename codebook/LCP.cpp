void cal_lcp() {
    int k = 0;
    for(int i = 0; i < n; i++) {
        k = max(0ll, k-1);
        if(c[i] == 0) continue;
        int p = sa[c[i]-1], j = i;
        while(p + k < n && j + k < n && s[p+k] == s[j+k]) k++;
        lcp[c[i]-1] = k;
    }
}
