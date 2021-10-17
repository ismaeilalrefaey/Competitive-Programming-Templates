// --------------------------------- //
// ========== Normal DFS =========== //

vector< bool > dfs_num;

void init()
{
	dfs_num.assign(n ,false);
}

void DFS(int u)
{
	dfs_num[u] = true;
	for(auto v : al[u])
		if( !dfs_num[v] )
			DFS(v);
}

// ---------------------------------------- //
// ========== DFS Spanning Tree =========== //

vector< int > dfs_parent;
vector< bool > dfs_num;
vector< int > depth;
vector< int > dfsST;
vector< int > idx;

void init()
{
	dfsST.clear();
	idx.assign(n ,-1);
	depth.assign(n ,0);
	dfs_parent.assign(n ,-1);
	dfs_num.assign(n ,false);
}

void DFS(int u ,int p ,int h)
{
	dfs_num[u] = true;
	dfs_parent[u] = p;
	dfsST.push_back(u);
	depth.push_back(h);
	
	if( idx[u] == -1 ) idx[u] = (int)dfsST.size() - 1;
	
	for(auto v : al[u])
	{
		if( !dfs_num[v] )
		{
			DFS(v ,u ,h + 1);
			dfsST.push_back(u);
			depth.push_back(h);
		}
	}
}


// ------------------------------ //
// ========== DFS All =========== //
void dfsAll()
{
	for(int u = 0 ; u < n ; u++)
		if( !dfs_num[u] )
			DFS(u);
}
