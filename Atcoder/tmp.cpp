#include <bits/stdc++.h>
using namespace std;
const long long INF = 1000000000000000;
int main(){
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    for (int i = 0; i < N; i++){
        cin >> A[i];
    }
    vector<long long> S(N - K + 1, 0);
    for (int i = 0; i <= N - K; i++){
        for (int j = 0; j < K; j++){
            S[i] += A[i + j];
        }
    }
    auto conv = [&](vector<long long> X, vector<long long> Y){
        int n = X.size(), m = Y.size();
        vector<long long> Z(n + m - 1, -INF);
        Z[0] = X[0] + Y[0];
        int p = 0, q = 0;
        for (int i = 1; i < n + m - 1; i++){
            if (p == n - 1){
                q++;
            } else if (q == m - 1){
                p++;
            } else if (X[p + 1] - X[p] > Y[q + 1] - Y[q]){
                p++;
            } else {
                q++;
            }
            Z[i] = X[p] + Y[q];
        }
        return Z;
    };
    auto rec = [&](auto rec, int L, int R) -> vector<vector<vector<long long>>>{
        int M = (R - L) / K;
        vector<vector<vector<long long>>> ans(K, vector<vector<long long>>(K, vector<long long>(M + 1, -INF)));
        for (int i = 0; i < K; i++){
            for (int j = 0; j < K; j++){
                if (i + j <= R - L){
                    ans[i][j][0] = 0;
                }
            }
        }
        if (K == 1 && R - L == 1){
            ans[0][0][0] = 0;
            ans[0][0][1] = A[L];
        } else if (M >= 1){
            int m = (L + R) / 2;
            vector<vector<vector<long long>>> ansL = rec(rec, L, m);
            vector<vector<vector<long long>>> ansR = rec(rec, m, R);
            for (int i = 0; i < K; i++){
                for (int j = 0; j < K; j++){
                    if (L == 0 && i > 0 || R == N && j > 0){
                        continue;
                    }
                    vector<long long> LR = conv(ansL[i][0], ansR[0][j]);
                    for (int k = 0; k < LR.size(); k++){
                        ans[i][j][k] = max(ans[i][j][k], LR[k]);
                    }
                    for (int k = 1; k < K && k <= m; k++){
                        LR = conv(ansL[i][k], ansR[K - k][j]);
                        for (int l = 0; l < LR.size() && l < M; l++){
                            ans[i][j][l + 1] = max(ans[i][j][l + 1], LR[l] + S[m - k]);
                        }
                    }
                }
            }
        }
        return ans;
    };
    vector<vector<vector<long long>>> ans = rec(rec, 0, N);
    for (int i = 1; i <= N / K; i++){
        cout << ans[0][0][i];
        if (i < N / K){
            cout << ' ';
        }
    }
    cout << endl;
}
