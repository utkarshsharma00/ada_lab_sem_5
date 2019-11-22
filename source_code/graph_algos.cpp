#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

class Edge
{
public:
    int neighbour;
    int weight;

    Edge(int neighbour, int weight)
    {
        this->neighbour = neighbour;
        this->weight = weight;
    }
};

class Djikstra_Helper
{
public:
    int vertex;
    string path_so_far;
    int distance_so_far;

    Djikstra_Helper(int vertex, string path_so_far, int distance_so_far)
    {
        this->vertex = vertex;
        this->path_so_far = path_so_far;
        this->distance_so_far = distance_so_far;
    }

    bool operator<(const Djikstra_Helper &other) const
    {
        return this->distance_so_far < other.distance_so_far;
    }

    bool operator>(const Djikstra_Helper &other) const
    {
        return this->distance_so_far > other.distance_so_far;
    }

    void display()
    {
        cout << vertex << " " << path_so_far << " " << distance_so_far;
    }
};

class Prims_Helper
{
public:
    int vertex;
    int acquiring_vertex;
    int cost_of_acquiring;

    Prims_Helper(int vertex, int acquiring_vertex, int cost_of_acquiring)
    {
        this->vertex = vertex;
        this->acquiring_vertex = acquiring_vertex;
        this->cost_of_acquiring = cost_of_acquiring;
    }

    bool operator<(const Prims_Helper &other) const
    {
        return this->cost_of_acquiring < other.cost_of_acquiring;
    }

    bool operator>(const Prims_Helper &other) const
    {
        return this->cost_of_acquiring > other.cost_of_acquiring;
    }
};

class Kruskal_Helper
{
public:
    int vertex_1;
    int vertex_2;
    int weight;

    Kruskal_Helper(int vertex_1, int vertex_2, int weight)
    {
        this->vertex_1 = vertex_1;
        this->vertex_2 = vertex_2;
        this->weight = weight;
    }

    bool operator>(const Kruskal_Helper &other) const
    {
        return this->weight > other.weight;
    }
};

class Bellman_Helper
{
public:
    int vertex_1;
    int vertex_2;
    int weight;

    Bellman_Helper(int vertex_1, int vertex_2, int weight)
    {
        this->vertex_1 = vertex_1;
        this->vertex_2 = vertex_2;
        this->weight = weight;
    }

    bool operator>(const Bellman_Helper &other) const
    {
        return this->weight > other.weight;
    }
};


void addEdge(vector<vector<Edge>> &graph, int vertex1, int vertex2, int weight)
{
    graph[vertex1].push_back(Edge(vertex2, weight));
    graph[vertex2].push_back(Edge(vertex1, weight));
}

void display(vector<vector<Edge>> &graph)
{
    for (int vertex = 0; vertex < graph.size(); vertex++)
    {
        cout << vertex << "->";
        for (int neighbour = 0; neighbour < graph[vertex].size(); neighbour++)
        {
            Edge new_edge = graph[vertex][neighbour];
            cout << "[" << new_edge.neighbour << "@" << new_edge.weight << "]";
        }
        cout << endl;
    }
}
