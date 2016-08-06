#include <iostream>
using namespace std;

int binarysearch(int arr1[], int i, int j, int num)     //For sorted arrays.
{
    if (j - i < 2)
    {
        if (num == arr1[i])
            return i+1;
        else if (num == arr1[j])
            return j+1;
        else
            return 0;
    }

    else
    {
        int mid = (i+j)/2;
        if (arr1[mid] <= num)
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
    int arr[] = {4, 44, 66, 234, 546, 901, 6634};
    cout << binarysearch(arr, 0, 6, 5) << endl;
    return 0;
}
