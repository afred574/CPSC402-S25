#include <iostream>
#include <list>
#include <vector>
#include <limits.h>
#include <fstream>

using namespace std;

#define INF INT_MAX


struct Vertex {
    list<pair<int, int>> adj;
    bool known;
    int dist;
    Vertex* path;
};

class Graph {
public:
    Graph(int numVertices) : numVertices(numVertices), vertices(numVertices) {}

    void addEdge(int u, int v, int w) {
        vertices[u].adj.push_back(make_pair(v, w));
    }

void dijkstra(int source) {
    // Initialize all vertices as unknown and with infinite distance from source
    for (int i = 0; i < numVertices; i++) {
        vertices[i].known = false;
        vertices[i].dist = INF;
        vertices[i].path = nullptr;
    }

    // The distance from the source vertex to itself is 0
    vertices[source].dist = 0;


    
    for (int i = 0; i < numVertices; i++) {
        // Find the closest unknown vertex
        int minDist = INF;
	Vertex* closestVertex = nullptr;
	
        for (int j = 0; j < numVertices; j++) {
            if (!vertices[j].known && vertices[j].dist < minDist) {
                minDist = vertices[j].dist;
                closestVertex = &vertices[j];
            }
        }

        // If all vertices are known, break out of the loop
        if (closestVertex == nullptr) {
            break;
        }

        // Mark the closest vertex as known
        closestVertex->known = true;

        // Update the distance to each adjacent vertex
        for (auto& neighbor : closestVertex->adj) {
            int v = neighbor.first;
            int w = neighbor.second;
            if (!vertices[v].known && closestVertex->dist + w < vertices[v].dist) {
                vertices[v].dist = closestVertex->dist + w;
                vertices[v].path = closestVertex;
            }
        }
    }
}

  
    void printShortestPaths(int source) {
        for (int i = 0; i < numVertices; i++) {
            cout << "Shortest path from vertex " << source << " to vertex " << i << ": ";
            if (vertices[i].dist == INF) {
                cout << "no path exists" << endl;
            } else {
                cout << vertices[i].dist << endl;
            }
        }
    }

private:
    int numVertices;
    vector<Vertex> vertices;
};



int main() {
    ifstream input("graph.dat");
    if (!input) {
        cerr << "Failed to open file" << endl;
        return 1;
    }

    int numVertices, numEdges;
    input >> numVertices >> numEdges;

    Graph g(numVertices);

    int u, v, w;
    for (int i = 0; i < numEdges; i++) {
        input >> u >> v >> w;
        g.addEdge(u, v, w);
    }

    g.dijkstra(1);
    g.printShortestPaths(1);

    return 0;
}

