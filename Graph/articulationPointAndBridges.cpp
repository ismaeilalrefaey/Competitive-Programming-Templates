vector< bool > articulation_vertex;
vector< int > dfs_parent;
vector< int > dfs_low;
vector< int > dfs_num;
int dfsNumberCounter;
int rootChildren;
int dfsRoot;

void init()
{
	dfsRoot = 0;
	rootChildren = 0;
	dfsNumberCounter = 0;
	dfs_low.assign(n ,0);
	dfs_num.assign(n ,0);
	dfs_parent.assign(n ,-1);
	articulation_vertex.assign(n ,false);
}

void articulationPointAndBridges(int u)
{
	dfs_num[u] = dfs_low[u] = dfsNumberCounter++;
	
	for(auto v : al[u])
	{
		if( dfs_num[v] == 0 )
		{
			dfs_parent[v] = u;
			rootChildren += (u == dfsRoot);
			
			articulationPointAndBridges(v);
			
			if( dfs_low[v] >= dfs_num[u] ){
				articulation_vertex[u] = true;
			}
			if( dfs_low[v] > dfs_num[u] ){
				// (u ,v) is Bridge
			}
			
			dfs_low[u] = min(dfs_low[u] ,dfs_low[v]);
		}
		else if( v != dfs_parent[u] ) dfs_low[u] = min(dfs_low[u] ,dfs_num[v]);
	}
	
	if( u == dfsRoot ) articulation_vertex[u] = (rootChildren > 1);
}
