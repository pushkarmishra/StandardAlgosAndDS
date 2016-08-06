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
const int mx = 1e7+10, mod = 1e9+7;

struct linked_list
{
	linked_list* next;
	int val;

	linked_list(): next(NULL), val(0) {};
	linked_list(linked_list* put): next(put) {};
	linked_list(linked_list* put, int v)
	{
		next = put; val = v;
	}
};
linked_list* hasher[mx];

int get_hash(int num)
{
	int ret = 0;
	int add = 7, mul = 31;

	while(num > 0)
	{
		int unit_digit = num%10;
		ret = ((ret+unit_digit)*mul + add)%mx;

		num = num/10;
	}

	return ret;
}

linked_list* insert_in_linked_list(linked_list* root, int v)
{
	linked_list *new_root = new linked_list(root, v);
	return new_root;
}

void insert_in_hash(int num)
{
	int hash_index = get_hash(num);
	hasher[hash_index] = insert_in_linked_list(hasher[hash_index], num);
}

bool find_in_hash(int num)
{
	int hash_index = get_hash(num);
	linked_list* cur = hasher[hash_index];

	while(cur!=NULL)
	{
		if(cur->val == num)
			return true;
		cur = cur->next;
	}
	return false;
}

void delete_from_hash(int num)
{
	int hash_index = get_hash(num);
	linked_list* prev = hasher[hash_index], *cur = prev->next;

	if(num == hasher[hash_index]->val)
	{
		hasher[hash_index] = hasher[hash_index]->next;
		return;
	}

	while(cur != NULL)
	{
		if(cur->val == num)
		{
			prev->next = cur->next;
			return;
		}
		cur = cur->next; prev = prev->next;
	}
}

int main()
{
	rf;// wf;
	
	for(int i = 0; i<mx; ++i)
		hasher[i] = NULL;

	int n; scanf("%d", &n);
	while(n--)
	{
		int num;
		scanf("%d", &num);

		bool found = find_in_hash(num);
		if(found) delete_from_hash(num);
		
		insert_in_hash(num);
	}

	return 0;
}