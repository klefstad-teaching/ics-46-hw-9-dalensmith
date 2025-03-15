#include "dijkstras.h"

std::vector<int> dijkstra_shortest_path(const Graph& G, int source, std::vector<int>& previous) {
    int vertices = G.numVertices;
    std::vector<int> distances(vertices, INF);
    std::vector<bool> visited(vertices, false);
    distances[source] = 0;
    previous[source] = -1;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> heap;
    heap.push({0, source});
    while(!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        if(visited[u])
            continue;
        visited[u] = true;
        for(const Edge& e : G[u]) {
            int v = e.dst;
            int w = e.weight;
            if(distances[u] + w < distances[v]) {
                distances[v] = distances[u] + w;
                previous[v] = u;
                heap.push({distances[v], v});
            }
        }
    }
    return distances;
}

std::vector<int> extract_shortest_path(const std::vector<int>& distances, const std::vector<int>& previous, int destination) {
    std::vector<int> path;
    if(distances[destination] == INF)
        return path;
    std::stack<int> stk;
    for(int v = destination; v != -1; v = previous[v])
        stk.push(v);
    while(!stk.empty()) {
        path.push_back(stk.top());
        stk.pop();
    }
    return path;
}

void print_path(const std::vector<int>& v, int total) {
    for(const int& vertex : v)
        std::cout << vertex << ' ';
    std::cout << std::endl << "Total cost is " << total << std::endl;
}