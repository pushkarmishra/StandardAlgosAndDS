#include <cstdio>
#include <ctime>
#include <cstdlib>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
using namespace std;
const int mx=1e5+10;

struct node
{
	int pr, sz, val;
	node* l, *r;

	node(node* put, int ins, int s)
	{
		l=r=put;
		val=ins; sz=s;
		pr = rand()%int(1e9) + 1;
	}

}; node* dummy, *root;

node* rotate_right(node* cur)
{
	node *x = cur->l, *y = x->r;
	x->r=cur, cur->l = y;
	
	cur->sz = cur->l->sz + cur->r->sz + 1;
	x->sz = x->l->sz + x->r->sz + 1;
	
	return x;
}
node* rotate_left(node* cur)
{
	node *x = cur->r, *y = x->l;
	x->l=cur, cur->r = y;
	
	cur->sz = cur->l->sz + cur->r->sz + 1;
	x->sz = x->l->sz + x->r->sz + 1;
	
	return x;
}

void insert(node* &cur, int vins)
{
	if(cur == dummy)
		return void(cur = new node(dummy, vins, 1));

	(cur->val >= vins)? insert(cur->l, vins): insert(cur->r, vins);
	cur->sz+=1;

	if(cur->l->pr < cur->pr)
		cur = rotate_right(cur);
	else if(cur->r->pr < cur->pr)
		cur = rotate_left(cur);
}

int main()
{
	rf;// wf;
	srand(time(NULL));

	dummy = new node(NULL, 0, 0); dummy->pr=-mx;
	root = dummy;

	int n;
	scanf("%d", &n);
	rep(i, 1, n)
	{
		int vins;
		scanf("%d", &vins);
		insert(root, vins);
	}
	return 0;
}