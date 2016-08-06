#include <iostream>
#include <algorithm>
using namespace std;

long tree[400000], arr[100000], max1, max2;

int getMAX(int ss, int se, int qs, int qe, int index)
{
    if (qs<=ss && qe>=se) return tree[index];
    if (se<qs || ss>qe) return 0;

    int mid = (ss+se)/2;
    int a = getMAX(ss, mid, qs, qe, 2*index+1);
    int b = getMAX(mid+1, se, qs, qe, 2*index+2);

    return max(a, b);
}

int construct(int x, int y, int s)
{
    if (x==y)
    {
        tree[s] = arr[x];
        return tree[s];
    }

    int mid = (x+y)/2;
    int a = construct(x, mid, 2*s+1);
    int b = construct(mid+1, y, 2*s+2);
    tree[s] =  max(a, b);

    return tree[s];
}

void update(int ss, int se, int x, int val, int index)
{
    arr[x]=val;
    if (x>se || x<ss) return;

    if (tree[index] < val) tree[index]=val;
    if (ss!=se)
    {
        int mid = (ss+se)/2;
        update(ss, mid, x, val, 2*index+1);
        update(mid+1, se, x, val, 2*index+2);
    }
}

int main()
{
    int n;
    cin >> n;

    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    construct(1, n, 1);
    update(1, n, 3, 100, 1);

    cout << getMAX(1, n, 1, 4, 1) << endl;
    return 0;
}
