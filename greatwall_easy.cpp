#include <bits/stdc++.h>
 
  using namespace std;
   const int lim = 1e5+10;
   typedef long long int lli;
   lli arr[lim];
   lli gcd(lli a , lli b){  // ËÒ ËÃÁ »¡µÔ¹Ñè¹áËÅÐ
     while(b != 0){
         lli t = a%b ;
         a = b;
         b = t;
     }
     return a;
   }
   int main(){
     int n ;
     scanf("%d",&n);
     for(int i = 0 ; i < n ;i++){
         scanf("%lld",&arr[i]);
     }
     lli tmp = arr[0] ; // Start GCD
     for(int i = 1 ; i <n  ; i++){
         tmp = gcd(tmp , arr[i]);
     }
     lli sum = 0 ;
     for(int i = 0 ; i < n ; i++){
         sum += arr[i]/tmp;
     }
     printf("%lld",sum);
   }
