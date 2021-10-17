#include <bits/stdc++.h>
using namespace std;

#define FastIO cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
#define LSOne(a) ( (a) & -(a) )
#define SQ(a) (a)*(a)
#define INF 	 4e18
#define EPS      1e-9
#define OO   	  1e9
#define PB  push_back
#define MP  make_pair
#define S      second
#define F 		first

typedef long double 	ld;
typedef long long 		ll;
typedef pair<int , int> ii;
typedef pair<int , ii> iii;
typedef pair<ll , ll>  pll;
typedef vector< int >   vi;
typedef vector< ll >    vl;
typedef vector< ii >   vii;
typedef vector< pll >  vll;

/// ------------------------------- ///

class UnionFind
{
	private:
		int numSet;
		vector< int > p;
		vector< int > rank;
		vector< int > setSize;
/* 
 * You Can Make Any vector And Store Information Of
 * Sets On The Root Of Set "like setSize above" 
 */
 
	public:
		UnionFind(int _N)
		{
			numSet = _N;
			rank.assign(_N ,0);
			setSize.assign(_N ,1);
			p.resize(_N); for(int i = 0 ; i < _N ; ++i) p[i] = i;
		}
					
		int numDisjointSets()
		{
			return numSet;
		}
		
		int sizeOfSet(int i)
		{
			return setSize[ findSet(i) ];
		}
		
		int findSet(int i)
		{
			return (p[i] == i) ? i : (p[i] = findSet(p[i]));
		}
		
		bool isSameSet(int i ,int j)
		{
			return findSet(i) == findSet(j);
		}
		
		void unionSet(int i ,int j)
		{
			if( isSameSet(i ,j) ) return;
			
			int x = findSet(i); 
			int y = findSet(j); 
			
			if( rank[x] > rank[y] ) swap(x ,y);
			p[x] = y;
			
			if( rank[x] == rank[y] ) rank[y] += 1;
			setSize[y] += setSize[x];
			numSet -= 1;  
		}
};

int main()
{
	return 0;
}
