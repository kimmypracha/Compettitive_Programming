#include <bits/stdc++.h>
#define rep(i , j , k ) for(int i = j ; i <= k ; ++i)
#define input() (*istream_iterator<int>(cin))
 using namespace std;
  const int lim = 1e5+10;
  typedef long long int lli;
  lli arr[lim];
  lli gcd(lli a , lli b){  // หา หรม ปกตินั่นแหละ
    return (!b)? a : gcd(b , a%b);
  }
  int main(){
    int n  = input();
    lli tmp ,sum = 0;
    rep(_i , 0 ,n-1){
        scanf("%lld",&arr[_i]);
        tmp = (not _i)? arr[0] : gcd(tmp , arr[_i]);
    }
    rep(_i , 0 , n-1){
        sum += arr[_i]/tmp;
    }
    printf("%lld",sum);
  }
