#include <bits/stdc++.h>
#define ld long double
#define ll long long
using namespace std;

using cd = complex< double >;
const double PI = acos(-1);

#define INF 0x7fffffffffffffff
#define OO 0x7fffffff
#define SQ(a) (a)*(a)
#define EPS 1e-10

typedef pair<int , int> ii;
typedef pair<ll , ll> pll;
typedef vector< ii > vii;
typedef vector< int > vi;
#define PB push_back
#define MP make_pair
#define S second
#define F first

/// ======================================================================= ///

const int MOD = 1e9 + 7;

template<typename T>T _gcd(T __a , T __b){ return !__b ? __a : _gcd( __b , __a % __b); }
template<typename T>T _lcm(T __a , T __b){ return abs( __a * ( __b /_gcd(__a,__b) ) ); }

int obc(int x) { return __builtin_popcount(x); }  // one bits counter
int zlc(int x) { return __builtin_clz(x); }  // Zeros bits counter from last
int zfc(int x) { return __builtin_ctz(x); }  // Zeros bits counter from first

template<typename T> T _powMOD(T __n , T __p){
    if( __p == 0 ) return 1 % MOD;
    if( __p  % 2 ) return ((__n % MOD) * _powMOD( __n ,__p - 1) ) %  MOD;
    auto R = _powMOD( __n , __p >> 1) % MOD;
    return (R * R) % MOD;
}

template<typename T> T _pow(T __n , T __p){
    if( __p == 0 ) return 1;
    if( __p  & 1 ) return __n * _pow( __n ,__p - 1);
    auto R = _pow( __n , __p >> 1);
    return R * R;
}

/// ---- \Extended \Euclid ---- ///
//  F = GCD , S.F = X , S.S = Y , EQU = aX + bY = GCD(a ,b)
pair<ll , pll> ExtdEcld(ll a ,ll b){

    if( !b ) return pair<ll , pll>(a ,pll(1ll ,0ll));
    pair<ll , pll> Sol = ExtdEcld(b ,a % b);
    return pair<ll , pll>(Sol.F ,pll(Sol.S.S ,Sol.S.F - (a / b) * Sol.S.S));
}

vector< int > primeFactors(ll n ,vector< int > &Primes){
    int idx = 0;
    ll Pr = Primes[idx];
    vector< int > PrFactors;

    while( 1ll * Pr * Pr <= n ) {
        if( n % Pr == 0 ) {
            PrFactors.push_back(Pr);
            while( n % Pr == 0 ) n /= Pr;
        }
        Pr = Primes[++idx];
    } if( n != 1 ) PrFactors.push_back(n);

    return PrFactors;
}

vector< int > PrimeTo1e7(ll n = 1e7 + 7e2 + 1){
    vector< int >  Res;
    vector< bool > Pr(n ,true);

    Pr[0] = Pr[1] = false;
    for(ll i = 2ll ; i < n ; i++) if( Pr[i] ){
        for(ll j = i * i ; j < n ; j += i )
            Pr[j] = false;
        Res.push_back((int)i);
    }
    return Res;
}

inline bool isPrime(ll n ,vector< bool > &Pr ,vector< int > &Primes){
    /// --- \VIP\NOTE --- ///
        // --- only work for 1e14 + 14e9 --- //

    ll SieveSize = 1e7 + 7e2;
    if( n < SieveSize ) return Pr[n];

    for(int P : Primes)
        if( n % P == 0 )
            return false;
    return true;
}

/// --- Fast Fourier Transform --- ///
void fft(vector< cd > &a, bool invert) {
    int n = (int)a.size();
    if( n == 1 ) return;

    vector< cd > a0(n / 2), a1(n / 2);
    for(int i = 0 ; 2 * i < n ; i++) {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for(int i = 0 ; 2 * i < n ; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if( invert ) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}

/// --- Multiplying Two Polynomials Via Fast Fourier Transform --- ///
vector< int > fftMul(vector< int > const& a, vector< int > const& b ,int N ,int M) {
    vector< cd > fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while(n < N + M)
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for(int i = 0 ; i < n ; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vector< int > result(n);
    for(int i = 0 ; i < n ; i++)
        result[i] = round((int)fa[i].real());
    return result;
}

/// --- Find sqrt Of lvl N --- ///
ld SqrtN(ld x ,ld n){
    bool founded = false;
    long double Res = 1.0;

    ld L = 0.0 ,R = x;
    while( abs(R - L) >= EPS && !founded ){
        ld Mid = (L + R) / 2.0;
        ld Pow = pow(Mid , n);

             if( Pow > x ) Res = R = Mid;
        else if( Pow < x ) Res = L = Mid;
        else Res = Mid ,founded = true;
    }

    return Res;
}

ll SAPS(ll n ,ll q ,ll a1){
    /// --- Sum Of Arithmetic Progression Series --- ///
    /// --- n = Number Of Elements --- ///
    /// --- d = s[i + 1] - s[i] --- ///

    ll Sn = (n / 2) * (2 * a1 + (n - 1) * q);
    return Sn;
}

ll SGPS(ll n ,ll r ,ll a1){
    /// --- Sum Of Geometric Progression Series --- ///
    /// --- n = Number Of Elements --- ///
    /// --- r = s[i + 1] / s[i] --- ///

    ll Sn = a1 * ( (1 - _pow(r ,n)) / (1 - r) );
    return Sn;
}

ll Inv(ll b){
    return _powMOD(b ,MOD - 2ll);
}


/*****************************************\
| (a + b) % m = (a%m + b%m)%m             |
| (a * b) % m = (a%m * b%m)%m             |
| (a - b) % m = (a%m - b%m + m)%m         |
| (a / b) % m = (a%m * power(b, m-2)%m)%m |
\*****************************************/
