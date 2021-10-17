class SparseTable
{
	private:
		vector< vector< pair<int , int> > > SpT;	// Sparse Table Matrix
	
		vector< int > order; 	// dfs order
		vector< int > depth; 	// vrx depth 

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
			SpT.assign(L[size] + 1 ,vector< pair<int , int> >(size));
			
			for(int i = 0 ; i < size ; i++) SpT[0][i] = make_pair(order[i] ,depth[i]);
			
			for(int j = 1 ; P[j] <= size ; j++)
			{
				for(int i = 0 ; i + P[j] - 1 < size ; i++)
				{
					pair<int , int> x = SpT[j - 1][i];
					pair<int , int> y = SpT[j - 1][i + P[j - 1]];
					
					if( x.second < y.second ) {
						SpT[j][i] = x;
					} else {
						SpT[j][i] = y;
					}
				} 
			}
		}
		
	public:
		SparseTable(vector< int > &order ,vector< int > &depth)
		{
			this -> order = order;
			this -> depth = depth;

			this -> size = (int)order.size();
			this -> logS = log2(size) + 1;
			
			init(); // init vectors P & L
			BLD();  // Building the SpT;
		}
		
		int QRY(int left ,int right)
		{
			/// --- {main} SpT.QRT(idx[u] ,idx[v]) && BE SURE: idx[v] >= idx[u] --- ///

			long long k = L[right - left + 1];
			
			pair<int , int> x = SpT[k][left];
			pair<int , int> y = SpT[k][right - P[k] + 1];

			pair<int , int> lca = x.second < y.second ? x : y;			
			return lca.first;
		}
};

vector< int > depth;
vector< int > order;
vector< int > idx;

void init()
{
	order.clear();
	depth.clear();
	idx.resize(n);
}

void DFS(int u ,int p ,int h)
{
	idx[u] = (int)order.size();
	order.push_back(u);
	depth.push_back(h);

	for(int v : al[u]) if( v != p )
    {
        DFS(v ,u ,h + 1);
        order.push_back(u);
        depth.push_back(h);
    }
}

