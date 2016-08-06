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
const int mx = 1e6+10, mod = 1e9+7;

int t, n;
long long ans = 0;
string s[mx]; char in[mx];

unsigned long long prefix[mx], suffix[mx], pw[mx];
unsigned long long magic = 0xabcdef;
int marki[mx]={0}, markg[mx]={0};

unsigned long long getHash(unsigned long long s[], int l, int r)
{
    return s[r + 1] - s[l] * pw[r - l + 1];
}

void suffix_palin(string w, int mark[])
{
	int len = w.size();
	
	prefix[0] = 0;
	suffix[0] = 0;
	rep(j, 0, len-1)
	{
		prefix[j + 1] = prefix[j] * magic + w[j];
		suffix[j + 1] = suffix[j] * magic + w[len - 1 - j];
	}

	for (int j = len - 1; j; -- j)
	{
		if (getHash(prefix, 0, j - 1) ==  getHash(suffix, len - j, len - 1))
			mark[len-j] = 1;
	}
	mark[len]=1;
}

struct trie
{
	trie* p[26];
	int ut, bl;

	trie()
	{
		rep(i, 0, 25)
			p[i] = NULL;
		ut = 0; bl = 0;
	}
} *pr, *sr;

void get(trie* cur, string w)
{
	suffix_palin(w, markg);
	reverse(w.begin(), w.end());
	suffix_palin(w, marki);

	for(int i=-1;;)
	{
		if(cur->p[w[i+1]-'a'] == NULL)
			break;
		cur = cur->p[w[++i]-'a'];

		ans += markg[i+1]*cur->ut;
		if(i == w.size()-1)
		{
			ans += cur->bl;
			break;
		}
	}
	rep(i, 0, w.size())
		markg[i] = 0;
}

void insert(trie *cur, string w)
{
	for(int i=-1;;)
	{
		if(cur->p[w[i+1]-'a'] == NULL)
			cur->p[w[i+1]-'a'] = new trie();
		cur = cur->p[w[++i]-'a'];
		
		if(i == w.size()-1)
		{
			cur->ut += 1;
			break;
		}
		cur->bl += marki[i+1];
	}
	rep(i, 0, w.size())
		marki[i] = 0;
}

int main()
{
	//rf;// wf;

	pw[0] = 1;
	rep(i, 1, mx-1)
		pw[i] = pw[i - 1] * magic;
	
	scanf("%d", &t);
	while(t--)
	{
		pr = new trie();
		sr = new trie();
		ans = 0;

		scanf("%d", &n);
		rep(i, 1, n)
			scanf("%s", in), s[i]=in;

		rep(i, 1, n)
		{
			get(pr, s[i]);
			insert(pr, s[i]);
		}
		for(int i=n; i; --i)
		{
			get(sr, s[i]);
			insert(sr, s[i]);
		}

		printf("%lld\n", ans);
	}
	return 0;
}