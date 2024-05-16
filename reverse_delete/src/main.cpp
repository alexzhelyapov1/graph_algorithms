#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <set>

using namespace std;
static std::ofstream out;


struct Edge {
    int u;
    int v;
    int weight;

    bool operator<(const Edge& other) const {
        return weight > other.weight;
    }
};


class Graph {
  public:

    int V;
    vector<Edge> edges;

    std::vector<Graph> GetConnectivityComponents();
    void ReverseDelete();
    bool IsConnected();
    void GraphVizPrint(std::ofstream& out, const std::string& color="default");
};


class DSU {
  public:
    int V_;
    std::vector<int> parent;

    DSU(int V): V_(V) {
        for (int i = 0; i < V; i++) {
            parent.push_back(-1);
        }
    }

    int Find(int i) {
        if (parent[i] == -1) {
            return i;
        }
        return Find(parent[i]);
    }

    void Unite(int x, int y) {
        int xset = Find(x);
        int yset = Find(y);
        parent[xset] = yset;
    }

    int AreasNumber() {
        vector<int> parents;

        for (int i = 0; i < V_; i++) {
            parents.push_back(Find(i));
        }
        set<int> unique_areas(parents.begin(), parents.end());

        return unique_areas.size();

        // int root = Find(0);

        // for (int i = 1; i < V_; i++) {
        //     if (Find(i) != root) {
        //         return false;
        //     }
        // }

        // return true;
    }
};


// Функция для проверки, связан ли граф
bool Graph::IsConnected() {
    DSU areas(V);

    // Объединяем вершины, соединенные ребрами
    for (Edge& edge : edges) {
        int x = areas.Find(edge.u);
        int y = areas.Find(edge.v);
        if (x != y) {
            areas.Unite(x, y);
        }
    }

    // Проверяем, принадлежат ли все вершины одному подмножеству
    if (areas.AreasNumber() == 1) {
        return true;
    }
    return false;
}


void Graph::ReverseDelete() {
    // Сортируем ребра по убыванию веса
    sort(edges.begin(), edges.end());

    int i = 0;
    while (i < edges.size()) {
        // Удаляем ребро
        Edge edge = edges[i];
        edges.erase(edges.begin() + i);

        // Проверяем, связан ли граф
        if (!IsConnected()) {
            // Если граф не связан, возвращаем ребро на место
            edges.insert(edges.begin() + i, edge);
            i++;
        }
    }
}

void Graph::GraphVizPrint(std::ofstream& out, const std::string& color) {
    static std::vector<std::string> colors = {"black", "red", "blue", "yellow", "green", "aqua", "cadetblue1", "chartreuse", "coral", "crimson", "cyan", "fuchsia", "pink"};
    std::string color_ = color;
    static int i = 0;
    static int launch_number;

    if (color == "default") {
        color_ = colors[i++];
    }

    for (auto& edge : edges) {
        out << edge.u << " -- " << edge.v << " [color = " << color_;

        if (launch_number == 0) {
            out << ", label = \"" << edge.weight << "\"";
        }

        out << "]" << std::endl;
    }

    launch_number++;
}


// std::vector<Graph> Graph::GetConnectivityComponents() {

// }


int main() {
    out.open("/home/alex/graph_algorithms/reverse_delete/gen/GV.txt");
    if (!out.is_open()) {
        throw std::runtime_error("ERROR! Can't open file\n");
    }
    out << "graph graphname {\n";

    // Пример графа
    Graph graph;
    graph.V = 4;
    graph.edges = {
        {0, 1, 4},
        {0, 2, 3},
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 7}
    };

    graph.GraphVizPrint(out);

    // Вызываем алгоритм обратного удаления
    // vector<Edge> mst = reverseDelete(graph);
    graph.ReverseDelete();

    graph.GraphVizPrint(out);

    // Выводим минимальное остовное дерево
    cout << "Минимальное остовное дерево:" << endl;
    for (Edge& edge : graph.edges) {
        cout << edge.u << " - " << edge.v << " : " << edge.weight << endl;
    }

    out << "}";
    out.close();

    return 0;
}