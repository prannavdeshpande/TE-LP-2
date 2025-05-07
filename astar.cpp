#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <string>
#include <cmath>

// Directions for moving the empty space
std::vector<int> dx = {-1, 1, 0, 0};
std::vector<int> dy = {0, 0, -1, 1};
std::vector<std::string> direction = {"Up", "Down", "Left", "Right"};

// A structure to represent the puzzle state
struct Puzzle {
    std::vector<std::vector<int>> state; // Current puzzle configuration
    int emptyX, emptyY;                 // Position of the empty space
    int g, h;                           // Cost to reach this state and heuristic (Manhattan distance)

    // Function to calculate total cost (f = g + h)
    int f() {
        return g + h;
    }

    // Check if the current state is the goal state
    bool isGoal(const std::vector<std::vector<int>>& goal) {
        for (int i = 0; i < state.size(); i++)
            for (int j = 0; j < state[i].size(); j++)
                if (state[i][j] != goal[i][j]) return false;
        return true;
    }

    // Convert the current state to a string for easy hashing/comparison
    std::string stateToString() {
        std::string s;
        for (int i = 0; i < state.size(); i++) {
            for (int j = 0; j < state[i].size(); j++) {
                s += std::to_string(state[i][j]) + " ";
            }
        }
        return s;
    }
};

// Comparator for priority_queue (min-heap based on f value)
struct ComparePuzzle {
    bool operator()(Puzzle& a, Puzzle& b) {
        return a.f() > b.f(); // Smaller f has higher priority
    }
};

// Print the puzzle state
void printPuzzle(const std::vector<std::vector<int>>& puzzle) {
    for (int i = 0; i < puzzle.size(); i++) {
        for (int j = 0; j < puzzle[i].size(); j++) {
            std::cout << puzzle[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Calculate the Manhattan distance (heuristic)
int calculateHeuristic(const std::vector<std::vector<int>>& puzzle, const std::vector<std::vector<int>>& goal) {
    int h = 0;
    int N = puzzle.size();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = puzzle[i][j];
            if (val != 0) {
                for (int x = 0; x < N; x++) {
                    for (int y = 0; y < N; y++) {
                        if (goal[x][y] == val) {
                            h += std::abs(i - x) + std::abs(j - y);
                        }
                    }
                }
            }
        }
    }
    return h;
}

// Find position of 0 (empty tile)
std::pair<int, int> findEmptySpace(const std::vector<std::vector<int>>& puzzle) {
    for (int i = 0; i < puzzle.size(); i++)
        for (int j = 0; j < puzzle[i].size(); j++)
            if (puzzle[i][j] == 0) return {i, j};
    return {-1, -1}; // Should not happen
}

// Validate puzzle state (contains numbers 0 to N²-1 exactly once)
bool isValidState(const std::vector<std::vector<int>>& state, int N) {
    std::unordered_set<int> seen;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int val = state[i][j];
            if (val < 0 || val >= N * N || seen.count(val)) {
                return false;
            }
            seen.insert(val);
        }
    }
    return true;
}

// Solve using A* search
bool solvePuzzle(std::vector<std::vector<int>>& initialState, const std::vector<std::vector<int>>& goal) {
    std::priority_queue<Puzzle, std::vector<Puzzle>, ComparePuzzle> pq;
    std::unordered_set<std::string> visited;

    std::pair<int, int> emptyPos = findEmptySpace(initialState);
    Puzzle start = {initialState, emptyPos.first, emptyPos.second, 0, calculateHeuristic(initialState, goal)};
    pq.push(start);
    visited.insert(start.stateToString());

    while (!pq.empty()) {
        Puzzle current = pq.top();
        pq.pop();

        std::cout << "Current state (f = " << current.f() << "):" << std::endl;
        printPuzzle(current.state);

        if (current.isGoal(goal)) {
            std::cout << "Solution found!" << std::endl;
            printPuzzle(current.state);
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int newX = current.emptyX + dx[i];
            int newY = current.emptyY + dy[i];

            if (newX >= 0 && newX < initialState.size() && newY >= 0 && newY < initialState.size()) {
                std::vector<std::vector<int>> newState = current.state;
                std::swap(newState[current.emptyX][current.emptyY], newState[newX][newY]);

                Puzzle nextState = {newState, newX, newY, current.g + 1, calculateHeuristic(newState, goal)};
                std::string stateStr = nextState.stateToString();

                if (visited.find(stateStr) == visited.end()) {
                    pq.push(nextState);
                    visited.insert(stateStr);
                    std::cout << "Move " << direction[i] << " (f = " << nextState.f() << "):" << std::endl;
                    printPuzzle(newState);
                }
            }
        }
    }

    return false; // No solution found
}

int main() {
    int N;
    std::cout << "Enter the puzzle size (N for NxN grid, e.g., 3 for 3x3): ";
    std::cin >> N;

    // Input validation for puzzle size
    if (N <= 1) {
        std::cout << "Invalid puzzle size! Must be greater than 1." << std::endl;
        return 1;
    }

    // Initialize goal state
    std::vector<std::vector<int>> goal(N, std::vector<int>(N));
    std::cout << "Enter the goal state (" << N << "x" << N << " grid, numbers 0 to " << (N * N - 1) << "):" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> goal[i][j];
        }
    }
    if (!isValidState(goal, N)) {
        std::cout << "Invalid goal state! Must contain unique numbers from 0 to " << (N * N - 1) << "." << std::endl;
        return 1;
    }

    // Initialize initial state
    std::vector<std::vector<int>> initial(N, std::vector<int>(N));
    std::cout << "Enter the initial state (" << N << "x" << N << " grid, numbers 0 to " << (N * N - 1) << "):" << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cin >> initial[i][j];
        }
    }
    if (!isValidState(initial, N)) {
        std::cout << "Invalid initial state! Must contain unique numbers from 0 to " << (N * N - 1) << "." << std::endl;
        return 1;
    }

    if (!solvePuzzle(initial, goal)) {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}

// Time Complexity: O(b^d) where b is the branching factor and d is the depth of the solution.
// Space Complexity: O(b^d) for the priority queue and visited set.