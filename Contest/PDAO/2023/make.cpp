#include<bits/stdc++.h>
using namespace std;
int main(){
    srand(time(NULL));
    cout<<1<<endl;
    int n = rand()%50,d = rand()%10000+100;
    set<int>st;
    while(n--){
        int x = rand()%d+1;
        if(x==d)continue;
        st.insert(x);
    }
    cout<<st.size()<<' '<<d<<endl;
    for(auto i:st){
        cout<<(rand()%2==0?'R':'I')<<' '<<i<<endl;
    }
}
