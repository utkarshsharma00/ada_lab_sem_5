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

bool BFS(vector<vector<Edge>> &graph, int source)
{
    priority_queue<Djikstra_Helper, vector<Djikstra_Helper>, greater<Djikstra_Helper>> queue;
    vector<bool> visited(graph.size(), false);

    queue.push(Djikstra_Helper(source, " " + to_string(source), 0));

    while (queue.size() > 0)
    {
        Djikstra_Helper remove = queue.top(); //get front
        queue.pop();                          //remove front

        if (visited[remove.vertex] == true)
        {
            continue;
        }
        else
        {
            visited[remove.vertex] = true;
        }

        cout << remove.vertex << " via " << remove.path_so_far << " @ " << remove.distance_so_far << endl;

        for (int neighbour = 0; neighbour < graph[remove.vertex].size(); neighbour++) //add children
        {
            Edge new_edge = graph[remove.vertex][neighbour];
            if (visited[new_edge.neighbour] == false)
            {
                Djikstra_Helper nbr = Djikstra_Helper(new_edge.neighbour, remove.path_so_far + to_string(new_edge.neighbour), remove.distance_so_far + new_edge.weight);
                queue.push(nbr);
            }
        }
    }
}

vector<vector<Edge>> Prims(vector<vector<Edge>> &graph, int source)
{
    priority_queue<Prims_Helper, vector<Prims_Helper>, greater<Prims_Helper>> queue;
    vector<bool> visited(graph.size(), false);
    vector<vector<Edge>> subgraph(graph.size());

    queue.push(Prims_Helper(source, -1, 0));

    while (queue.size() > 0)
    {
        Prims_Helper remove = queue.top(); //get front
        queue.pop();                       //remove front

        if (visited[remove.vertex] == true)
        {
            continue;
        }
        else
        {
            visited[remove.vertex] = true;
        }

        if (remove.acquiring_vertex != -1)
        {
            addEdge(subgraph, remove.vertex, remove.acquiring_vertex, remove.cost_of_acquiring);
        }

        for (int neighbour = 0; neighbour < graph[remove.vertex].size(); neighbour++) //add children
        {
            Edge new_edge = graph[remove.vertex][neighbour]; //new_edge basically means neighbouring_edge
            if (visited[new_edge.neighbour] == false)
            {
                Prims_Helper nbr = Prims_Helper(new_edge.neighbour, remove.vertex, new_edge.weight);
                queue.push(nbr);
            }
        }
    }

    return subgraph;
}


void Merge(vector<int> &pointer_array, vector<int> &rank_array, int vertex_1_set_leader, int vertex_2_set_leader) //required for Kruskal's
{
    if (rank_array[vertex_1_set_leader] < rank_array[vertex_2_set_leader])
    {
        pointer_array[vertex_1_set_leader] = vertex_2_set_leader;
    }

    else if (rank_array[vertex_2_set_leader] < rank_array[vertex_1_set_leader])
    {
        pointer_array[vertex_2_set_leader] = vertex_1_set_leader;
    }

    else
    {
        pointer_array[vertex_1_set_leader] = vertex_2_set_leader;
        rank_array[vertex_2_set_leader]++;
    }
}

int find(vector<int> &pointer_array, int vertex) //required for Kruskal's
{
    if (pointer_array[vertex] == vertex)
    {
        return vertex;
    }
    else
    {
        int set_leader = find(pointer_array, pointer_array[vertex]);
        return set_leader;
    }
}

void floyd_warshall(vector<vector<Edge>> &graph)
{
    vector<vector<int>> result = {graph.size(), vector<int>(graph.size(), INT_MAX)};

    for (int i = 0; i < graph.size(); i++)
    {
        result[i][i] = 0;
        for (int neighbour = 0; neighbour < graph[i].size(); neighbour++)
        {
            Edge new_edge = graph[i][neighbour];
            result[i][new_edge.neighbour] = new_edge.weight;
        }
    }

    for (int intermediate = 0; intermediate < graph.size(); intermediate++)
    {
        for (int source = 0; source < graph.size(); source++)
        {
            for (int destination = 0; destination < graph.size(); destination++)
            {
                if (intermediate == source || intermediate == destination || source == destination)
                {
                    continue;
                }
                else if (result[intermediate][destination] == INT_MAX || result[source][intermediate] == INT_MAX)
                {
                    continue;
                }
                else
                {
                    if (result[source][intermediate] + result[intermediate][destination] < result[source][destination])
                    {
                        result[source][destination] = result[source][intermediate] + result[intermediate][destination];
                    }
                }
            }
        }
    }

    for (int source = 0; source < graph.size(); source++)
    {
        for (int destination = 0; destination < graph.size(); destination++)
        {
            cout << result[source][destination] << "\t\t";
        }
        cout << endl;
    }
}


