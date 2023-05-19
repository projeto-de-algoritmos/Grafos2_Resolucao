#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define INF 9999999

class Graph
{
public:
int numVertices;
vector<vector<pair<int, int>>> adjacencyList;

Graph(int numVertices)
{
    this->numVertices = numVertices;
    adjacencyList.resize(numVertices);
}

void addEdge(int u, int v, int weight)
{
    adjacencyList[u].push_back(make_pair(v, weight));
}

int dijkstra(int source, int target)
{
    vector<int> distances(numVertices, INF);
    vector<int> visited(numVertices, 0);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distances[source] = 0;

    pq.push(make_pair(distances[source], source));

    while (!pq.empty())
    {
        pair<int, int> p = pq.top();
        int u = p.second;
        pq.pop();

        if (!visited[u])
        {
            visited[u] = 1;
            for (auto it = adjacencyList[u].begin(); it != adjacencyList[u].end(); it++)
            {
                int v = it->first;
                int weight = it->second;

                if (distances[v] > distances[u] + weight)
                {
                    distances[v] = distances[u] + weight;
                    pq.push(make_pair(distances[v], v));
                }
            }
        }
    }

    return distances[target];
}
};

int main()
{
int numCities, numRoads, city1, city2, weight;

cin >> numCities >> numRoads;

Graph graph(numCities), graph2(numCities);

for (int i = 0; i < numRoads; i++)
{
    cin >> city1 >> city2 >> weight;
    graph.addEdge(--city1, --city2, weight);
    graph.addEdge(city2, city1, weight);
}

for (int i = 0; i < numCities; i++)
{
    for (auto it1 = graph.adjacencyList[i].begin(); it1 != graph.adjacencyList[i].end(); it1++)
    {
        city1 = it1->first;
        weight = it1->second;

        if (!graph.adjacencyList[city1].empty())
        {
            for (auto it2 = graph.adjacencyList[city1].begin(); it2 != graph.adjacencyList[city1].end(); it2++)
            {
                if (i != it2->first)
                    graph2.addEdge(i, it2->first, weight + it2->second);
            }
        }
    }
}

int minDistance = graph2.dijkstra(0, numCities - 1);

cout << (minDistance == INF ? -1 : minDistance) << endl;

return 0;
}