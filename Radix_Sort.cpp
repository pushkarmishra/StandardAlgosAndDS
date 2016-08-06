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
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5 + 10, mod = 1e9+7;

int bucket[10];
int aux_arr[mx];
int a[mx];
int p_10 = 1;

void sort_by_digit(int a[], int n)
{
	memset(bucket, 0, sizeof bucket);

	rep(i, 1, n)
	{
		int num = a[i]/p_10;
		bucket[num%10]++;
	}

	rep(i, 1, 9)
		bucket[i] += bucket[i-1];

	for(int i = n; i; --i)
	{
		int num = a[i]/p_10;
		int idx = bucket[num%10];

		aux_arr[idx] = a[i];
		bucket[num%10]--;
	}
	
	memcpy(a, aux_arr, sizeof aux_arr);
	p_10 *= 10;
}

int main()
{
	rf;// wf;
	ios::sync_with_stdio(0);

	int n;
	cin >> n;

	rep(i, 1, n)
		cin >> a[i];

	rep(i, 1, 10)
		sort_by_digit(a, n);

	rep(i, 1, n)
		cout << a[i] << ' ';
	cout << endl;

	return 0;
}

