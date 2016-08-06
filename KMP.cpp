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

int longest_pref_suf[mx];
void create_longest_pref_suf(string pattern)
{
	longest_pref_suf[0] = 0;
	for(int i = 1; i < pattern.size(); ++i)
	{
		int prev = longest_pref_suf[i-1];
		
		longest_pref_suf[i] = (pattern[prev] == pattern[i])? prev+1: 0;
	}
}

int KMP(string text, string pattern)
{
	int count = 0;
	int i = 0, j = 0;

	while(i<text.size())
	{
		int prev_i = i;
		while(i<text.size() and j<pattern.size() and text[i] == pattern[j])
			i++, j++;
		
		if(j == pattern.size())
			count++;
		
		j = j? longest_pref_suf[j-1]: 0;
		i += (prev_i == i);
	}

	return count;
}

int main()
{
	rf;// wf;
	
	string pattern, text;
	memset(longest_pref_suf, 0, sizeof longest_pref_suf);

	cin >> text >> pattern;
	create_longest_pref_suf(pattern);

	cout << KMP(text, pattern) << endl;
	return 0;
}