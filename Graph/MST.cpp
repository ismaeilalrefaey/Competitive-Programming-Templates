// ------------------------------------- //
// ============= Kruskal =============== //

class UnionFind
{
	private:
		vector< int > p;
		int numSet;

	public:
		UnionFind(int _N)
		{
			numSet = _N;
			p.resize(_N); for(int i = 0 ; i < _N ; ++i) p[i] = i;
		}
					
		int numDisjointSets()
		{
			return numSet;
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
			p[ findSet(j) ] = findSet(i);
			numSet -= 1;  
		}
};

vector< vi > mstAl;   // MST Adj List
map< ii , ll > mstEL; // MST Edg List

ll Kruskal(vector< iii > EL) // Orginal Edg List
{
	ll mstCost = 0;
	
	UnionFind UF(n);
 
	sort(EL.begin() ,EL.end());
 
	for(auto i : EL)
	{
		int u = i.S.F;
		int v = i.S.S;
 
		if( !UF.isSameSet(u ,v) )
		{
			mstCost += i.F;
			UF.unionSet(u ,v);
 
			mstAL[u].PB(v);
			mstAL[v].PB(u);
			mstEL[ pll(u ,v) ] = i.F;
			mstEL[ pll(v ,u) ] = i.F;
		}
	}
	
	return mstCost;
}

// ---------------------------------- //
// ============= Prim =============== //

 
priority_queue< ii , vii , greater< ii > > pq;
vector< vii > al;


void process(int u)
{
	vis[u] = true;
	for(ii v : al[u])
		if( !vis[v.F] )
			pq.push( ii(v.S ,v.F) );
}

int main()
{
	// ....
	// ....
	
	
	vis.assign(n ,false);
	process(0);
	
	ll mstCost = 0;
	while( !pq.empty() )
	{
		int u = pq.top().S;
		int w = pq.top().F;
		pq.pop();
		
		if( !vis[u] )
		{
			mstCost += w;
			process(u);
		}
	}
	
}
