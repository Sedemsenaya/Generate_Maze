//
// Created by Colli on 11/10/2024.
//

#include "UnionFind.h"

// Function to generate a grid graph
vector<vector<pair<int, int>>> generateGridGraph(int rows, int cols) {
    vector<vector<pair<int, int>>> graph(rows * cols);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int node = r * cols + c;
            if (r > 0) {
                int weight = dis(gen);
                graph[node].emplace_back(node - cols, weight); // Up
            }
            if (r < rows - 1) {
                int weight = dis(gen);
                graph[node].emplace_back(node + cols, weight); // Down
            }
            if (c > 0) {
                int weight = dis(gen);
                graph[node].emplace_back(node - 1, weight); // Left
            }
            if (c < cols - 1) {
                int weight = dis(gen);
                graph[node].emplace_back(node + 1, weight); // Right
            }
        }
    }
    return graph;
}


// Function to generate a grid graph with fixed weights for all edges
vector<vector<pair<int, int>>> generateGridGraphFixed(int rows, int cols, int fixedWeight) {
    vector<vector<pair<int, int>>> graph(rows * cols);

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int node = r * cols + c;
            if (r > 0) {
                graph[node].emplace_back(node - cols, fixedWeight); // Up
            }
            if (r < rows - 1) {
                graph[node].emplace_back(node + cols, fixedWeight); // Down
            }
            if (c > 0) {
                graph[node].emplace_back(node - 1, fixedWeight); // Left
            }
            if (c < cols - 1) {
                graph[node].emplace_back(node + 1, fixedWeight); // Right
            }
        }
    }
    return graph;
}


// Function to generate the grid graph with a fixed weight influenced by position (rows, cols, fixedWeight)
vector<vector<pair<int, int>>> generateGridGraphFixedAdjustment(int rows, int cols, int fixedWeight) {
    vector<vector<pair<int, int>>> graph(rows * cols);

    // Generate edges with weights influenced by the fixedWeight and position
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            int node = r * cols + c;

            // Here, the weight is influenced by both the fixedWeight and the position (row, col)
            int positionWeight = (r + c + fixedWeight) % 100 + 1;  // Modulo to keep the weight within 1-100 range

            if (r > 0) {
                // Up
                graph[node].emplace_back(node - cols, positionWeight);
            }
            if (r < rows - 1) {
                // Down
                graph[node].emplace_back(node + cols, positionWeight);
            }
            if (c > 0) {
                // Left
                graph[node].emplace_back(node - 1, positionWeight);
            }
            if (c < cols - 1) {
                // Right
                graph[node].emplace_back(node + 1, positionWeight);
            }
        }
    }
    return graph;
}




// Function to build the minimum spanning tree using Kruskal's algorithm
vector<Edge> kruskal(int rows, int cols, const vector<vector<pair<int, int>>> &graph) {
    vector<Edge> edges;

    // Collect edges from the graph
    for (int u = 0; u < graph.size(); ++u) {
        for (const auto &[v, weight] : graph[u]) {
            if (u < v) { // To avoid duplicate edges
                edges.push_back({u, v, weight});
            }
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());

    UnionFind uf(rows * cols);
    vector<Edge> mstEdges;

    // Iterate through edges to form the MST
    for (const auto &edge : edges) {
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unionSets(edge.u, edge.v);
            mstEdges.push_back(edge);
        }
    }

    return mstEdges;
}

// Function to create the maze from the MST edges
vector<vector<char>> createMaze(int rows, int cols, const vector<Edge> &mstEdges) {
    vector<vector<char>> maze(2 * rows + 1, vector<char>(2 * cols + 1, '1'));

    // Create walls and paths based on MST edges
    for (const auto &edge : mstEdges) {
        int r1 = edge.u / cols, c1 = edge.u % cols;
        int r2 = edge.v / cols, c2 = edge.v % cols;
        maze[2 * r1 + 1][2 * c1 + 1] = '0'; // Path cell
        maze[2 * r2 + 1][2 * c2 + 1] = '0'; // Path cell
        if (r1 == r2) { // Horizontal edge
            maze[2 * r1 + 1][2 * min(c1, c2) + 2] = '0'; // Create path
        } else if (c1 == c2) { // Vertical edge
            maze[2 * min(r1, r2) + 2][2 * c1 + 1] = '0'; // Create path
        }
    }

    // Mark entrance and exit with empty cells
    maze[1][1] = ' '; // Entrance (start)
    maze[2 * rows - 1][2 * cols - 1] = ' '; // Exit (end)

    return maze;
}

// Function to print the maze
void printMaze(const vector<vector<char>> &maze) {
    for (const auto &row : maze) {
        for (char cell : row) {
            cout << cell << ' ';
        }
        cout << endl;
    }
}

// Function to solve the maze
vector<pair<int, int>> solveMaze(const vector<vector<char>> &maze, pair<int, int> start, pair<int, int> end) {
    int rows = maze.size(), cols = maze[0].size();
    vector<pair<int, int>> path;
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    vector<pair<int, int>> stack = {start};

    while (!stack.empty()) {
        pair<int, int> current = stack.back();
        stack.pop_back();
        if (visited[current.first][current.second]) continue;
        visited[current.first][current.second] = true;
        path.push_back(current);

        if (current == end) return path; // Return the path when the end is reached

        // Explore neighbors
        for (const auto &dir : vector<pair<int, int>>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) { // Up, Down, Left, Right
            int nr = current.first + dir.first;
            int nc = current.second + dir.second;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                (maze[nr][nc] == '0' || maze[nr][nc] == ' ') &&
                !visited[nr][nc]) {
                stack.emplace_back(nr, nc);
            }
        }
    }
    return {}; // No path found
}

// Function to mark the solution path
void markSolutionPath(vector<vector<char>> &maze, const vector<pair<int, int>> &path) {
    for (const auto &[r, c] : path) {
        if (maze[r][c] == '0') { // Mark the solution path with empty spaces only if it's a path
            maze[r][c] = ' ';
        }
    }
}
