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
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;
#define ll long long

ll v;
int q, ch, qx1, qy1, qx2, qy2, mx, my, chk;

struct node
{
	node *lo, *ro, *li, *ri;
	ll sum;
	node(node* put)
	{
		sum = 0;
		lo=ro=ri=li=put;
	}
};
node *root, *dummy;

void upc(node* &cur, int x, int y, node* l, node* r)
{
	if(y<qy1 or qy2<x) return;
	if(cur == dummy) cur=new node(dummy);
	
	l=(l==NULL)? dummy:l; r=(r==NULL)? dummy:r;
	cur->lo=(l!=dummy)? l:dummy; cur->ro=(r!=dummy)? r:dummy;

	if(qy1<=x and y<=qy2)
	{
		cur->sum=(chk)? v: (cur->lo->sum + cur->ro->sum);
		return;
	}

	int m=(x+y)>>1;
	upc(cur->li, x, m, l->li, r->li); upc(cur->ri, m+1, y, l->ri, r->ri);

	cur->sum = (cur->li->sum + cur->ri->sum);
}
void upr(node* &cur, int x, int y)
{
	if(y<qx1 or qx2<x) return;
	if(cur == dummy) cur=new node(dummy);

	if(qx1<=x and y<=qx2)
	{
		chk=1; upc(cur, 1, my, cur->lo, cur->ro);
		return;
	}

	int m=(x+y)>>1;
	upr(cur->lo, x, m); upr(cur->ro, m+1, y);

	chk=0; upc(cur, 1, my, cur->lo, cur->ro);
}

ll quc(node* &cur, int x, int y)
{
	if(y<qy1 or qy2<x or cur==dummy) return 0;
	if(qy1<=x and y<=qy2)
		return cur->sum;
	
	int m=(x+y)>>1;
	return (quc(cur->li, x, m) + quc(cur->ri, m+1, y));
}
ll qur(node* &cur, int x, int y)
{
	if(y<qx1 || qx2<x || cur==dummy) return 0;
	if(qx1<=x && y<=qx2)
		return quc(cur, 1, my);
	
	int m=(x+y)>>1;
	return (qur(cur->lo, x, m) + qur(cur->ro, m+1, y));
}

int main()
{
	rf;// wf;
	scanf("%d %d %d", &mx, &my, &q);
	dummy = new node(NULL);
	root = new node(dummy);

	while(q--)
	{
		scanf("%d %d %d", &ch, &qx1, &qy1); qx1++; qy1++;
		if(ch==1)
		{
			scanf("%lld", &v); qx2=qx1, qy2=qy1;
			upr(root, 1, mx);
		}
		else
		{
			scanf("%d %d", &qx2, &qy2); qx2++; qy2++;
			printf("%lld\n", qur(root, 1, mx));
		}
	}
	return 0;
}