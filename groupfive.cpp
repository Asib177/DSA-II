#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge
{
    char src, dest;
    int weight;
};

class Graph
{
public:
    int V, E;
    vector<Edge> edges;

    Graph(int V, int E) : V(V), E(E) {}

    void addEdge(char src, char dest, int weight)
    {
        Edge edge = {src, dest, weight};
        edges.push_back(edge);
    }

    int boruvkaMST()
    {
        vector<int> parent(V, -1);
        vector<int> cheapest(V, -1);

        int numTrees = V;
        int MSTweight = 0;

        while (numTrees > 1)
        {
            fill(cheapest.begin(), cheapest.end(), -1);

            for (int i = 0; i < E; ++i)
            {
                int set1 = find(parent, edges[i].src - 'A');
                int set2 = find(parent, edges[i].dest - 'A');
                // cout << set1 << " ";

                if (set1 != set2)
                {
                    if (cheapest[set1] == -1 || edges[cheapest[set1]].weight > edges[i].weight)
                        cheapest[set1] = i;

                    if (cheapest[set2] == -1 || edges[cheapest[set2]].weight > edges[i].weight)
                        cheapest[set2] = i;
                }
            }

            for (int i = 0; i < V; ++i)
            {
                if (cheapest[i] != -1)
                {
                    int set1 = find(parent, edges[cheapest[i]].src - 'A');
                    int set2 = find(parent, edges[cheapest[i]].dest - 'A');

                    if (set1 != set2)
                    {
                        cout << "Edge added: " << edges[cheapest[i]].src << " - " << edges[cheapest[i]].dest
                             << " Weight: " << edges[cheapest[i]].weight << endl;

                        MSTweight += edges[cheapest[i]].weight;
                        unionSets(parent, set1, set2);
                        numTrees--;
                    }
                }
            }
        }

        return MSTweight;
    }

private:
    int find(vector<int> &parent, int i)
    {
        if (parent[i] == -1)
            return i;
        return find(parent, parent[i]);
    }

    void unionSets(vector<int> &parent, int x, int y)
    {
        int rootX = find(parent, x);
        int rootY = find(parent, y);
        parent[rootX] = rootY;
    }
};

int main()
{
    int V = 7;
    int E = 11;

    Graph graph(V, E);

    graph.addEdge('A', 'B', 12);
    graph.addEdge('A', 'D', 5);
    graph.addEdge('B', 'C', 8);
    graph.addEdge('B', 'D', 10);
    graph.addEdge('B', 'E', 7);
    graph.addEdge('C', 'E', 2);
    graph.addEdge('D', 'E', 15);
    graph.addEdge('D', 'F', 6);
    graph.addEdge('E', 'F', 1);
    graph.addEdge('E', 'G', 9);
    graph.addEdge('F', 'G', 11);

    int MSTweight = graph.boruvkaMST();

    cout << "Weight of the Minimum Spanning Tree: " << MSTweight << endl;

    return 0;
}
