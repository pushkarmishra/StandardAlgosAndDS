#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <set>
#include <string>
#include <cstring>
#include <queue>
#include <cassert>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5 + 10, mod = 1e9+7;

void radixSortHelper(int arr[], int n, int* aux_arr) {
	int pow10 = 1;
	int sorter[10];

	do {
		memset(sorter, 0, sizeof(sorter));
	    
	    for (int i = 0; i < n; i += 1) {
	        int num = abs(arr[i]) / pow10;
	        num = num - ((num / 10) * 10);
	        
	        sorter[num] += 1;
	    }
	    
	    for (int i = 1; i < 10; i += 1) {
	        sorter[i] += sorter[i-1];
	    }
	    
	    for (int i = n - 1; i >= 0; i -= 1) {
	        int num = abs(arr[i]) / pow10;
	        num = num - ((num / 10) * 10);
	        
	        aux_arr[sorter[num] - 1] = arr[i];
	        sorter[num] -= 1;
	    }
	    
	    memcpy(arr, aux_arr, sizeof(int) * n);
	    pow10 *= 10;

	} while (pow10 <= 1e9);
}

void radixSort(int arr[], int n) {
	int *aux_arr = new int[n];
	radixSortHelper(arr, n, aux_arr);

	int idx = 0;
	for (int i = n - 1; i >= 0; i -= 1) {
        if (aux_arr[i] < 0) {
            arr[idx] = aux_arr[i];
            idx += 1;
        }
    }
    
    for (int i = 0; i < n; i += 1) {
        if (aux_arr[i] >= 0) {
            arr[idx] = aux_arr[i];
            idx += 1;
        }
    }
}

int main()
{
	// rf;// wf;
	ios::sync_with_stdio(0);

	int n;
	cin >> n;

	int a[n];
	for (int i = 0; i < n; i += 1) {
		cin >> a[i];
	}
	radixSort(a, n);

	for (int i = 0; i < n; i += 1) {
		cout << a[i] << ' ';
	}
	cout << endl;

	return 0;
}
