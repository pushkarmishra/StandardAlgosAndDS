#include <iostream>
using namespace std;

void merge(int arr[], int i, int j, int mid, int arr1[])
{
    int k = mid + 1, l = i, start = i;
    while ((i <= mid) and (k <= j))
        arr1[l++] = (arr[i] < arr[k])? arr[i++]: arr[k++];

    while (k <= j) arr1[l++] = arr[k++];
    while (i <= mid) arr1[l++] = arr[i++];

    for (int p = start; p <= j; p++) arr[p] = arr1[p];
    for (int i = 0; i < 7; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void mergesort(int arr[], int i, int j, int arr1[])
{
    if (i < j)                                  //If there is a difference of 1 or more b/w i and j, this means,
    {                                           //there are more than one element.
       int mid = (i + j)/2;
       mergesort(arr, i, mid, arr1);            //Calling mergesort on each half.
       mergesort(arr, mid+1, j, arr1);
       merge(arr, i, j, mid, arr1);             //Merging two halves.
    }
}

int main()
{
    int arr[] = {4, 6, 3, 2, 7, 3, 9};
    int arr1[6];
    mergesort(arr, 0, 6, arr1);

    for (int i = 0; i < 7; i++)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
