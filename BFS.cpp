#include <iostream>
#include <vector>
using namespace std;

int bfs (vector< vector<int> > &a, int b[], vector< vector<int> > &vec, int d, int n)
{
    int t = d;                                                                //d denotes the layer which is currently being accessed.
    while (t <= n)                                                            //maximum layers can be n for n nodes.
    {
        for (int i = 0; i < vec[t-1].size(); i++)                             //For each element in the previous layer (loop till end of layer),
        {
            for (int j = 0; j < a[vec[t-1][i]].size(); j++)
            {
                if (b[a[vec[t-1][i]][j]] == 0)                                //It is checked whether its adjacent element has been accessed or not.
                {
                    b[a[vec[t-1][i]][j]] = 1;
                    vec[t].push_back(a[vec[t-1][i]][j]);                      //if not, Adjacent elements are added to the current layer.
                }
            }
        }
        t = t+1;                                                              //Moving on to next layer.
    }
}

int main()
{
    int n, m, temp1, temp2, level = 1, start = 1;
    cin >> n >> m;                                           //Accepting number of nodes(n) and edges(m) for the graph.

    vector< vector<int> > v(n+1);                                  //Declaring two dimensional vector with n rows.
    vector< vector<int> > v1(n+1);
    int status[n];


    for(int i = 1; i <= n; i++)
        status[i] = 0;

    for (int j = 1; j <= m; j++)
    {
        cin >> temp1 >> temp2;                               //Taking in edges and forming adjacency list using vectors (undirected graph).
        v1[temp1].push_back(temp2);
        v1[temp2].push_back(temp1);
    }

    status[start] = 1;
    v[0].push_back(start);                              //Putting the start value in first layer to make it the root (here, root is 1).

    bfs (v1, status, v, level, n);                     //Calling BFS.

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j < v[i].size(); j++)           //Printing the BFS tree formed, with certain number of layers.
            cout << v[i][j] << ' ';
        cout << endl;
    }
    return 0;
}
