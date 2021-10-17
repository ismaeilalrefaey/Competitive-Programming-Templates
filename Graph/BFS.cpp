// ---------------------------- // 
// ============ BFS =========== //

vector< int > BFS(int s)
{
    vector< int > dist(n ,-1);
    queue< int > q;

    dist[s] = 0;
    q.push(s);

    while( !q.empty() )
    {
        int u = q.front(); q.pop();

        for(int v : al[u]) if( dist[v] == -1 )
        {
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
	
    return dist;
}
