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
#define rf freopen("/Users/pushkarmishra/Desktop/in.in", "r", stdin)
#define wf freopen("out.out", "w", stdout)
#define rep(i, s, n) for(int i=int(s); i<=int(n); ++i)
using namespace std;
const int mx = 1e5+10, mod = 1e9+7;

struct Complex
{
	long double re, im;
	
	Complex() {}
	Complex(long double _re, long double _im): re(_re), im(_im) {}
	
	Complex conjugate() const {
		return Complex(re, -im);
	}
	
	long double mod() const {
		return re * re + im * im;
	}
	
	Complex operator+(const Complex &z) const {
		return Complex(re + z.re, im + z.im);
	}
	
	Complex operator-(const Complex &z) const {
		return Complex(re - z.re, im - z.im);
	}
	
	Complex operator*(const Complex &z) const {
		return Complex(re * z.re - im * z.im, re * z.im + im * z.re);
	}
} *a, *b, *c, *ans;

Complex* fft(int n, Complex *pol)
{
	Complex *ret = new Complex[n];
	int s = log2(n);
	
	rep(i, 0, n-1)
	{
		int j=i, k=0;
		rep(it, 1, s)
			k = k*2 + (j&1), j>>=1;

		ret[k] = pol[i];
	}

	rep(i, 1, s)
	{
		int m = 1<<i;
		for(int j=0; j<n; j+=m) rep(k, 0, m/2-1)
		{
			Complex t = Complex(cos((2*M_PI*k)/(1.0*m)), sin((2*M_PI*k)/(1.0*m)));
			Complex u = ret[j+k];
			t = t*ret[j+k+m/2];

			ret[j+k] = u+t;
			ret[j+k+m/2] = u-t;
		}
	}
	return ret;
}

int main()
{
	//rf;// wf;
	
	int n, l;
	scanf("%d", &n);
	l = log2(n+1); l = 1<<(l+1);
	
	a = new Complex[l]; b = new Complex[l];
	rep(i, 0, n-1)
		a[i] = Complex(0, 0),
		scanf("%Lf", &a[i].re);
	
	rep(i, 0, n-1)
		b[i] = Complex(0, 0),
		scanf("%Lf", &b[i].re);
	
	rep(i, n, l-1)
		a[i] = b[i] = Complex(0, 0);
	
	Complex *get_a = fft(l, a);
	Complex *get_b = fft(l, b);
	
	c = new Complex[l];
	rep(i, 0, l-1)
		c[i] = get_a[i]*get_b[i];

	ans = fft(l, c);
	reverse(ans+1, ans+l);
	rep(i, 0, 2*n-2)
		printf("%Lf ", ans[i].re/(1.0*l));
	printf("\n");
	
	return 0;
}