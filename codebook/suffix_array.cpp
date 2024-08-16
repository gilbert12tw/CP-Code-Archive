#define radix_sort(x,y){\
	for(i=0;i<A;++i)c[i]=0;\
	for(i=0;i<n;++i)c[x[y[i]]]++;\
	for(i=1;i<A;++i)c[i]+=c[i-1];\
	for(i=n-1;~i;--i)sa[--c[x[y[i]]]]=y[i];\
}
#define AC(r,a,b)\
	r[a]!=r[b]||a+k>=n||r[a+k]!=r[b+k]
void suffix_array(const string &s,int *sa,int *rank,int *tmp,int *c){
	int A='z'+1,i,k,id=0,n=s.size();
	for(i=0;i<n;++i)rank[tmp[i]=i]=s[i];
	radix_sort(rank,tmp);
	for(k=1;id<n-1;k<<=1){
		for(id=0,i=n-k;i<n;++i)tmp[id++]=i;
		for(i=0;i<n;++i)
			if(sa[i]>=k)tmp[id++]=sa[i]-k;
		radix_sort(rank,tmp);
		swap(rank,tmp);
		for(rank[sa[0]]=id=0,i=1;i<n;++i)
			rank[sa[i]]=id+=AC(tmp,sa[i-1],sa[i]);
		A=id+1;
	}
}
//h:高度數組 sa:後綴數組 rank:排名 
void suffix_array_lcp(const string &s,int *h,int *sa,int *rank){
    int len = s.size();
	for(int i=0;i<len;++i)rank[sa[i]]=i;
	for(int i=0,k=0;i<len;++i){
		if(rank[i]==0)continue;
		if(k)--k;
		while(s[i+k]==s[sa[rank[i]-1]+k])++k;
		h[rank[i]]=k;
	}
	h[0]=0;// h[k]=lcp(sa[k],sa[k-1]);
}
const int mxL = 5e5 + 5;
int sa[mxL], rk[mxL], tmp[mxL], c[mxL], h[mxL];
