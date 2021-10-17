#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ii;
typedef vector<ii> vii;

int main()
{
                             /// --- (3) 2nwa3 ltmthel al graph --- ///

/// ================================== START OF ADJ-MATRIX TYPE ================================== ///

    int V;
    int AdjMat[100][100];
/*
    NOTE : size not more than AdjMat[1000][1000]; => 1000 * 1000 = 1000000;

    ( AdjMat[i][j] = 0 ) => unweighted edge
    ( AdjMat[i][j] > 0 ) => weighted edge

    /// --- START OF INPUT --- ///
          6
          0  10   0   0 100   0
         10   0   7   0   8   0
          0   7   0   9   0   0
          0   0   9   0  20   5
        100   8   0  20   0   0
          0   0   0   5   0   0

    /// --- END OF INPUT --- ///
*/

    cin >> V;
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> AdjMat[i][j];

    cout << "Neighbors of vertex (0) :" << endl;
    for (int j = 0; j < V; j++)
        if (AdjMat[0][j])
            cout << "Edge 0-" << j << " weight = " << AdjMat[0][j] << endl;

/// ================================== END OF ADJ-MATRIX TYPE ================================== ///



/// ================================== START OF ADJ-LIST TYPE ================================== ///

    int total_neighbors, id, weight;
    vector<vii> AdjList; /// vector < vector < pair<int,int> > >AdjList;
/*
    for each line: num neighbors  list of neighbors + weight pairs
                         2                   2             10       <=  first neighbor with weight
                                             5             100      <= second neighbor with weight

    /// --- START OF INPUT --- ///
        6
        2 2 10 5 100
        3 1 10 3 7 5 8
        2 2 7 4 9
        3 3 9 5 20 6 5
        3 1 100 2 8 4 20
        1 4 5
    /// --- END OF INPUT --- ///
*/
    cin >> V;
    AdjList.assign(V, vii()); // quick way to initialize AdjList with V entries of vii
    for (int i = 0; i < V; i++) {
        cin >> total_neighbors;
        for (int j = 0; j < total_neighbors; j++) {
            cin >> id >> weight;
            AdjList[i].push_back( make_pair(id - 1, weight) );   // some index fix
        }
    }

    cout << "Neighbors of vertex (0) :" << endl;
    for (auto j = AdjList[0].begin() ; j != AdjList[0].end() ; j++)
        cout << "Edge 0-" << j->first << " weight = " << j->second << endl;

/// ================================== END OF ADJ-LIST TYPE ================================== ///



/// ================================== START OF EDGE-LIST TYPE ================================== ///

    int E, a, b;
    priority_queue< pair<int, ii> > EdgeList; /// priority_queue< weight , < a , b > > EdgeList;
/*
    for each line: a-b of edge(a,b) and weight
    /// --- START OF INPUT --- ///
        7
        1 2 10
        1 5 100
        2 3 7
        2 5 8
        3 4 9
        4 5 20
        4 6 5
    /// --- END OF INPUT --- ///
*/
    cin >> E;
    for (int i = 0; i < E; i++){
        cin >> a >> b >> weight ;
        EdgeList.push( { -weight, {a, b} } ); // trick to reverse sort order
    }
/*
        NOTE :
           the EdgeList sorted in decreasing order
           (so we when cin >> wight; ) we push it in EdgeList ( -wight );
           in this trick we put the largest weight in the last and, the lowest weight in the front of EdgeList;

     edges sorted by weight (smallest->largest)
*/

    for (int i = 0; i < E; i++) {
        pair<int, ii> edge = EdgeList.top();
        EdgeList.pop();
        cout << "weight: " << -edge.first /// -- negate the weight again to out put the right weight ;
             << " ( " <<edge.second.first << " - " << edge.second.second << " ) "
             << endl;
    }

/// ================================== END OF EDGE-LIST TYPE ================================== ///
    return 0;
}
