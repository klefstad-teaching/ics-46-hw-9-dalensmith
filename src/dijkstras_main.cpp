#include "dijkstras.h"

int main() {
    Graph g;
    file_to_graph("src/largest.txt", g);
    std::vector<int> previous(g.numVertices, -1);
    std::vector<int> distances;
    std::vector<int> path;
    distances = dijkstra_shortest_path(g, 0, previous);
    path = extract_shortest_path(distances, previous, 99);
    print_path(path, distances[99]);
    return 0;
}