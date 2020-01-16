#include <iostream>
#include <climits>
#include <vector>

int** mapToGraph(int** map, int x, int y)
{
    //***int graph[x*y][x*y];***
    int** graph = new int*[y];
    for(int i = 0; i < y; ++i)
        graph[i] = new int[x];
    //******

    for(int i = 0; i < x; ++i)
        for(int j = 0; j < y; ++j)
            graph[i][j]=INT_MAX;

    for(int i = 0; i < x; ++i)
        for(int j = 0; j < y; ++j)
        {
            if(j>0) graph[x*(j-1) + i][x*j+1] = map[i][j]; // z gory
            if(i>0) graph[x*j + i -1][x*j + 1] = map[i][j]; // z lewej
            if(i<x-1) graph[x*j + i + 1][x*j+1] = map[i][j]; // z prawej
            if(j < y-1) graph[x*(j+1) + i][x*j+1] = map[i][j]; // z dolu
        }
    return graph;
    //JESZCZE USUWANIE
}

/*std::vector <int> Dijkstra(int graph[], int V, int source)
{
    int prev[V];
    int d[V];
    for(int i = 0; i < V; ++i)
        d[i] = INT_MAX;

    d[source] = 0;
    std::priority_queue <int> q;
}
*/
/*template <typename valueType>
struct Graph
{
    struct Node
    {
        valueType value;
        std::vector < std::pair<Node*, int> > edges;//edge, waga
        bool operator <(Node n)
        {
            return this->value < n.value;
        }
    };

    size_t _size;
    std::vector <Node&> nodes;

    Node& getNodeFromValue(valueType val)
    {
        size_t i = 0;
        while(i < nodes.size() && nodes[i].first->value != val)
            ++i;
        return nodes[i];
    }
    void addNode(valueType from, valueType newNodeValue, int weight)
    {
        Node& current = getNodeFromValue(from);
        Node* newNode = new Node;
        newNode->value = newNodeValue;
        current.edges.push_back(std::make_pair(newNode, weight));
        ++_size;
    }
};
*/

/*template <typename valueType>
std::vector <valueType> Dijsktra(Graph <valueType> g, valueType sourceValue)
{
    typedef Graph<valueType> graph;
    typedef typename graph::Node node;
    auto source = graph::getNodeFromValue(sourceValue);


    int d[g._size()], p[g._size()];

    std::priority_queue<node> Q, S;
    for(size_t i = 0; i < g._size; ++i)
        Q.push(g.nodes[i]);

    d[sourceValue] = 0;
    for(size_t i = 0; i < g._size; ++i)
    {
        if(i != sourceValue) d[i] = INT_MAX;
        p[i] = -1;
    }

    while(!Q.empty())
    {
        node u = Q.pop();
        S.push(u);
        for(auto w = 0; w < u.edges.size(); ++w)
            if(d[u.edges[w]->value] < d[u]->value)
            {
                d[u.edges[w]]
            }
    }
}*/

bool belongsTo(int elem, std::vector<int> vec)
{
    for(int i = 0; i < vec.size(); ++i)
        if(vec[i] == elem)
            return true;
    return false;
}

int valToPos(int val, std::vector<int> vec)
{
    for(int i = 0; i < vec.size(); ++i)
        if(vec[i] == val)
            return i;
}

template <int Size>
std::pair<int[Size], int[Size]> Dijkstra(int graph[Size][Size], int source)
{
    int d[Size];
    int p[Size];
    d[source] = 0;
    for(int i = 0; i < Size; ++i)
    {
        p[i] = -1;
        if(i != source) d[i] = INT_MAX;
    }
    std::vector<int> Q, S;
    for(int i = 0; i < Size; ++i)
        Q.push_back(i);
    while(!Q.empty())
    {
        int Dmin = INT_MAX;
        int umin = 0;
        int u;
        while(umin < Size)
        {
            if(belongsTo(umin, Q) && d[umin] < Dmin)
            {
                u = umin;
                Dmin = d[umin];
            }
           ++umin;
        }//while

        Q.erase(Q.begin() + valToPos(u, Q)); //usuwamy u-ty element Q
        for(int w = 0; w < Size; ++w)
        {
            if(graph[u][w] > 0 && belongsTo(w, Q))
            {
                if(d[w] > d[u] + graph[u][w])
                {
                    d[w] = d[u] + graph[u][w];
                    p[w] = u;
                }//IF
            }//IF
        }//FOR
    }//WHILE

    std::pair<int[Size], int[Size]> result;
    for(int i = 0; i < Size; ++i)
    {
        result.first[i] = d[i];
        result.second[i] = p[i];
    }
    return result;
}

int main()
{
    int g[3][3];
    g[0][0] = 0;
    g[0][1] = 1;
    g[0][2] = 7;
    g[1][0] = -1;
    g[1][1] = 0;
    g[1][2] = 2;
    g[2][0] = -1;
    g[2][1] = -1;
    g[2][2] = 0;
    std::pair<int[3], int[3]> p = Dijkstra(g, 0);

    for(int i = 0; i < 3; ++i)
        std::cout << p.first[i] << " ";
    std::cout << std::endl;
    for(int i = 0; i < 3; ++i)
        std::cout << p.second[i] << " ";
}