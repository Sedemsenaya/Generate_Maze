README for Project 2 - Maze Generation using Minimum Spanning Trees (MST)
NB: RUN Command
----------------------------------------------------------------
unzip Generate_Maze-4
cd Generate_Maze-4
make
./output [rows] [columns] [pattern_type]
----------------------------------------------------------------

Overview
This project generates a maze based on a grid graph, where each cell is connected to its neighbors by weighted edges. By running a Minimum Spanning Tree (MST) algorithm on this graph, we create a connected maze with no cycles. The weight function applied to the edges influences the pattern of the maze paths.

The solution uses Kruskal's algorithm for MST construction, implemented with a priority queue for efficient edge selection. The runtime is approximately
O(ElogE), where E is the number of edges, with additional time complexity dependent on the union-find data structure used in Kruskal's algorithm. Given a grid of size
R×C (rows by columns), the number of edges scales with O(R×C).

Priority Queue
The priority queue chosen for this project is a binary heap, which supports the efficient sorting of edges by weight and ensures that the MST can be built in optimal time. This data structure allows for each edge to be processed in
O(logE) time, making it a practical choice for larger grids.

Weight Functions and Maze Patterns
To create different maze patterns, we experimented with various weight functions. Each function assigns weights to the edges based on specific criteria, influencing the maze’s appearance. Below are the weight functions implemented and how to run the program to generate each pattern:

Random Weights: This is the baseline pattern, where each edge is assigned a random weight. This results in a traditional maze structure with paths that appear organic.

Compile the project:
make
Run the maze generator:
./output [rows] [columns] [pattern_type]
Replace [rows] and [columns] with the desired maze dimensions.
I experimented with random maze generator which produces all kinds of patterns which makes applying the Kruskal algorithm significant  to do.
However, i made a function called generateGridGraph(rows, columns) which is randomized and  generateGridGraphFixed(rows, columns, fixed) which generates
mazes depending on the fixed input, but I noticed that the outputs are all the same for every input so i further  modified it into generateGridGraphFixedAdjustment(rows, columns, fixed)
to generateGrid with different patterns no matter the fixed input.

Approach 1: Modify Edge Weights Based on Row and Column
You could modify the weight assignment by adding a factor based on the row and column. This ensures that even if you pass the same fixed weight (e.g., 1), the maze generated will still change when you change the grid dimensions or the fixed weight value.

Here is an example of how you can modify the weight based on the row and column indices:

Updated generateGridGraphFixedAdjustment function:
How this works:
The positionWeight is calculated as (r + c + fixedWeight) % 100 + 1. This means that the weight of each edge will be influenced by its position (r, c) in the grid as well as the fixedWeight input.
r + c + fixedWeight: This ensures that the weight changes based on both the row, column, and the fixed weight.
% 100 + 1: This keeps the weight within the range 1-100, as your graph's edges should have weights within that range.
Why This Changes the Maze:
By adjusting the weight based on row (r), column (c), and the fixedWeight, each edge will have a unique weight, even for the same fixedWeight input.
For example, if you pass fixedWeight = 1, then a grid of size 5x8 will produce different edge weights than when you pass fixedWeight = 2.
Kruskal's algorithm will treat these differently weighted edges in a manner that will result in different MSTs and therefore different mazes.


