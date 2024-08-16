template<typename T>
struct Matrix {
	using rt = std::vector<T>;
	using mt = std::vector<rt>;
	using matrix = Matrix<T>;
	int r,c; mt m;
	Matrix(int r,int c):r(r),c(c),m(r,rt(c)){}
    Matrix(mt &m_): m(m_) {
        r = m.size(); c = m[0].size();
    }
	rt& operator[](int i){return m[i];}
	matrix operator+(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]+a.m[i][j];
		return rev;
	}
	matrix operator-(const matrix &a){
		matrix rev(r,c);
		for(int i=0;i<r;++i)
			for(int j=0;j<c;++j)
				rev[i][j]=m[i][j]-a.m[i][j];
		return rev;
	}
	matrix operator*(const matrix &a){
		matrix tmp(a.c,a.r); int s;
        for (int i = 0; i < r; i++) 
            for (int k = 0; k < c; k++) {
                s = m[i][k];
                for (int j = 0; j < a.c; j++) {
                    tmp.m[i][j] += s * a.m[k][j] % mod;
                    if (tmp.m[i][j] >= mod)
                        tmp.m[i][j] %= mod;
                }
            }
		return tmp;
	}
    matrix operator^(long long b) {
        matrix a(m), res(r, c);
        bool first = 1;
        while (b) {
            if (b&1) {
                if (first) res = a;
                else res = res * a;
                first = 0;
            }
            a = a * a; b >>= 1;
        }
        return res;
    }
    void print() {
        cout << '\n';
        for (int i=0; i<r; i++) {
            cout<<"[";
            for (int j=0; j<c; j++)
                cout<<m[i][j]<<" ]"[j==c-1];
            cout<<"\n";
        }
        cout << '\n';
    }
	bool inverse(){
		Matrix t(r,r+c);
		for(int y=0;y<r;y++){
			t.m[y][c+y] = 1;
			for(int x=0;x<c;++x)
				t.m[y][x]=m[y][x];
		}
		if( !t.gas() )
			return false;
		for(int y=0;y<r;y++)
			for(int x=0;x<c;++x)
				m[y][x]=t.m[y][c+x]/t.m[y][y];
		return true;
	}
	T gas(){
		vector<T> lazy(r,1);
		bool sign=false;
		for(int i=0;i<r;++i){
			if( m[i][i]==0 ){
				int j=i+1;
				while(j<r&&!m[j][i])j++;
				if(j==r)continue;
				m[i].swap(m[j]);
				sign=!sign;
			}
			for(int j=0;j<r;++j){
				if(i==j)continue;
				lazy[j]=lazy[j]*m[i][i];
				T mx=m[j][i];
				for(int k=0;k<c;++k)
					m[j][k]=m[j][k]*m[i][i]-m[i][k]*mx;
			}
		}
		T det=sign?-1:1;
		for(int i=0;i<r;++i){
			det = det*m[i][i];
			det = det/lazy[i];
			for(auto &j:m[i])j/=lazy[i];
		}
		return det;
	}
};

