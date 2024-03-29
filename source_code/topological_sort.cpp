#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <stack>
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

void slave_for_topological_sort(vector<vector<Edge>> &graph, int source, vector<int> &visited, stack<int> &stack)
{
    visited[source] = true;

    for (int neighbour = 0; neighbour < graph[source].size(); neighbour++)
    {
        Edge new_edge = graph[source][neighbour];
        if (visited[new_edge.neighbour] == false)
        {
            slave_for_topological_sort(graph, new_edge.neighbour, visited, stack);
        }
    }

    stack.push(source);
}

void topological_sort(vector<vector<Edge>> &graph)
{
    stack<int> stack;
    vector<int> visited(graph.size(), 0);
    for (int i = 0; i < graph.size(); i++) //i is vertex
    {
        if (visited[i] == 0)
        {
            slave_for_topological_sort(graph, i, visited, stack);
        }
    }

    while ((stack.size() > 0))
    {
        int val = stack.top();
        stack.pop();
        cout << val << " ";
    }
    cout << endl;
}

int main(int argc, char **argv)
{
    vector<vector<Edge>> graph(7);
    graph[0].push_back(Edge(1, 1));
    graph[0].push_back(Edge(4, 1));
    graph[1].push_back(Edge(2, 1));
    graph[2].push_back(Edge(3, 1));
    graph[6].push_back(Edge(4, 1));
    graph[6].push_back(Edge(5, 1));
    graph[5].push_back(Edge(3, 1));
    topological_sort(graph);
}
