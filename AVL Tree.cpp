#include <cstdio>
#include <algorithm>
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
#define rf freopen("in.in", "r", stdin)
using namespace std;

struct node
{
	node *l, *r;
	int h, val;
	node(int v, int hi, node* lr)
	{
		l=r=lr;
		h=hi, val=v;
	}
};
node *root, *dummy;

node* rotate_right(node* cur)
{
	node* x = cur->l;
	node* y = x->r;
	
	x->r=cur;
	cur->l = y;

	cur->h = max(cur->r->h, cur->l->h) + 1;
	x->h = max(x->l->h, x->r->h) + 1;
	return x;
}
node* rotate_left(node* cur)
{
	node* x = cur->r;
	node* y = x->l;
	
	x->l=cur;
	cur->r = y;

	cur->h = max(cur->r->h, cur->l->h) + 1;
	x->h = max(x->l->h, x->r->h) + 1;
	return x;
}

void insert(node* cur, int valins)
{
	if(cur->val > valins)
	{
		if(cur->l != dummy)
			insert(cur->l, valins);
		else cur->l = new node(valins, 1, dummy);

		cur->h = max(cur->l->h, cur->r->h) + 1;
	}
	else
	{
		if(cur->r != dummy)
			insert(cur->r, valins);
		else cur->r = new node(valins, 1, dummy);

		cur->h = max(cur->l->h, cur->r->h) + 1;
	}

	if(cur->l->h - cur->r->h > 1) cur = rotate_right(cur);
	else if(cur->r->h - cur->l->h > 1) cur = rotate_left(cur);
}

void inorder(node* cur)
{
	if(cur==dummy) return;
	
	inorder(cur->l);
	printf("%d\n", cur->val);
	inorder(cur->r);
}

int main()
{
	rf;// wf;
	dummy = new node(0, 0, NULL);
	root = NULL;

	int q;
	scanf("%d", &q);
	rep(i, 1, q)
	{
		int valins;
		scanf("%d", &valins);

		if(root==NULL)
			root= new node(valins, 1, dummy);
		else insert(root, valins);
	}

	inorder(root);
	printf("\n");
	return 0;
}