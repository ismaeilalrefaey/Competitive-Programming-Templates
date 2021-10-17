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

/// --- Fenwick Tree --- ///
class FenTree
{
	/// --- Note: Every Thing Is long long Here --- ///
	private:
		vector< long long > ft;
	
	public:
		FenTree(int m)
		{
			ft.assign(m + 1 ,0ll);
		}
		
		FenTree(const vector< long long > &f)
		{
			// build FenTree from a cnt array
			BLD(f);
		}
		
		FenTree(const vector< long long > &a ,int m)
		{
			// make a cnt array then build FenTree from the cnt array
			vector< long long > f(m + 1 ,0ll);
			for(auto i : a) f[i] += 1;
			BLD(f);
		}
		
		void BLD(const vector< long long > &f)
		{
			// build FenTree from a cnt array
			int m = (int)f.size() - 1;  // f[0] = 0;
			
			ft.assign(m + 1 ,0ll);
			for(int i = 1 ; i <= m ; i++)
			{
				ft[i] += f[i];
				if( i + LSOne(i) <= m ){
					ft[i + LSOne(i)] += ft[i];
				}
			}
		}
		
		ll QRY(int j)
		{
			ll sum = 0;
			while(j)
			{
				sum += ft[j];
				j -= LSOne(j);
			}
			
			return sum;
		}
		
		ll QRY(int i ,int j)
		{
			// (inc/exc)lusion
			return QRY(j) - QRY(i - 1);
		}
		
		void UPD(int i ,ll v)
		{
			while(i < (int)ft.size())
			{
				ft[i] += v;
				i += LSOne(i);
			}
		}

		int select1(int k)
		{
			// kth element in log2(N)
			int p = 1 ,i = 0;
			while( p * 2 < (int)ft.size() ) p *= 2;
			
			while( p ) 
			{
				if( i + p < (int)ft.size() )
				{
					if( k > ft[i + p] ) 
					{
						k -= ft[i + p];
						i += p;
					}
				}
				
				p /= 2;
			}
			
			return i + 1;
		}

		int select2(int k)
		{
			// kth element in log2(N) ^ 2
			int loop = 23;
			int L = 1 ,R = (int)ft.size() - 1;
			
			while( loop -- )
			{
				int Mid = (L + R) >> 1;
				(QRY(Mid) >= k) ? R = Mid 
				   		        : L = Mid;
			}
			
			return R;
		}
};

/// --- Range Update Point Query --- ///
class RUPQ
{
	private:
		FenTree ft;
		
	public:
		RUPQ(int m) : ft(FenTree(m)) {}
		
		void rangeUPD(int i ,int j ,ll v)
		{
			ft.UPD(  i   ,+v);
			ft.UPD(j + 1 ,-v);
		}
		
		ll pointQRY(int i)
		{
			return ft.QRY(i);
		}
};

/// --- Range Update Range Query --- ///
class RURQ
{
	private:
		FenTree purq;
		RUPQ rupq;
		
	public:
		RURQ(int m) :purq(FenTree(m)) ,rupq(RUPQ(m)){}
		
		void rangeUPD(int i ,int j ,ll v)
		{
			rupq.rangeUPD(i ,j ,v);
			purq.UPD(  i   ,+v * (i - 1));
			purq.UPD(j + 1 ,-v * j);
		}
		
		ll QRY(int j)
		{	
			return rupq.pointQRY(j) * j - purq.QRY(j);
		}
		
		ll QRY(int i ,int j)
		{
			return QRY(j) - QRY(i - 1);
		}
};

int main() 
{
	
    return 0;
}
