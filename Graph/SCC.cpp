#include <bits/stdc++.h>
using namespace std;

typedef long double 	ld;
typedef long long 		ll;
typedef pair<int , int> ii;
typedef pair<int , ii> iii;
typedef pair<ll , ll>  pll;
typedef vector< int >   vi;
typedef vector< ll >    vl;
typedef vector< ii >   vii;
typedef vector< pll >  vll;

#define FastIO cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
#define LSOne(a) ( (a) & -(a) )
#define SQ(a) (a)*(a)
#define INF  ll(4e18)
#define OO   int(1e9)
#define EPS      1e-9
#define PB  push_back
#define MP  make_pair
#define lf   (p << 1)
#define rg   (lf | 1)
#define S      second
#define F 		first

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

// ------------------------------------- //
// ============= Tarajan =============== //

vector< int > Scc; // what is the Scc number of u

vector< vector< int > > al2;
vector< vector< int > > al1;
int n ,m;

int numSCC ,dfsNumberCounter;
vector< bool > visited;
vector< int > dfs_num;
vector< int > dfs_low;
stack< int > St;
 
void init()
{
	dfs_num.assign(n ,0);
	dfs_low.assign(n ,0);
	visited.assign(n ,false);
	while( !St.empty() ) St.pop();
	dfsNumberCounter = numSCC = 0;
	
	al1.assign(n ,vector< int >());
	al2.assign(n ,vector< int >());
	
	Scc.assign(n ,-1);
}
 
void tarjanSCC(int u)
{
	St.push(u);
	visited[u] = true;
	dfs_num[u] = dfs_low[u] = dfsNumberCounter++;
	
	for(int v : al1[u])
	{
		if( dfs_num[v] == 0 ) {
			tarjanSCC(v);
		}
		
		if( visited[v] ) {
			dfs_low[u] = min(dfs_low[u] ,dfs_low[v]);
		}
	}
	
	if( dfs_num[u] == dfs_low[u] )
	{
		numSCC += 1;
		while( true )
		{
			int v = St.top(); St.pop();
			
			Scc[v] = numSCC;
			visited[v] = false;
			
			if( v == u ) break;
		}
	} 
}
 
// merge way diff from problem to another
void makeNewGraph()
{
	for(int u = 0 ; u < n ; u++)
	{
		int U = Scc[u];
		for(int v : al1[u])
		{
			int V = Scc[v];
			if( U != V )
			{
				al2[U].push_back(V);
				al2[U].push_back(U);
			}
		}
	}
}

// -------------------------------------- //
// ============= Kosaraju =============== //


vector< vector< int > > al ,al_t;
vector< int > dfs_num ,S;
int n ,m;

void init()
{
	S.clear();
	dfs_num.assign(n ,0);
	al.assign(n ,vector< int >());
	al_t.assign(n ,vector< int >());
}

void kosaraju1(int u)
{
	dfs_num[u] = 1;
	
	for(int v : al[u]) if( !dfs_num[v] ) kosaraju1(v);
	
	S.push_back(u);
}

void kosaraju2(int u ,UnionFind &UF)
{
	dfs_num[u] = 1;
	
	for(int v : al_t[u]) if( !dfs_num[v] )
	{
		UF.unionSet(u ,v);
		kosaraju2(v ,UF);
	}
}

void Solve()
{
	scanf("%d%d" ,&n ,&m);
	
	init();
	while( m-- )
	{
		int u; scanf("%d" ,&u); u--;
		int v; scanf("%d" ,&v); v--;
		al_t[v].push_back(u); // Note This
		al[u].push_back(v);
	}
	
	for(int i = 0 ; i < n ; i++)
		if( !dfs_num[i] )
			kosaraju1(i);
	
	UnionFind UF(n);
	dfs_num.assign(n ,0);
	for(int i = n - 1 ; i >= 0 ; i--)
		if( !dfs_num[ S[i] ] )
			kosaraju2(S[i] ,UF);
}

int main()
{
	
}
