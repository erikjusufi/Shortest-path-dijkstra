#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned int uint;

// Node structure representing a cell in the grid
struct Node {
    uint value;
    std::pair<uint, uint> coordinates;
};

// Custom comparator class for priority queue ordering
class Comparator {
public:
    bool operator()(const Node &lhs, const Node &rhs) const {
        return (lhs.value > rhs.value);
    }
};

// Function to check if a position (x, y) is within the bounds of the grid
bool isSafe(int x, int y, int N, int M) {
    return x >= 0 && x < N && y >= 0 && y < M;
}

// Function to solve the minimum cost path problem
uint solve(const uint N, const uint M, uint16_t *const problem, std::vector<std::pair<uint, uint>> &solution) {
    // Array to store accumulated costs for each cell
    uint *accumulated_cost = new uint[N * M];

    // Initialize accumulated cost array with maximum value
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            accumulated_cost[j + i * M] = UINT32_MAX;
        }
    }

    // Priority queue for Dijkstra's algorithm
    priority_queue<Node, vector<Node>, Comparator> pq;

    // Coordinates of the destination (bottom-right corner)
    std::pair<uint, uint> destination;
    destination.first = N - 1;
    destination.second = M - 1;

    // Initialize accumulated cost and push the starting node into the priority queue
    *accumulated_cost = *(problem);
    pq.push({*(problem), {0, 0}});

    // Dijkstra's algorithm
    while (!pq.empty()) {
        Node node = pq.top();
        pq.pop();
        int x = node.coordinates.first;
        int y = node.coordinates.second;

        // Check right neighbor
        if (isSafe(x, y + 1, N, M) && accumulated_cost[x * M + y + 1] == UINT32_MAX) {
            accumulated_cost[x * M + y + 1] = accumulated_cost[x * M + y] + *(problem + (y + 1) % M + x * (M));
            pq.push({accumulated_cost[x * M + y + 1], {x, y + 1}});
        }

        // Check bottom neighbor
        if (isSafe(x + 1, y, N, M) && accumulated_cost[(x + 1) * M + y] == UINT32_MAX) {
            accumulated_cost[(x + 1) * M + y] = accumulated_cost[x * M + y] + *(problem + y % M + (x + 1) * (M));
            pq.push({accumulated_cost[(x + 1) * M + y], {x + 1, y}});
        }
    }

    // Backtrack to reconstruct the optimal path
    solution.push_back(destination);
    while (true) {
        if (isSafe(destination.first, destination.second - 1, N, M) &&
            isSafe(destination.first - 1, destination.second, N, M)) {
            if (accumulated_cost[(destination.first - 1) * M + destination.second] >=
                accumulated_cost[destination.first * M + destination.second - 1]) {
                destination.first = destination.first;
                destination.second = destination.second - 1;
                solution.push_back(destination);
            } else {
                destination.first = destination.first - 1;
                destination.second = destination.second;
                solution.push_back(destination);
            }
        } else if (isSafe(destination.first - 1, destination.second, N, M)) {
            destination.first = destination.first - 1;
            destination.second = destination.second;
            solution.push_back(destination);
        } else if (isSafe(destination.first, destination.second - 1, N, M)) {
            destination.first = destination.first;
            destination.second = destination.second - 1;
            solution.push_back(destination);
        } else {
            break;
        }
    }

    // Reverse the path to obtain the correct order
    reverse(solution.begin(), solution.end());

    // Calculate and return the minimum cost
    uint cost = accumulated_cost[N * M - 1];
    delete[] accumulated_cost;
    return cost;
}

int main() {
    // Example grid represented by the array
    uint16_t grid[] = {100, 200, 1000, 0,
                       200, 100, 600, 0,
                       300, 1600, 100, 0};

    uint16_t *ptr = grid;
    std::vector<std::pair<unsigned int, unsigned int>> path;

    // Solve the problem and obtain the result
    uint16_t minCost = solve(3, 4, ptr, path);

    // Output the minimum cost
    cout << "Minimum cost: " << minCost << "\n";

    // Output the optimal path coordinates
    for (int i = 0; i < path.size(); ++i) {
        cout << "(" << path[i].first << ", " << path[i].second << ")" << endl;
    }

    return 0;
}
