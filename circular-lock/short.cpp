#include <bits/stdc++.h>
using namespace std;
int g(int a,int b){
    return b==0?a:g(b,a%b);
}
int main(){
    int n,a,b,p,q,c,d,r,s;cin>>n;
    while(n--){cin>>a>>b>>p>>q>>c>>d>>r>>s;cout<<((a-b-c+d)%g(g(g(p,q),r),s)?"No\n":"Yes\n");}
    return 0;
}