int np[mxN], d[mxN], num[mxN];
vector<int> prime;
 
void build(int n) {
    d[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(np[i] == 0) { // is prime
            np[i] = i;
            d[i] = 2;
            num[i] = 1; // number of smallest prime divisor
            prime.pb(i);
        }
        for(int j : prime) {
            if(j * i > n) break;
            np[j * i] = j;
            if(np[i] == j) {
                num[i * j] = num[i] + 1;
                d[i * j] = d[i] / (num[i] + 1) * (num[i] + 2);
                break;
            } else {
                num[i * j] = 1;
                d[i * j] = d[i] * 2; // d[i * j] = d[i] * (num[i * j] + 1)
            }
        }
    }
}
