#include <bits/stdc++.h>
#define all(x) x.begin() , x.end()
#define sz(x) (x.size())
#define rep(i,j,k) for(i =  j ; i<=k  ; i++)
#define eb emplace_back
#define fi first
#define se second
#define lim 100001
#define idx(x) (lv[x] - lv[root[inc[x]]])
 using namespace std;
 vector<int> G[lim] , chain[lim];
 int par[lim] , heavy[lim] ,subt[lim] = {}, lv[lim]={} ,inc[lim],root[lim];
 int dfs(int n){
  int i;
//  const vector<int> &vec = G[n];
  rep(i,0,sz(G[n])-1){
   if(par[n]!=G[n][i]){
    lv[G[n][i]] = lv[n]+1;
    par[G[n][i]] = n;
    subt[n] += dfs(G[n][i]);
   }
  }
 return ++subt[n];
 }
 int ch = 0;
 int hld(int n){
  int i , hev = 0;
//  cout << "Add " << n << "In Chain " << ch << endl;
  chain[ch].eb(n);
  inc[n] = ch;
  rep(i,0,sz(G[n])-1){
    if(G[n][i]!=par[n]){
   hev = (subt[hev]<subt[G[n][i]])? G[n][i] : hev;
   }
  }
  if(hev){
  heavy[n] = hev;
  hld(hev);
  }
  rep(i,0,sz(G[n])-1){
   if(G[n][i]!=par[n] and G[n][i] != hev){
        ch++;
        root[ch] = G[n][i];
        hld(G[n][i]);
   }
  }
 }
 class segtree{
  vector<int> st,lz;
  build(int p,int l ,int r){
   if(l==r){
    st[p] = 0;
   }else{
    build(p*2 , l , (l+r)/2);
    build(p*2 + 1 , (l+r)/2 + 1 , r);
    st[p] = st[p*2 ] + st[p*2 + 1];
   }
  }
  public:
  int rmq(int p,int l,int r,int a,int b){
   if(a> r || b < l) return  0;
   if(lz[p]!=0){
     st[p] += lz[p];
     if(l!=r){
        lz[p*2] += lz[p];
        lz[p*2 + 1] += lz[p];
     }
    lz[p] = 0;
   }
   if(a<=l and r <= b) return st[p];
   int p1 = rmq(p*2 , l , (l+r)/2 ,a , b);
   int p2 = rmq(p*2 + 1 , (l+r)/2 + 1 , r , a,  b);
   return p1 + p2;
  }
  void add(int p ,int l,int r,int a, int b){
//      cout << p << " " << l << " "<< r << " " << a <<" " << b << endl;
   if(lz[p]!=0){
    st[p] += (r - l +1 )* lz[p];
    if(l!=r){
        lz[p*2] += lz[p];
        lz[p*2 + 1 ] += lz[p];
    }
    lz[p] = 0;
   }
   if(b < l || a > r) return;
   if(a<=l and r <= b){
    st[p] += (r-l+1);
    if(l!=r){
        ++lz[p*2] , ++lz[p*2 + 1];
    }
    return ;
   }else{
    add(1, l ,(l+r)/2 , a , b );
    add(1 , (l+r)/2 + 1 , r , a , b);
    st[p] = st[p*2] + st[p*2 + 1 ];
   }
  }
  segtree(int num){
//      cout << "Chain "<<num << " Size "<< sz(chain[num]) << endl;
   st.resize(sz(chain[num])*2 + 1);
   lz.resize(sz(chain[num])*2 + 1);
   fill(all(lz) , 0);
   build(1,0,sz(chain[num])-1);
  }

 };
 vector<segtree> vs;
 int run_b(int a,int b){
     if(a==b) return 0;
   if(inc[a]!=inc[b]){
     return (lv[root[inc[a]]] < lv[root[inc[b]]])? vs[inc[b]].rmq(1,0,sz(chain[inc[b]])-1,0,idx(b))  + run_b(a,par[root[inc[b]]])
            : vs[inc[a]].rmq(1,0,sz(chain[inc[a]])-1 , 0, idx(a)) + run_b(par[root[inc[a]]],b);
   }else{
     return (idx(a) < idx(b))? vs[inc[a]].rmq(1,0,sz(chain[inc[a]])-1, idx(a)+1,idx(b))
            : vs[inc[a]].rmq(1,0,sz(chain[inc[a]])-1,idx(b)+1 , idx(a) ) ;
   }
 }
 void  run_a(int a, int b){
//     cout << a <<" "<< b << endl;
    if(a==b) return;
  if(inc[a]!= inc[b]){
//        cout << "unequal" << inc[a] <<" "<<inc[b] << endl;
        if(lv[root[inc[a]]] < lv[root[inc[b]]]) {
//                cout << sz(chain[inc[b]])<<" "<<idx(b) <<endl;
                vs[inc[b]].add(1,0,sz(chain[inc[b]])-1,0,idx(b)) ,  run_a(a,par[root[inc[b]]]);
        }
        else {
                vs[inc[a]].add(1,0,sz(chain[inc[a]])-1 , 0, idx(a)) ,  run_a(par[root[inc[a]]],b);
        }
  }else{
//        cout << "equal" << inc[a] << endl;
   (idx(a) < idx(b))? vs[inc[a]].add(1,0,sz(chain[inc[a]])-1, idx(a)+1,idx(b))
            : vs[inc[a]].add(1,0,sz(chain[inc[a]])-1,idx(b)+1 , idx(a) ) ;
  }
 }
 int main(){
  int V,Q;
  cin >> V >> Q;
  int i , j;
  rep(i,0,V-2){
   int A,B;
   cin >> A >> B;
   G[A].eb(B);
   G[B].eb(A);
  }
  par[1] = 1;
  subt[0] = -1;
  dfs(1);
  root[0] = 1;
  hld(1);
  rep(i,0,ch){
   vs.eb(i);
  }
  rep(i,0,Q-1){
   string a;
   int r, s;
   cin >> a >> r >>s ;
   //cout << a ;
   if(a[0] == 'A'){
     run_a(r,s);
   }else{
     cout << run_b(r,s);
   }
}
 }
