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

int d[mx];
int mark[mx];

int dijkstra(int start_point, int end_point, vector<pair<int, int> > G[])
{
	d[start_point] = 0;
	priority_queue< pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > nodes_in_priority;

	nodes_in_priority.push(make_pair(d[start_point], start_point));

	while(!nodes_in_priority.empty())
	{
		int u = nodes_in_priority.top().second;
		int dis_till_here = nodes_in_priority.top().first;
		nodes_in_priority.pop();

		if(mark[u])
			continue;
		else
			mark[u] = 1;
		
		for(int i = 0; i<G[u].size(); ++i)
		{
			int v = G[u][i].first;
			int dis_u_v = G[u][i].second;

			if(dis_till_here + dis_u_v < d[v])
			{
				d[v] = dis_till_here + dis_u_v;
				nodes_in_priority.push(make_pair(d[v], v));
			}
		}
	}

	return d[end_point];
}

int main()
{
	rf;// wf;
	
	;
	return 0;
}