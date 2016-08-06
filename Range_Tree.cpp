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
#define wf freopen("out.out", "w", stdout)
using namespace std;
#define mpp make_pair
#define ff first
#define ss second
#define pb push_back
#define pii pair<int, int>
const int mx=1e9, mxn=1e5+10;

static int cm[mxn][4], del[mxn], ins[mxn];
int tot, q, x1, x2, yy1, y2, idx, inn=-1;
char ch[mxn][1];

int *xs, *v;
vector< pii > pts[4];

//--------------------------------------Range Tree (2D)--------------------------------------//
struct rnode
{
	rnode *l, *r;
	int* ys, *lp, *rp, *b;
	int div, cnt, leaf, sz;
	rnode(rnode* put, int d, int le)
	{
		l=r=put;
		div=d, leaf=le; cnt=0;
	}
};rnode *root[4], *dummy;
int cmm, state;

inline void frac_casc(int* tbf, rnode* &cur, rnode* &ch)
{
	int i=1, j=1;
	while(j<=ch->sz && i<=cur->sz)
	{
		while(ch->ys[j] < cur->ys[i] && j<=ch->sz) j++;
		tbf[i++]=j;
	}
	while(i<=cur->sz) tbf[i++]=ch->sz+1;
	tbf[cur->sz+1]=ch->sz+1;
}
void fory(rnode* &cur, vector<pii> der)
{
	int sz=der.size();
	rep(i, 0, sz-1) v[i]=der[i].ff;

	cur->sz = unique(v, v+sz)-v;
	cur->ys=new int[cur->sz+2]; cur->b=new int[cur->sz+2];
	cur->lp=new int[cur->sz+2]; cur->rp=new int[cur->sz+2];
	
	rep(i, 0, cur->sz-1) cur->ys[i+1]=v[i], cur->b[i+1]=0;
	cur->ys[cur->sz+1]=2*mx; cur->b[0]=cur->b[cur->sz+1]=0;

	if(cur->leaf) return;

	vector<pii> lh, rh;
	rep(i, 0, sz-1)
		(der[i].ss < cur->div)? lh.pb(der[i]): rh.pb(der[i]);

	fory(cur->l, lh); fory(cur->r, rh);
	frac_casc(cur->lp, cur, cur->l); frac_casc(cur->rp, cur, cur->r);
}
void build_dim(rnode* &cur, int* v, int lc, int rc)
{
	if(lc==rc)
		return void(cur=new rnode(dummy, v[lc], 1));

	int mid=(lc+rc)>>1;
	cur = new rnode(dummy, v[mid+1], 0);
	
	build_dim(cur->l, v, lc, mid); build_dim(cur->r, v, mid+1, rc);
}

inline void bitup(int *bit, int i, int sz)
{
	for(; i<=sz; i+=i&-i) bit[i]+=state;
}
inline void change_statex(rnode* cur, int x, int y)
{
	y=lower_bound(cur->ys+1, cur->ys+cur->sz+1, y) - cur->ys;
	while(true)
	{
		bitup(cur->b, y, cur->sz+1);
		if(cur->leaf) break;
		
		if(cur->div > x) y=cur->lp[y], cur=cur->l;
		else y=cur->rp[y], cur=cur->r;
	}
}

inline int getp(rnode **v, rnode* cur, int nv, int yy1, int y2, int * yo, int * yt)
{
	int id=-1;
	while(true)
	{
		v[++id]=cur;
		yo[id]=yy1, yt[id]=y2;
		if(cur->leaf) break;
		
		if(cur->div > nv) yy1=cur->lp[yy1], y2=cur->lp[y2], cur=cur->l;
		else yy1=cur->rp[yy1], y2=cur->rp[y2], cur=cur->r;
	}
	return id;
}