Example run:
Original Maze (Random Weights):

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 1 0 0 0 0 0 0 0 0 0 1
1 0 1 0 1 1 1 0 1 1 1 1 1 0 1 0 1
1 0 1 0 0 0 0 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 1 1 0 1 0 1 0 1 1 1 0 1
1 0 1 0 0 0 1 0 0 0 0 0 0 0 1 0 1
1 0 1 1 1 0 1 1 1 1 1 0 1 0 1 1 1
1 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 1 1 0 1 1 1 1 1 0 1
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1                   1
1 0 1   1 1 1   1 1 1 1 1   1   1
1 0 1           1   1   1   1   1
1 0 1   1 1 1   1   1   1 1 1   1
1 0 1       1               1   1
1 0 1 1 1   1 1 1 1 1   1   1 1 1
1 0 1 0 1   1 0 0 0 1   1   1 0 1
1 0 1 0 1   1 1 1 0 1 1 1 1 1 0 1
1 0 1 0 0
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
csenaya@blue:~/Generate_Maze-4/Generate_Maze-4$ ./output 5 8
Original Maze (Random Weights):

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   1 0 0 0 0 0 0 0 1 0 1 0 0 0 1
1 0 1 0 1 0 1 1 1 1 1 0 1 1 1 0 1
1 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 1
1 1 1 0 1 1 1 1 1 0 1 0 1 0 1 1 1
1 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 1
1 0 1 0 1 1 1 1 1 1 1 0 1 1 1 1 1
1 0 1 0 0 0 1 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1               1 0 1       1
1   1   1   1 1 1 1 1 0 1 1 1   1
1       1   1 0 1 0 1 0 1   1   1
1   1 1 1 1 1 0 1 0 1 0 1   1   1
1                       1       1
1 1 1 0 1 1 1 1 1 0 1   1   1 1 1
1 0 0 0 1 0 0 0 0 0 1           1
1 0 1 0 1 1 1 1 1 1 1   1 1 1 1 1
1 0 1 0 0 0 1 0 0 0 0
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
csenaya@blue:~/Generate_Maze-4/Generate_Maze-4$ ./output 5 8
Original Maze (Random Weights):

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 1 0 0 0 1 0 0 0 0 0 0 0 1
1 0 1 1 1 1 1 0 1 1 1 1 1 0 1 0 1
1 0 0 0 1 0 0 0 0 0 1 0 1 0 1 0 1
1 1 1 0 1 0 1 1 1 0 1 0 1 0 1 1 1
1 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 1
1 0 1 0 1 1 1 1 1 1 1 0 1 0 1 0 1
1 0 1 0 0 0 0 0 0 0 1 0 1 0 1 0 1
1 0 1 1 1 0 1 1 1 1 1 0 1 1 1 0 1
1 0 0 0 1 0 0 0 1 0 0 0 0 0 1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 1 0 0 0 0 0 0 0 1
1   1 1 1 1 1 0 1 1 1 1 1 0 1 0 1
1       1           1 0 1 0 1 0 1
1 1 1   1   1 1 1   1 0 1 0 1 1 1
1 0 0           1               1
1 0 1 0 1 1 1 1 1 1 1 0 1 0 1   1
1 0 1 0 0 0 0 0 0 0 1 0 1 0 1   1
1 0 1 1 1 0 1 1 1 1 1 0 1 1 1   1
1 0 0 0 1 0 0 0 1 0 0 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
csenaya@blue:~/Generate_Maze-4/Generate_Maze-4$ ./output 5 8 6
Original Maze with Fixed Weight:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Original Maze with Fixed Weight Adjustments:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1
1 1 1   1   1   1   1   1   1   1
1       1   1   1   1   1   1   1
1   1   1 1 1 1 1 1 1 1 1 1 1 1 1
1   1                           1
1 1 1 1 1 1 1   1   1   1   1   1
1               1   1   1   1   1
1   1   1   1 1 1 1 1 1 1 1 1 1 1
1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution and Adjustment Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1
1 1 1   1   1   1   1   1   1   1
1       1   1   1   1   1   1   1
1   1   1 1 1 1 1 1 1 1 1 1 1 1 1
1   1                           1
1 1 1 1 1 1 1   1   1   1   1   1
1               1   1   1   1   1
1   1   1   1 1 1 1 1 1 1 1 1 1 1
1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
csenaya@blue:~/Generate_Maze-4/Generate_Maze-4$ ./output 5 8 3
Original Maze with Fixed Weight:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Original Maze with Fixed Weight Adjustments:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 0 0 0 0 0 0 0 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1
1 1 1   1   1   1   1   1   1   1
1       1   1   1   1   1   1   1
1   1   1 1 1 1 1 1 1 1 1 1 1 1 1
1   1                           1
1 1 1 1 1 1 1   1   1   1   1   1
1               1   1   1   1   1
1   1   1   1 1 1 1 1 1 1 1 1 1 1
1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution and Adjustment Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1
1 1 1   1   1   1   1   1   1   1
1       1   1   1   1   1   1   1
1   1   1 1 1 1 1 1 1 1 1 1 1 1 1
1   1                           1
1 1 1 1 1 1 1   1   1   1   1   1
1               1   1   1   1   1
1   1   1   1 1 1 1 1 1 1 1 1 1 1
1   1   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
csenaya@blue:~/Generate_Maze-4/Generate_Maze-4$ ./output 10 15 4
Original Maze with Fixed Weight:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 1 1 1 1 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1
1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1 0 1
1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 0 1 1 1 0 1
1 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 1
1 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1
1 1 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
Original Maze with Fixed Weight Adjustments:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1   0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 1 1 1 1 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1
1 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 0 1 1 1 0 1
1 0 0 0 0 0 1 0 0 0 0 0 0 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1
1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 0 1 0 1 1 1 0 1
1 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 1 0 0 0 1
1 0 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 0 1
1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1
1 0 1 0 1 0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 1
1 1 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 0   1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 0 1                   1
1 1 1 0 1 1 1 1 1   1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1   1
1 0 0 0 1 0 0 0 0                                           1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1   1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1   1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1   1 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1                   1       1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   1 1 1 1 1   1 1 1   1
1           1               1           1                   1
1 1 1   1 1 1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1   1   1 1 1   1
1   1                   1                       1   1       1
1   1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   1
1                                                           1
1   1   1   1   1   1   1   1   1   1   1 0 1 0 1 0 1 0 1 0 1
1   1   1   1   1   1   1   1   1   1   1 0 1 0 1 0 1 0 1 0 1
1   1   1   1   1 1 1 1 1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1 1 1
1   1   1   1   1 0 0 0 0 0 0 0 0 0 0                   1 0 1
1 1 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1 0 1
1 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Maze with Solution and Adjustment Path:

1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
1 0 0 0 0 0 0 0 0 0 1                   1
1 1 1 0 1 1 1 1 1   1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 1 1 1   1
1 0 0 0 1 0 0 0 0                                           1
1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1   1
1 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1   1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 1 1 1 1 1 1 1 1 1 1   1 1 1
1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1                   1       1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   1 1 1 1 1   1 1 1   1
1           1               1           1                   1
1 1 1   1 1 1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1   1   1 1 1   1
1   1                   1                       1   1       1
1   1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1   1
1                                                           1
1   1   1   1   1   1   1   1   1   1   1 0 1 0 1 0 1 0 1 0 1
1   1   1   1   1   1   1   1   1   1   1 0 1 0 1 0 1 0 1 0 1
1   1   1   1   1 1 1 1 1 1 1 1 1 1 1   1 1 1 1 1 1 1 1 1 1 1
1   1   1   1   1 0 0 0 0 0 0 0 0 0 0                   1 0 1
1 1 1 1 1 1 1 1 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1   1 0 1
1 0 0 0 0 0 0 0 0 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0 1
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1

Conclusion:
As you can see, larger rows and columns produce more aesthetically looking patterns. whilst say ./output 5 8 1 and 5 8 2 produce same output but different
outputs with different rows and columns like 7 7 2 or 7 7 1