#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Disjoint Set Union (DSU) data structure
class DSU {
    vector<int> parent, rank;

public:
    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find with path compression
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }

    // Union by rank
    void unite(int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else {
                parent[s2] = s1;
                rank[s1]++;
            }
        }
    }
};

// Comparator for sorting edges by weight
bool comparator(vector<int> &a, vector<int> &b) {
    return a[2] < b[2];
}

// Kruskal's algorithm to find Minimum Spanning Tree
pair<int, vector<vector<int>>> kruskalsMST(int V, vector<vector<int>> &edges) {
    // Sort edges by weight
    sort(edges.begin(), edges.end(), comparator);

    DSU dsu(V);
    int cost = 0, count = 0;
    vector<vector<int>> mst_edges; // Store MST edges

    // Process edges in sorted order
    for (auto &e : edges) {
        int x = e[0], y = e[1], w = e[2];

        // If including this edge doesn't form a cycle
        if (dsu.find(x) != dsu.find(y)) {
            dsu.unite(x, y);
            cost += w;
            mst_edges.push_back({x, y, w});
            if (++count == V - 1) break;
        }
    }

    // Check if MST exists
    if (count != V - 1) return make_pair(-1, vector<vector<int>>());
    return make_pair(cost, mst_edges);
}

int main() {
    int V, E;

    cout << "Enter number of vertices: ";
    cin >> V;

    cout << "Enter number of edges: ";
    cin >> E;

    if (V <= 0 || E < 0) {
        cout << "Invalid input!" << endl;
        return 1;
    }

    vector<vector<int>> edges;
    cout << "Enter " << E << " edges in format (u v weight):\n";

    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        if (u < 0 || u >= V || v < 0 || v >= V || w < 0) {
            cout << "Invalid edge input!" << endl;
            return 1;
        }

        edges.push_back({u, v, w});
    }

    // Run Kruskal's algorithm
    pair<int, vector<vector<int>>> result = kruskalsMST(V, edges);
    int cost = result.first;
    vector<vector<int>> mst_edges = result.second;

    if (cost == -1) {
        cout << "No valid Minimum Spanning Tree exists!" << endl;
    } else {
        cout << "Minimum Spanning Tree cost: " << cost << endl;
        cout << "Edges in MST (u v weight):\n";
        for (const auto &e : mst_edges) {
            cout << e[0] << " " << e[1] << " " << e[2] << endl;
        }
    }

    return 0;
}
