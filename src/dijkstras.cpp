#include "dijkstras.h"
#include <queue>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) { 
    int numV = G.size();
    vector <int> vDist (numV , INF);
    vector <bool> visitedV (numV, false);

    vDist[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int,int>> minHeap; //   node, distance
    minHeap.push({0, source});

    while ( !minHeap.empty()) { 
        auto currVmin = minHeap.top();
        minHeap.pop();
        int currV = currVmin.second;
        int dst = -currVmin.first;

        if (visitedV[currV]) { continue; }
        visitedV[currV] = true;

        for (Edge e : G[currV]) { 
            int adjcntTo = e.dst;
            int eWeight = e.weight;

            if (!visitedV[adjcntTo] && dst + eWeight < vDist[adjcntTo]) { 
                vDist[adjcntTo] = dst + eWeight;
                previous[adjcntTo] = currV;
                minHeap.push ({-vDist[adjcntTo], adjcntTo});
            }
        }
    }
    return vDist;
}
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) { 
    vector <int> currPath;
    int currV = destination;

    while (currV != -1) { 
        currPath.push_back(currV);
        currV = previous[currV];
    }

    return currPath;
}
void print_path(const vector<int>& v, int total) { 
    for (int i = 0; i < v.size(); i++) { 
        cout << v[i] << " "; 
    }
    cout <<  endl;
    cout << "Total cost is " << total <<endl;
}