inline int bitqu(int *bit, int i)
{
	int ret=0;
	for(; i; i-=i&-i) ret+=bit[i];
	return ret;
}
int queryx(rnode* &cur, int x1, int yy1, int x2, int y2)
{
	if(x1>x2 || yy1>y2) return 0;
	int tyy1=lower_bound(cur->ys+1, cur->ys+cur->sz+1, yy1)-cur->ys;
	int ty2=lower_bound(cur->ys+1, cur->ys+cur->sz+1, y2)-cur->ys;
	
	rnode **lx = new rnode*[20], **rx = new rnode*[20];
	int *lyy1=new int[20], *ly2=new int[20], *ryy1=new int[20], *ry2=new int[20];

	int szl=getp(lx, cur, x1, tyy1, ty2, lyy1, ly2),
	    szr=getp(rx, cur, x2, tyy1, ty2, ryy1, ry2);

	int i=0, ret=0;
	while(lx[i] == rx[i] and i<szl) ++i;

	rep(j, i, szl-1)
		if(lx[j]->div>x1) lyy1[j]=lx[j]->rp[lyy1[j]], ly2[j]=lx[j]->rp[ly2[j]];
	rep(j, i, szr-1)
		if(rx[j]->div<=x2)ryy1[j]=rx[j]->lp[ryy1[j]], ry2[j]=rx[j]->lp[ry2[j]];

	rep(j, i, szl-1)
	{
		if(lx[j]->div > x1 and lx[j]->r->ys[ly2[j]] > y2) ly2[j]--;
		if(lx[j]->div > x1)
			ret += bitqu(lx[j]->r->b, ly2[j])-bitqu(lx[j]->r->b, lyy1[j]-1);
	}
	rep(j, i, szr-1)
	{
		if(rx[j]->div <= x2 and rx[j]->l->ys[ry2[j]] > y2) ry2[j]--;
		if(rx[j]->div <= x2)
			ret += bitqu(rx[j]->l->b, ry2[j])-bitqu(rx[j]->l->b, ryy1[j]-1);
	}
	
	if(lx[szl]->ys[ly2[szl]] > y2) ly2[szl]--;
	if(rx[szr]->ys[ry2[szr]] > y2) ry2[szr]--;

	if(x1<=lx[szl]->div and lx[szl]->div<=x2)
		ret+= bitqu(lx[szl]->b, ly2[szl])-bitqu(lx[szl]->b, lyy1[szl]-1);
	if(x1<=rx[szr]->div and rx[szr]->div<=x2 and lx[szl]!=rx[szr])
		ret+= bitqu(rx[szr]->b, ry2[szr])-bitqu(rx[szr]->b, ryy1[szr]-1);

	delete lx; delete rx; delete lyy1; delete ly2; delete ryy1; delete ry2;
	return ret;
}
//-------------------------------------------------------------------------------------------//

//-------------------------------------------------------------------------------------------//
void take_input_and_build_rangetrees()
{
	scanf("%d", &q);
	rep(i, 1, q)
	{
		scanf("%s", ch[i]);
		if(ch[i][0]=='I' or ch[i][0]=='Q')
		{
			scanf("%d %d %d %d", &cm[i][0], &cm[i][1], &cm[i][2], &cm[i][3]);
			if(ch[i][0]=='I')
			{
				int id=0;
				ins[++inn]=i;
				for(int j=0; j<=2; j+=2) for(int k=1; k<=3; k+=2)
					pts[id++].pb(mpp(cm[i][k], cm[i][j]));
			}
		}
		else scanf("%d", &del[i]);
	}
	if(inn<0) return;

	rep(i, 0, 3)
	{
		sort(pts[i].begin(), pts[i].end());
		
		rep(j, 0, inn) xs[j]=pts[i][j].ss;
		sort(xs, xs+inn+1);
		int sz=unique(xs, xs+inn+1)-xs;
		build_dim(root[i], xs, 0, sz-1);

		fory(root[i], pts[i]);
	}
}
//-------------------------------------------------------------------------------------------//

int main()
{
	//rf; wf;
	dummy = new rnode(NULL, 0, 0);
	rep(i, 0, 3) root[i]=new rnode(dummy, 0, 0);
	xs=new int[mxn];
	v=new int[mxn];

	take_input_and_build_rangetrees();

	rep(i, 1, q)
	{
		if(ch[i][0]=='I')
		{
			tot++, state=1;
			x1=cm[i][0], yy1=cm[i][1], x2=cm[i][2], y2=cm[i][3];
			
			int id=0;
			for(int j=0; j<=2; j+=2) for(int k=1; k<=3; k+=2)
				change_statex(root[id++], cm[i][j], cm[i][k]);
		}
		else if(ch[i][0]=='Q')
		{
			x1=cm[i][0], yy1=cm[i][1], x2=cm[i][2], y2=cm[i][3];
			
			if(inn<0) {printf("0\n"); continue;}

			int ans=queryx(root[3], 1, 1, mx, yy1-1)+queryx(root[3], 1, 1, x1-1, mx)
			    +queryx(root[0], x2+1, 1, mx, mx)+queryx(root[0], 1, y2+1, mx, mx);
			ans-= queryx(root[0], x2+1, y2+1, mx, mx)+queryx(root[3], 1, 1, x1-1, yy1-1)
			    +queryx(root[1], x2+1, 1, mx, yy1-1)+queryx(root[2], 1, y2+1, x1-1, mx);

			printf("%d\n", tot-ans);
		}
		else
		{
			idx=del[i]-1; idx=ins[idx];
			tot--; state=-1;
			x1=cm[idx][0], yy1=cm[idx][1], x2=cm[idx][2], y2=cm[idx][3];
			
			int id=0;
			for(int j=0; j<=2; j+=2) for(int k=1; k<=3; k+=2)
				change_statex(root[id++], cm[idx][j], cm[idx][k]);
		}
	}
	return 0;
}