#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

// Structure to represent an edge in the priority queue
using Edge = pair<int, pair<int, int>>; // (weight, (u, v))

void prim(const vector<vector<pair<int, int>>>& graph, int& mst_weight, vector<pair<pair<int, int>, int>>& mst_edges) {
    int n = graph.size();
    vector<bool> visited(n, false);
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // Min-heap for edges
    
    // Start from vertex 0
    visited[0] = true;
    for (const auto& [v, weight] : graph[0]) {
        pq.push({weight, {0, v}});
    }
    
    while (!pq.empty()) {
        auto [weight, vertices] = pq.top();
        int u = vertices.first;
        int v = vertices.second;
        pq.pop();
        
        if (visited[v]) continue;
        
        visited[v] = true;
        mst_weight += weight;
        mst_edges.push_back({{u, v}, weight});
        
        for (const auto& [next_v, next_weight] : graph[v]) {
            if (!visited[next_v]) {
                pq.push({next_weight, {v, next_v}});
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    
    // Initialize adjacency list
    vector<vector<pair<int, int>>> graph(n);
    
    // User input for edges
    cout << "Enter edges in format 'u v w' (vertex u, vertex v, weight w). Enter -1 to stop:\n";
    while (true) {
        int u, v, w;
        cin >> u;
        if (u == -1) break;
        cin >> v >> w;
        
        if (u < 0 || u >= n || v < 0 || v >= n) {
            cout << "Invalid vertex. Try again.\n";
            continue;
        }
        
        graph[u].push_back({v, w});
        graph[v].push_back({u, w}); // For undirected graph
    }
    
    // Run Prim's algorithm
    int mst_weight = 0;
    vector<pair<pair<int, int>, int>> mst_edges;
    prim(graph, mst_weight, mst_edges);
    
    // Output: Total weight and edges in MST
    cout << "Total weight of MST: " << mst_weight << endl;
    cout << "Edges in MST (u, v, weight):\n";
    for (const auto& edge : mst_edges) {
        int u = edge.first.first;
        int v = edge.first.second;
        int w = edge.second;
        cout << u << " - " << v << ": " << w << endl;
    }
    
    return 0;
}