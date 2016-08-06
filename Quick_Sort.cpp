#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <cstring>
#include <cassert>
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5+10, mod = 1e9+7;

int pivot(int a[], int first, int last) 
{
	int  p = first;
	int pivotElement = a[first];
 
	for(int i = first+1 ; i <= last ; i++)
	{
		if(a[i] <= pivotElement)
		{
			p++;
			swap(a[i], a[p]);
		}
	}
 
	swap(a[p], a[first]);
	return p;
}

void quickSort( int a[], int first, int last ) 
{
	int pivotElement;
 
	if(first < last)
	{
		pivotElement = pivot(a, first, last);
		quickSort(a, first, pivotElement-1);
		quickSort(a, pivotElement+1, last);
	}
}

int main()
{
	rf;// wf;

	int a[] = {3, 2, 1, 5, 7, 0};
	quickSort(a, 0, 5);

	rep(i, 0, 5)
		cout << a[i] << ' ';
	cout << endl;
	return 0;
}