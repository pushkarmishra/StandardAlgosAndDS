//The graph 2-D array is the adjacency matrix depicting the cost between any two edges. graph[i][j] represents
//edge cost from i to j. If there exists no edge between i and j, then,
//graph[i][j]=graph[j][i]=(graph[i][i])=123456789(random large value).
#include <iostream>
using namespace std;

int bellmanford(int graph[][100000001], int start, int end, int nodes)
{
    int min, temp;
    int m[nodes][nodes];         //row 1 is for the node 'end'. Next nodes-1 rows contain the other rows.
    m[0][0] = 0;                 //the m(end, 0) element is set to 0.
    for (int i = 1; i < nodes; i++)
        m[i][0] = 123456789;     //Initializing all other nodes to a huge number.

    for (int j = 1; j < nodes; j++)
    {
        for (int k = 0; k < nodes; k++)
        {
            min = 123456789;
            for (int p = 1; p <= nodes; p++)
            {
                temp = m[p][j-1] + graph[k][p];
                if (temp < min)
                    min = temp;
            }
            (m[k][j-1] < min)? m[k][j] = m[k][j-1]: m[k][j] = min;
        }
    }

    return m[start][nodes-1];
}

int main()
{
    return 0;
}
