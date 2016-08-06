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
	if(n == 1)
	{
		Complex *ret = new Complex[1];
		ret[0] = pol[0];
		return ret;
	}
	
	Complex *even, *odd;
	even = new Complex[n/2];
	odd = new Complex[n/2];
	
	for(int i=0, j=0; i<n; i+=2)
		even[j++] = pol[i];
	for(int i=1, j=0; i<n; i+=2)
		odd[j++] = pol[i];
	
	Complex *get_even = fft(n/2, even);
	Complex *get_odd = fft(n/2, odd);
	
	Complex *ret = new Complex[n];
	rep(j, 0, n/2-1)
	{
		Complex t = Complex(cos((2*M_PI*j)/(1.0*n)), sin((2*M_PI*j)/(1.0*n)));
		ret[j] = get_even[j] + t*get_odd[j];
		ret[j+n/2] = get_even[j] - t*get_odd[j];
	}
						   
	return ret;
}

int main()
{
	rf;// wf;
	
	int n, l;
	scanf("%d", &n);
	l = log2(n+1); l = 1<<(l+1);
	
	//Takes in two polynomials and pads extra zero-coefficient terms to form polynomial of degree
	//l = 2^k.
	a = new Complex[l]; b = new Complex[l];
	rep(i, 0, n-1)
		a[i] = Complex(0, 0),
		scanf("%Lf", &a[i].re);
	rep(i, 0, n-1)
		b[i] = Complex(0, 0),
		scanf("%Lf", &b[i].re);
	rep(i, n, l-1)
		a[i] = b[i] = Complex(0, 0);
	
	//Evaluates the two polynomials at l roots of unity.
	Complex *get_a = fft(l, a);
	Complex *get_b = fft(l, b);
	
	//Multiplies the two polynomials A(x) and B(x) to get value of C(x) at the l roots of unity.
	c = new Complex[l];
	rep(i, 0, l-1)
		c[i] = get_a[i]*get_b[i];

	//Performs inverse DFT by taking an l-degree polynomial with coefficients as the value
	//of C(x) at l roots of unity. The original polynomial C(x) is obtained with coefficients in
	//reverse order.
	ans = fft(l, c);
	reverse(ans+1, ans+l);
	rep(i, 0, 2*n-2)
		printf("%Lf ", ans[i].re/(1.0*l));
	printf("\n");
	
	return 0;
}