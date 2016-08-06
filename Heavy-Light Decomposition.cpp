#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <cassert>
#include <set>
#include <string>
#include <cstring>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
#define mp make_pair
#define pi pair<int, int>
#define ms(a, v) memset(a, int(v), sizeof(a))
using namespace std;
const int mx=1e4+10;

int n, t, qs, qe, val, chno=1, idx=0;
static int pos[mx], wc[mx], chain[mx], st[4*mx],
           l[mx], lca[mx][20], ch[mx], vis[mx], p[mx];

vector<pi> g[mx];
pi ed[mx];
int cmp(pi l, pi r)
{
	return ch[l.first]>ch[r.first];
}

/*----------Segment tree functions-----------*/
void up(int x, int y, int r)
{
	if(y<qs || qe<x) return;
	if(qs<=x && y<=qe) return void(st[r]=val);
	int m=(x+y)>>1;
	up(x, m, 2*r); up(m+1, y, 2*r+1);
	st[r]=max(st[2*r], st[2*r+1]);
}
int qu(int x, int y, int r)
{
	if(y<qs || qe<x || qs>qe) return 0;
	if(qs<=x && y<=qe) return st[r];
	int m=(x+y)>>1;
	return max(qu(x, m, 2*r), qu(m+1, y, 2*r+1));
}
/*-----------------------------------------*/

/*-----------Lowest Common Ancestor---------*/
int lcanc(int x, int y)
{
	if(l[x]<l[y]) swap(x, y);
	while(l[x]>l[y])
	{
		int j=log2(l[x]-l[y]);
		x=lca[x][j];
	}

	int j=log2(l[x]);
	while(x!=y)
	{
		while(lca[x][j]==lca[y][j] && j)
			j--;
		x=lca[x][j], y=lca[y][j];
	}
	return x;
}
/*-----------------------------------------*/

/*-----------DFS to Preprocess---------*/
void dfs(int u)
{
	vis[u]=ch[u]=1;
	rep(i, 0, g[u].size()-1)
	{
		int v=g[u][i].first;
		if(vis[v]) continue;

		l[v]=l[u]+1;
		p[v]=lca[v][0]=u;

		int go=u, j=1;
		while(go!=-1)
		{
			go=lca[v][j]=lca[go][j-1];
			j++;
		}

		dfs(v);
		ch[u]+=ch[v];
	}
}
/*----------------------------------------------*/

/*------------Heavy Light Decomposition---------*/

void hld(int u)
{
	wc[u]=chno;
	qs=qe=pos[u]=++idx, val=g[u][0].second;
	up(1, n, 1);

	for(int i=1; i<g[u].size(); ++i)
	{
		int v=g[u][i].first;
		if(i==1)
		{
			hld(v);
			continue;
		}

		chno++;
		chain[chno]=v;
		hld(v);
	}
}
/*------------------------------------------------*/

/*---------- UPDATE AND QUERY FUNCTIONS-----------*/
void update(int u, int v)
{
	if(p[u]==v)
		qs=qe=pos[u];
	else if(p[v]==u)
		qs=qe=pos[v];
	up(1, n, 1);
}
int getmax(int a, int b)
{
	int ret=0;
	while(1)
	{
		if(wc[a]==wc[b])
		{
			qs=pos[b]+1, qe=pos[a];
			ret=max(ret, qu(1, n, 1));
			break;
		}

		int chnh=chain[wc[a]];
		qs=pos[chnh], qe=pos[a];
		ret=max(ret, qu(1, n, 1));
		a=p[chnh];
	}
	return ret;
}
int query(int a, int b)
{
	int anc=lcanc(a, b);
	return max(getmax(a, anc), getmax(b, anc));
}
/*-----------------------------------------*/

int main()
{
	rf;
	scanf("%d", &t);
	while(t--)
	{
		ms(lca, -1); ms(vis, 0);
		ms(ch, 0); ms(st, 0);
		rep(i, 0, mx-1) g[i].clear();
		
		g[1].push_back(mp(0, 0));
		vis[0]=1, ch[0]=1e9;
		chno=1, idx=0;

		scanf("%d", &n);
		rep(i, 1, n-1)
		{
			int u, v, d;
			scanf("%d %d %d", &u, &v, &d);
			g[u].push_back(mp(v, d));
			g[v].push_back(mp(u, d));
			ed[i]=mp(u, v);
		}

		dfs(1);
		rep(i, 1, n)
			sort(g[i].begin(), g[i].end(), cmp);

		chain[1]=1;
		hld(1);

		char q[100];
		while(1)
		{
			scanf("%s", q);
			if(q[0]=='D') break;
			if(q[0]=='C')
			{
				int i;
				scanf("%d %d", &i, &val);
				update(ed[i].first, ed[i].second);
			}
			else
			{
				int u, v;
				scanf("%d %d", &u, &v);
				printf("%d\n", query(u, v));
			}
		}
	}
	return 0;
}
