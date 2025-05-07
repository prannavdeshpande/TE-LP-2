#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Function to construct adjacency list
vector<vector<vector<int>>> constructAdj(vector<vector<int>> &edges, int V) {
    // adj[u] = list of {v, wt}
    vector<vector<vector<int>>> adj(V); 

    for (const auto &edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int wt = edge[2];
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt}); // For undirected graph
    }
    
    return adj;
}

// Dijkstra's algorithm to find shortest paths
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
    // Create adjacency list
    vector<vector<vector<int>>> adj = constructAdj(edges, V);

    // Min-heap priority queue: {distance, vertex}
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;

    // Distance array initialized to infinity
    vector<int> dist(V, INT_MAX);

    // Push source with distance 0
    pq.push({0, src});
    dist[src] = 0;

    while (!pq.empty()) {
        // Extract vertex with minimum distance
        int u = pq.top()[1];
        int curr_dist = pq.top()[0];
        pq.pop();

        // If we've found a longer path, skip
        if (curr_dist > dist[u]) continue;

        // Process all neighbors
        for (auto x : adj[u]) {
            int v = x[0];      // Neighbor vertex
            int weight = x[1]; // Edge weight

            // If we find a shorter path to v through u
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V, E, src;

    // Get number of vertices
    cout << "Enter number of vertices: ";
    cin >> V;

    // Get number of edges
    cout << "Enter number of edges: ";
    cin >> E;

    // Get source vertex
    cout << "Enter source vertex (0 to " << V-1 << "): ";
    cin >> src;

    // Input validation
    if (src < 0 || src >= V) {
        cout << "Invalid source vertex!" << endl;
        return 1;
    }

    vector<vector<int>> edges;
    cout << "Enter " << E << " edges in format (u v weight):\n";
    
    // Get edges from user
    for (int i = 0; i < E; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        
        // Validate input
        if (u < 0 || u >= V || v < 0 || v >= V || wt < 0) {
            cout << "Invalid edge input!" << endl;
            return 1;
        }
        
        edges.push_back({u, v, wt});
    }

    // Run Dijkstra's algorithm
    vector<int> result = dijkstra(V, edges, src);

    // Print results
    cout << "\nShortest distances from vertex " << src << ":\n";
    for (int i = 0; i < V; i++) {
        if (result[i] == INT_MAX)
            cout << "Vertex " << i << ": Unreachable" << endl;
        else
            cout << "Vertex " << i << ": " << result[i] << endl;
    }

    return 0;
}