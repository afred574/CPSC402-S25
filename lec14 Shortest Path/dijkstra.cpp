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

void dijkstra(const Graph& graph, int source, std::vector<int>& dist) {
    int n = graph.size();
    dist.assign(n, std::numeric_limits<int>::max());
    dist[source] = 0;

    using Pair = std::pair<int, int>; // (distance, node)
    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pq;
    pq.emplace(0, source);

    while (!pq.empty()) {
        auto [currentDist, u] = pq.top();
        pq.pop();

        if (currentDist > dist[u]) continue; // Skip if already found a shorter path

        for (const Edge& e : graph[u]) {
            int v = e.to;
            int weight = e.weight;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
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
