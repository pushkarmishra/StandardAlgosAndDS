#include <iostream>
using namespace std;

int binarysearch(int arr1[], int i, int j, int num)
{
    if (j - i < 2)
    {
        if (num < arr1[i])
            return i;
        else if (arr1[j] == 0)
            return -1;
        else
            return j;
    }

    else
    {
        int mid = (i+j)/2;
        if (arr1[mid] < num)
        {
            i = mid;
            return binarysearch(arr1, i, j, num);
        }
        else if (arr1[mid] > num)
        {
            j = mid;
            return binarysearch(arr1, i, j, num);
        }
    }
}

int main()
{
    int n, t = 1, check;
    cin >> n;
    int arr[n], arr1[n];

    fill(arr1, arr1 + n, 0);

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    arr1[0] = arr[0];
    for (int j = 1; j < n; j++)
    {
        check = binarysearch(arr1, 0, t, arr[j]);
        if (check == -1)
        {
            arr1[t] = arr[j];
            t = t + 1;
        }
        else if (check != -1)
            arr1[check] = arr[j];
    }

    return 0;
}
