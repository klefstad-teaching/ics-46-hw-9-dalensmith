#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

constexpr int INF = std::numeric_limits<int>::max();

struct Edge {
    int src = 0;
    int dst = 0;
    int weight = 0;
    Edge(int s = 0, int d = 0, int w = 0) : src(s), dst(d), weight(w) {}
    friend std::istream& operator>>(std::istream& in, Edge& e) {
        return in >> e.src >> e.dst >> e.weight;
    }

    friend std::ostream& operator<<(std::ostream& out, const Edge& e) {
        return out << "(" << e.src << "," << e.dst << "," << e.weight << ")";
    }
};

struct Graph : public std::vector<std::vector<Edge>> {
    int numVertices = 0;
};

inline std::istream& operator>>(std::istream& in, Graph& G) {
    if (!(in >> G.numVertices))
        throw std::runtime_error("Unable to find input file");
    G.resize(G.numVertices);
    for (Edge e; in >> e;)
        G[e.src].push_back(e);
    return in;
}

inline void file_to_graph(const std::string& filename, Graph& G) {
    std::ifstream in(filename);
    if(!in)
        throw std::runtime_error("Can't open input file");
    in >> G;
    in.close();
}

std::vector<int> dijkstra_shortest_path(const Graph& G, int source, std::vector<int>& previous);
std::vector<int> extract_shortest_path(const std::vector<int>& distances, const std::vector<int>& previous, int destination);
void print_path(const std::vector<int>& v, int total);