#include <iostream>
#include <vector>
using namespace std;

int dfs(vector< vector<int> > &vec, vector<int> &vec1, int a[])
{
    for (int k = 0; k < vec1.size(); k++)                              //This is the list which stores the new nodes coming in.
    {
        if (a[vec1[k]] == 0)                                           //Already explored nodes aren't explored again.
        {
            a[vec1[k]] = 1;
            for (int l = 0; l < vec[vec1[k]].size(); l++)
                vec1.push_back(vec[vec1[k]][l]);                       //If unexplored node is found, it is added to the list, to be explored later.
        }
    }

    return 0;
}

int main()
{
    int n, m, temp1, temp2;
    cin >> n >> m;

    vector< vector<int> > v(n+1);
    vector <int> v1;
    int status[n+1];

    for (int i = 1; i <= m; i++)
    {
        cin >> temp1 >> temp2;
        v[temp1].push_back(temp2);
        v[temp2].push_back(temp1);
    }
    for (int i = 1; i <= n; i++)
        status[i] = 0;

    v1.push_back(1);
    dfs(v, v1, status);                                              //Calling dfs (with root as 1).

    return 0;
}
