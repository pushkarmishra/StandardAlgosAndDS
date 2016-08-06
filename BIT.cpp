//The binary indexed tree, or the Fenwick tree is implemented using an array. It helps in storing cumulative frequencies,
//and allows the modification as well summation between two indices in sub-polynomial time. In the tree array, index stores
//the sum of that many values before it and including it, as it has number of trailing zeroes in the binary representation.
//Thus, odd numbers store their own value. index 2 stores the sum of 1st and second value, index 4 stores sum of 1-4, index
//6 stores sum of 5th and 6th element and so on.
#include <iostream>
using namespace std;

void update(int tree[], int idx, int lastindex, int val)  //If there is a change in any value, this function modifies
{                                                         //the cumulative sum by changing the values of those indexes
    while(idx <= lastindex)                               //in the tree which are responsible for the value modified.
    {
        tree[idx] += val;                                 //The idx is incremented till the last index is reached.
        idx += (idx & -idx);                              //& operator is used to find the next responsible index.
    }
}

int getsum (int tree[], int idx)                          //This function reports the cumulative sum upto the given index.
{
    int sum = 0;
    while (idx > 0)
    {
        sum += tree[idx];
        idx -= (idx & -idx);                              //index is decreased till it reaches 0.
    }
    return sum;
}

int main()
{
    int arr[] = {0, 1, 4, 2, 5, 3, 6, 1, 6, 2, 10};
    int BIT[11]={0};

    for (int i = 1; i <= 10; i++)
        update(BIT, i, 11, arr[i]);

    cout << getsum(BIT, 9)-getsum(BIT, 8) << endl;
    return 0;
}
