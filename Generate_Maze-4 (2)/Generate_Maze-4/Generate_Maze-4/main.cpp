#include <iostream>
#include <vector>
#include "UnionFind.h"

using namespace std;

// Function prototypes (you can place them in the appropriate place in your code)
vector<vector<pair<int, int>>> generateGridGraph(int rows, int cols);
vector<vector<pair<int, int>>> generateGridGraphFixed(int rows, int cols, int fixedWeight) ;
void printMaze(const vector<vector<char>>& maze);
vector<Edge> kruskal(int rows, int cols, const vector<vector<pair<int, int>>>& graph);
vector<vector<char>> createMaze(int rows, int cols, const vector<Edge>& mstEdges);
vector<pair<int, int>> solveMaze(const vector<vector<char>>& maze, pair<int, int> start, pair<int, int> end);
void markSolutionPath(vector<vector<char>>& maze, const vector<pair<int, int>>& path);
vector<vector<pair<int, int>>> generateGridGraphFixedAdjustment(int rows, int cols, int fixedWeight);


int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        cerr << "Usage: " << argv[0] << " <numRows> <numColumns> [<fixedWeight>]" << endl;
        return 1;
    }

    int numRows = stoi(argv[1]);
    int numColumns = stoi(argv[2]);

    // Check if a third argument is provided for fixed weight
    if (argc == 4) {
        int fixedWeight = stoi(argv[3]);
        // Generate the graph with fixed weight for all edges
        auto graph = generateGridGraphFixed(numRows, numColumns, fixedWeight);
        auto mstEdges = kruskal(numRows, numColumns, graph);
        auto maze = createMaze(numRows, numColumns, mstEdges);

        // Generate the graph with fixed weight for all edges
        auto graphAdj = generateGridGraphFixedAdjustment(numRows, numColumns, fixedWeight);
        auto mstEdgesAdj = kruskal(numRows, numColumns, graph);
        auto mazeAdj = createMaze(numRows, numColumns, mstEdges);

        cout << "Original Maze with Fixed Weight:\n" << endl;
        printMaze(maze);
        cout << "Original Maze with Fixed Weight Adjustments:\n" << endl;
        printMaze(mazeAdj);

        // Solve the maze
        pair<int, int> start = {1, 1};  // Entrance
        pair<int, int> end = {2 * numRows - 1, 2 * numColumns - 1};  // Exit
        auto solutionPath = solveMaze(maze, start, end);

        // Solve the maze
        pair<int, int> startAdj = {1, 1};  // Entrance
        pair<int, int> endAdj = {2 * numRows - 1, 2 * numColumns - 1};  // Exit
        auto solutionPathAdj = solveMaze(mazeAdj, start, end);

        if (!solutionPath.empty()) {
            markSolutionPath(maze, solutionPath);
        }
        if (!solutionPathAdj.empty()) {
            markSolutionPath(mazeAdj, solutionPathAdj);
        }

        // Remove walls around the entrance and exit
        maze[start.first][start.second - 1] = ' ';  // Left of start
        maze[end.first][end.second + 1] = ' ';  // Right of end

        // Remove walls around the entrance and exit
        mazeAdj[start.first][start.second - 1] = ' ';  // Left of start
        mazeAdj[end.first][end.second + 1] = ' ';  // Right of end

        cout << "\nMaze with Solution Path:\n" << endl;
        printMaze(maze);
        cout << "\nMaze with Solution and Adjustment Path:\n" << endl;
        printMaze(mazeAdj);
    } else {
        if (argc != 3) {
            cerr << "Usage: " << argv[0] << " <numRows> <numColumns>" << endl;
            return 1;
        }

        auto graph = generateGridGraph(numRows, numColumns);
        auto mstEdges = kruskal(numRows, numColumns, graph);
        auto maze = createMaze(numRows, numColumns, mstEdges);

        cout << "Original Maze (Random Weights):\n" << endl;
        printMaze(maze);

        // Solve the maze
        pair<int, int> start = {1, 1}; // Entrance
        pair<int, int> end = {2 * numRows - 1, 2 * numColumns - 1}; // Exit
        auto solutionPath = solveMaze(maze, start, end);

        if (!solutionPath.empty()) {
            markSolutionPath(maze, solutionPath);
        }

        // Remove walls around the entrance and exit
        maze[start.first][start.second - 1] = ' '; // Left of start
        maze[end.first][end.second + 1] = ' '; // Right of end

        cout << "\nMaze with Solution Path:\n" << endl;
        printMaze(maze);
    }

    return 0;
}