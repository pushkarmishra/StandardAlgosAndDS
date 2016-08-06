#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <queue>
#include <stack>
#include <map>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;

#define FOR(i, n) for(int i=0;i<int(n);i++)
#define FOR1(i, n) for(int i=1;i<=int(n);i++)
#define FORA(i, a, n) for(int i=a;i<int(n);i++)
#define FORR(i, n) for(int i=n-1;i>=0;i--)
#define foreach(it, c) for(typeof(c.begin()) it = c.begin(); it != c.end(); it++)
#define all(c) c.begin(), c.end()
#define clear(c,v) memset(c,v,sizeof(c))

typedef long long int lli;
typedef pair<int,int> ii;

// interval updates, interval queries (lazy propagation)
const int SN = 256;  // must be a power of 2

struct SegmentTree {

    // T[x] is the (properly updated) sum of indices represented by node x
    // U[x] is pending increment for _each_ node in the subtree rooted at x 
    int T[2*SN], U[2*SN];

    SegmentTree() { clear(T,0), clear(U,0); }

    // increment every index in [ia,ib) by incr 
    // the current node is x which represents the interval [a,b)
    void update(int incr, int ia, int ib, int x = 1, int a = 0, int b = SN) { // [a,b)
        ia = max(ia,a), ib = min(ib,b); // intersect [ia,ib) with [a,b)
        if(ia >= ib) return;            // [ia,ib) is empty 
        if(ia == a and ib == b) {       // We push the increment to 'pending increments'
            U[x] += incr;               // And stop recursing
            return; 
        }
        T[x] += incr * (ib - ia);          // Update the current node
        update(incr,ia,ib,2*x,a,(a+b)/2);  // And push the increment to its children
        update(incr,ia,ib,2*x+1,(a+b)/2, b);
    }

    int query(int ia, int ib, int x = 1, int a = 0, int b = SN) {
        ia = max(ia,a), ib = min(ib,b); //  intersect [ia,ib) with [a,b)
        if(ia >= ib) return 0;          // [ia,ib) is empty 
        if(ia == a and ib == b) 
            return U[x]*(b - a) + T[x];
        
        T[x] += (b - a) * U[x];           // Carry out the pending increments
        U[2*x] += U[x], U[2*x+1] += U[x]; // Push to the childrens' pending increments
        U[x] = 0;

        return query(ia,ib,2*x,a,(a+b)/2) + query(ia,ib,2*x+1,(a+b)/2,b);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    
    SegmentTree T;
    int n = SN;
    srand(time(0));
    int Q = 1000000;

    vector<int> v(n);

    char c;
    int a,b,x;
    // while(cin >> c >> a >> b){
    //     if(c == 'u'){
    //         cin >> x;
    //         T.update(x,a,b);
    //         FORA(i,a,b) v[i] += x;
    //     }
    //     else {
    //         int sum = 0;
    //         FORA(i,a,b) sum += v[i];

    //         cout << T.query(a,b) << ' ' << sum << endl;
    //     }
    //     FOR(i,n) cout << v[i] << ' '; cout << endl;
    // }
    // return 0;

    while(Q--){
        a = (rand() % n) + 1, b = (rand() % n) + 1;
        if(a > b) swap(a,b);

        x = rand() % (n*n);
        printf("update : [%d,%d) +%d\n", a,b,x);
        T.update(x,a,b);
        FORA(i,a,b) v[i] += x;

        a = (rand() % n) + 1, b = (rand() % n) + 1;
        if(a > b) swap(a,b);
        printf("query : [%d,%d) \n",a,b);

        int sum = 0;
        FORA(i,a,b) sum += v[i];

        FOR1(i,n) cout << v[i] << ' '; cout << endl;
        cout << T.query(a,b) << ' ' << sum << endl;

        assert(T.query(a,b) == sum);
    }
    
    return 0;
}
