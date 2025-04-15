#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <limits>

struct Edge {
    int to;
    int weight;
};

using Graph = std::vector<std::vector<Edge>>;

/**
 * @brief Computes the shortest path distances from a source node to all other nodes
 *        in a weighted directed graph using Dijkstra's algorithm.
 * 
 * @param graph A weighted directed graph represented as an adjacency list.
 *        - graph[u] contains a list of outgoing edges from node u.
 *        - Each edge is represented by a struct {to, weight}.
 * @param source The source node (0-based index) from which shortest distances are computed.
 * @param dist Output vector where dist[v] will contain the shortest distance from source to v.
 *        - If a node is unreachable from the source, its distance will be set to INT_MAX.
 * 
 * Algorithm Overview:
 * - Initializes all distances to infinity except the source node (set to 0).
 * - Uses a min-priority queue (min-heap) to repeatedly process the closest unvisited node.
 * - For each node, relaxes its neighbors: if a shorter path is found, update the distance and re-insert into the queue.
 * - Stops when all reachable nodes have been processed.
 * 
 * Time Complexity:
 * - O((V + E) log V), where V is the number of vertices and E is the number of edges.
 * - Assumes a binary heap for the priority queue.
 */
void dijkstra(const Graph& graph, int source, std::vector<int>& dist) {
    int n = graph.size();  // Number of vertices
    dist.assign(n, std::numeric_limits<int>::max());  // Initialize all distances to "infinity"
    dist[source] = 0;  // Distance to source is zero

    // Min-priority queue to select the next closest node (distance, node)
    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.emplace(0, source);  // Start from the source

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        // Skip processing if we already found a better path to u
        if (currentDist > dist[u]) continue;

        // Check all neighbors of u
        for (const Edge& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;

            // Relaxation step: if going through u offers a shorter path to v
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;  // Update shortest distance
                pq.emplace(dist[v], v);     // Push updated distance into queue
            }
        }
    }
}


int main() {
    std::ifstream infile("graph.dat");
    if (!infile) {
        std::cerr << "Error opening input file.\n";
        return 1;
    }

    int V, E;
    infile >> V >> E;

    Graph graph(V);
    for (int i = 0; i < E; ++i) {
        int u, v, w;
        infile >> u >> v >> w;
        --u; --v;  // Adjust from 1-based to 0-based indexing
        graph[u].push_back({v, w});
        // Uncomment the next line if the graph is undirected:
        // graph[v].push_back({u, w});
    }

    int source = 0; // Node 1 in the original graph
    std::vector<int> distances;
    dijkstra(graph, source, distances);

    std::cout << "Shortest distances from node " << (source + 1) << ":\n";
    for (int i = 0; i < distances.size(); ++i) {
        std::cout << "To " << (i + 1) << ": ";
        if (distances[i] == std::numeric_limits<int>::max())
            std::cout << "INF\n";
        else
            std::cout << distances[i] << "\n";
    }

    return 0;
}
