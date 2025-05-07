// C++ program for solution of M Coloring problem using backtracking
#include <iostream>
#include <vector>
using namespace std;

// Function to print the solution
void printSolution(const vector<int>& color, int V) {
    cout << "Solution Exists: Following are the assigned colors\n";
    for (int i = 0; i < V; i++)
        cout << " " << color[i] << " ";
    cout << "\n";
}

// Function to check if the current color assignment is safe for vertex v
bool isSafe(int v, const vector<vector<bool>>& graph, const vector<int>& color, int c, int V) {
    for (int i = 0; i < V; i++)
        if (graph[v][i] && c == color[i])
            return false;
    return true;
}

// Recursive utility function to solve m coloring problem
bool graphColoringUtil(const vector<vector<bool>>& graph, int m, vector<int>& color, int v, int V) {
    // Base case: If all vertices are assigned a color
    if (v == V)
        return true;
    
    // Try different colors for vertex v
    for (int c = 1; c <= m; c++) {
        // Check if assignment of color c to v is safe
        if (isSafe(v, graph, color, c, V)) {
            color[v] = c;
            
            // Recur to assign colors to rest of the vertices
            if (graphColoringUtil(graph, m, color, v + 1, V))
                return true;
                
            // If assigning color c doesn't lead to a solution, remove it (backtrack)
            color[v] = 0;
        }
    }
    
    // If no color can be assigned to this vertex
    return false;
}

// Main function that solves the m Coloring problem
bool graphColoring(const vector<vector<bool>>& graph, int m, int V) {
    // Initialize all color values as 0
    vector<int> color(V, 0);
    
    // Call graphColoringUtil() for vertex 0
    if (!graphColoringUtil(graph, m, color, 0, V)) {
        cout << "Solution does not exist" << endl;
        return false;
    }
    
    // Print the solution
    printSolution(color, V);
    return true;
}

int main() {
    int V, E, m;
    
    cout << "Enter the number of vertices: ";
    cin >> V;
    
    // Initialize adjacency matrix
    vector<vector<bool>> graph(V, vector<bool>(V, false));
    
    cout << "Enter the number of edges: ";
    cin >> E;
    
    cout << "Enter the edges (format: u v, where u and v are vertices): " << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        
        // Check if vertices are valid
        if (u < 0 || u >= V || v < 0 || v >= V) {
            cout << "Invalid vertices! Vertices should be between 0 and " << V-1 << endl;
            i--;
            continue;
        }
        
        // Add edge to graph
        graph[u][v] = true;
        graph[v][u] = true; // Undirected graph
    }
    
    cout << "Enter the number of colors: ";
    cin >> m;
    
    // Solve the graph coloring problem
    graphColoring(graph, m, V);
    
    return 0;
}
