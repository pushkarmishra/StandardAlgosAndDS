#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <stack>
#include <cassert>
#include <set>
#include <climits>
#include <string>
#include <cstring>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;
const int mx=1e9;

//--------------------------------------K-D Tree (4D)----------------------------------------//
struct kdnode
{
	kdnode *l, *r;
	int div[4], cnt, leaf;
	kdnode(kdnode* put, int a, int b, int c, int d, int le)
	{
		l=r=put;
		div[0]=a, div[1]=b, div[2]=c, div[3]=d;
		leaf=le; cnt=0;
	}
};kdnode *kdroot, *kddummy;

int cons[4], qs[4], qe[4], rs[4], re[4], state, cmm;
vector< vector<int> > pts;
int cmp(vector<int> l, vector<int> r)
{
	return l[cmm]<r[cmm];
}

void kdconstruct(int lc, int rc, kdnode* &cur, int d)
{
	if(lc>rc) return;
	if(lc==rc)
	{
		cur = new kdnode(kddummy, pts[lc][0], pts[lc][1], pts[lc][2], pts[lc][3], 1);
		return;
	}

	cmm=d;
	int sz=(rc-lc+1)/2; sz+=lc;
	sort(pts.begin()+lc, pts.begin()+rc+1, cmp);

	int piv=lc;
	while(pts[piv][d] < pts[sz][d]) piv++;
	cur = new kdnode(kddummy, pts[piv][0], pts[piv][1], pts[piv][2], pts[piv][3], 0);

	int nd=d+1; if(nd>=4)nd-=4;
	kdconstruct(lc, piv-1, cur->l, nd); kdconstruct(piv, rc, cur->r, nd);
}

void change_state(kdnode* &cur, int d)
{
	if(cur->leaf)
		return void(cur->cnt+=state);

	int nd=d+1; if(nd>=4)nd-=4;
	if(cur->div[d] > cons[d]) change_state(cur->l, nd);
	else change_state(cur->r, nd);

	cur->cnt = cur->l->cnt + cur->r->cnt;

}

int comp(int x[4], int y[4])
{
	if((y[0]<qs[0] or y[1]<qs[1] or y[2]<qs[2] or y[3]<qs[3]) or
	   (qe[0]<x[0] or qe[1]<x[1] or qe[2]<x[2] or qe[3]<x[3]))
		return 1;

	if((qs[0]<=x[0] and qs[1]<=x[1] and qs[2]<=x[2] and qs[3]<=x[3]) and
	   (y[0]<=qe[0] and y[1]<=qe[1] and y[2]<=qe[2] and y[3]<=qe[3]))
		return 2;

	return 3;
}

int kdqu(kdnode*cur, int d, int x[4], int y[4])
{
	if(cur->leaf)
	{
		rep(i, 0, 3) x[i]=y[i]=cur->div[i];		
		return (comp(x, y)==2)? cur->cnt : 0;
	}

	if(comp(x, y)==1 || cur==kddummy) return 0;
	if(comp(x, y)==2) return cur->cnt;
	
	int nd=d+1; if(nd>=4)nd-=4;
 	
 	int *lx=new int[4]; int *ly=new int[4];
 	rep(i, 0, 3) lx[i]=x[i], ly[i]=y[i];
 	ly[d] = cur->div[d]-1;
 	int lcnt = kdqu(cur->l, nd, lx, ly);
 	delete lx; delete ly;

 	int *rx=new int[4]; int *ry=new int[4];
 	rep(i, 0, 3) rx[i]=x[i], ry[i]=y[i];
 	rx[d] = cur->div[d];
 	int rcnt = kdqu(cur->r, nd, rx, ry);
 	delete rx; delete ry;

 	return lcnt+rcnt;
}
int kdquery(int a, int b, int c, int d)
{
	rep(i, 0, 3) rs[i]=1, re[i]=mx;
	qs[0]=a, qs[1]=b, qs[2]=a, qs[3]=b;
	qe[0]=c, qe[1]=d, qe[2]=c, qe[3]=d;

	return kdqu(kdroot, 0, rs, re);
}
//-------------------------------------------------------------------------------------------//

int main()
{
	rf;
	;
	return 0;
}