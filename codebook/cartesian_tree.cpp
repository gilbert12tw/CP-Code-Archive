struct Cartesian_Tree { // Root is Maximum
    int n, root;
    vector<int> w, rs, ls;
    Cartesian_Tree(int _n): n(_n), root(-1), rs(n, -1), ls(n, -1) {}

    void build(const vector<int> &we) {
        w = we;                 
        vector<int> stk;         
        for (int i = 0; i < n; i++) {
            int last = -1;
            while (!stk.empty() && w[stk.back()] < w[i]) {
                last = stk.back();
                stk.pop_back();
            }
            if (stk.empty()) {
                root = i;
            } else {
                rs[stk.back()] = i;
            }
            if (last != -1) {
                ls[i] = last;
            }
            stk.push_back(i);
        }
    }
};
