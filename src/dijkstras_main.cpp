#include "dijkstras.h"
#include <iostream>

int main () { 

    Graph G;
    file_to_graph("src/small.txt", G);

    if (G.numVertices == 4) { 
        cout << "PASSED" <<endl;
    }

    vector<int> previous(G.numVertices, -1);
    vector<int> dist = dijkstra_shortest_path(G, 0, previous);
    cout << "Distance from 0 to 3 should be 1" <<endl;
    cout << ((dist[3] == 1) ? "PASSED" : "FAILED") << endl;

    cout << "Distance from 0 to 1 should be 3 (via 0->3->1)" << endl;
    cout << ((dist[1] == 3) ? "PASSED" : "FAILED") << endl;

    cout << "Distance from 0 to 2 should be 6 (via 0->3->1->2)" <<endl;
    cout << ((dist[2] == 6) ? "PASSED" : "FAILED") << endl;

    vector<int> path = extract_shortest_path(dist, previous, 2);
    vector<int> expectedPath = {0, 3, 1, 2};
    cout << ((path == expectedPath) ? "PASSED" : "FAILED") << endl;

}