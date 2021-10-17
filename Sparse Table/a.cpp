#include <bits/stdc++.h>

using namespace std;

class SparseTable
{
	private:
		vector< vector< long long > > SpT;	// Sparse Table Matrix
	
		vector< long long > A; 	// main array
		vector< long long > P; 	// power of 2
		vector< long long > L; 	// logtm of 2
		
		int size;	// size of array
		int logS; 	// log2 of size
		
		void init()
		{
			P.assign(logS + 1 ,0ll);
			L.assign((1ll << logS) + 1 ,0ll);
			
			for(int i = 0 ; i <= logS ; i++)
			{
				P[i] = (1ll << i);
				L[(1ll << i)] = i;
			}
			
			for(int i = 2 ; i <= P[logS] ; i++)
				if( L[i] == 0ll ) 
					L[i] = L[i - 1];
		}
		
		void BLD()
		{
			// build function able to change according to needed SpT
			SpT.assign(L[size] + 1 ,vector< long long >(size));
			
			for(int i = 0 ; i < size ; i++) SpT[0][i] = i;
			
			for(int j = 1 ; P[j] <= size ; j++)
			{
				for(int i = 0 ; i + P[j] - 1 < size ; i++)
				{
					long long x = SpT[j - 1][i];
					long long y = SpT[j - 1][i + P[j - 1]];
					
					if( A[x] < A[y] ) {
						SpT[j][i] = x;
					} else {
						SpT[j][i] = y;
					}
				} 
			}
			
		}
		
	public:
		SparseTable(vector< long long > &initA)
		{
			this -> A 	 = initA;
			this -> size = (int)initA.size();
			this -> logS = (int)log2(size)+1;
			
			init(); // init vectors P & L
			BLD();  // Building the SpT;
		}
		
		long long QRY(int left ,int right)
		{
			// return the idx in the orginal array A
			long long k = L[right - left + 1];
			
			long long x = SpT[k][left];
			long long y = SpT[k][right - P[k] + 1];
			
			if( A[x] < A[y] ) {
				return x;
			}
			
			return y;
		}
};

int main()
{
	int n;
	cin >> n;
	
	vector< long long > a(n);
	for(long long &i : a) cin >> i;
	
	fflush(stdin);
	
	SparseTable SpT(a);
	
	int q;
	cin >> q;
	while( q-- )
	{
		int L; cin >> L; L--;
		int R; cin >> R; R--;
		
		cout << a[ SpT.QRY(L ,R) ] << endl;
	}
	return 0;
}
