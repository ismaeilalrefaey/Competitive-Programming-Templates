#include <bits/stdc++.h>
using namespace std;

#define FastIO cin.tie(0);cout.tie(0);ios::sync_with_stdio(0);
#define LSOne(a) ( (a) & -(a) )
#define SQ(a) (a)*(a)
#define INF  ll(4e18)
#define OO   int(1e9)
#define EPS      1e-9
#define PB  push_back
#define MP  make_pair
#define lf   (p << 1)
#define rg   (lf | 1)
#define S      second
#define F       first

typedef long long       ll;
typedef long double     ld;
typedef pair<int , int> ii;
typedef pair<int , ii>  iii;
typedef pair<ll , ll>   pll;
typedef pair<ll , pll>  plll;
typedef vector< int >   vi;
typedef vector< ll >    vl;
typedef vector< ii >    vii;
typedef vector< pll >   vll;
typedef vector< iii >   viii;
typedef vector< plll >  vlll;

// "%[^\n]s"

// ------------------------ //

/// --- PBDS Librarie --- //
#include <bits/extc++.h>

using namespace __gnu_pbds;
typedef tree<int ,null_type ,less< int > ,rb_tree_tag ,
        tree_order_statistics_node_update> ost;
/// ost a; a.insert(x); a.find_by_order(kth); a.order_of_key(num);

// ------------------------------------------------------- //

const int dx[] = {1 ,0 ,-1 , 0 ,1 ,-1 ,1 ,-1};
const int dy[] = {0 ,1 , 0 ,-1 ,1 ,-1 ,-1 ,1};

const long double PI = 3.141592653589793238;
const long long MOD = 1e9 + 7;


// Usage: priority_queue< type , vector< type > , cmp > pq;
struct cmp
{
    bool operator()(const int& a, const int& b)
    {
        // if you put return a < b; it will be maxHeep
        // if you put return a > b; it will be minHeep

        return a > b;
    }
};

// ------------------------------------------------------- //
// --------------------- BitMask ------------------------- //

int obc(int x)
{
    /// --- int One bits counter --- ///
    return __builtin_popcount(x);
}
int zlc(int x)
{
    /// --- int Zeros bits counter from last --- ///
    return __builtin_clz(x);
}
int zfc(int x)
{
    /// --- int Zeros bits counter from first --- ///
    return __builtin_ctz(x);
}
int obc(ll x)
{
    /// --- long One bits counter --- ///
    return __builtin_popcountl(x);
}
int zlc(ll x)
{
    /// --- long Zeros bits counter from last --- ///
    return __builtin_clzl(x);
}
int zfc(ll x)
{
    /// --- long Zeros bits counter from first --- ///
    return __builtin_ctzl(x);
}

// ------------------------ //

// ---------------------------------------------------- //
// --------------------- Math ------------------------- //

vl primes;
ll sieve_size;
bitset< 10000011 > bs;

void sieve(ll upperbound)
{
    // always relax and call it to 1e7 ..
    // sieve(10000010);

    sieve_size = upperbound + 1;

    bs.set();
    bs[0] = bs[1] = false;
    for(int64_t i = 2ll ; i < sieve_size ; ++i) if( bs[i] )
    {
        for(int64_t j = 1ll * i * i ; j < sieve_size ; j += i) bs[j] = false;
        primes.push_back(i);
    }
}

vl primeFactors(ll num)
{
    ll x = num;
    vl factors;

    for(int i = 0 ; i < (int)primes.size() && 1ll * primes[i] * primes[i] <= x ; i++)
    {
        if( x % primes[i] == 0 )
        {
            ll cnt = 0;
            while( x % primes[i] == 0 )
            {
                cnt += 1;
                x /= primes[i];
                factors.push_back(primes[i]);
            }
        }
    }
    if( x != 1 )factors.push_back(x);

    return factors;
}

bool isPrime(ll num){
    /// --- \VIP\NOTE --- ///
        // --- only work for 1e14 + 14e9 --- //

    if( num < sieve_size ) return bs[num];

    for(int i = 0 ; i < (int)primes.size() && 1ll * primes[i] * primes[i] <= num ; i++)
        if( num % primes[i] == 0 )
            return false;

    return true;
}

ll numDiffPF[2002002];
void modified_sieve(ll upperbound)
{
    for(int i = 2 ; i <= upperbound ; i++)
        if( numDiffPF[i] == 0 )
            for(int j = i ; j <= upperbound ; j += i)
                numDiffPF[j] += 1;
}

/*
 *  num of divisors = π (cnt[ primes[i] ] + 1);
 *  sum of divisors = π ( (primes[i]^(cnt[ primes[i] ]+1) - 1) / (primes[i] - 1) )
 *  num of coPrimes under n with n: ans -= (ans / primes[i]) ; ans = n (first)
 *
 * --- Legendre's Formula ---*
 *
 * N! has P ^ X (P is Prime number)
 * The formula get the X that exist in N!
 *
 * X = Σi (N / P^i)
 *
 * Vp(P ,N) = X;
 * Vp(P ,N) = (N - Sp(P ,N)) / (P - 1)
 *      :Where:
 *           Sp(P ,N) = sum of digits of n in P-Base-Number
 */

ll Vp(ll P ,ll N)
{
    ll X = 0;

    for(ll i = P ; i <= N ; i *= P)
    {
        ll div = N / i;
        X += div;
    }

    return X;
}

// ------------------------ //

ll gcd(ll a ,ll b)
{
    return !b ? a : gcd(b ,a % b);
}
ll lcm(ll a ,ll b)
{
    return a / gcd(a ,b) * b;
}

/// --- [ax + by = gcd(a,b)] => get(x ,y) --- ///
ll extEuclid(ll a, ll b, ll &x, ll &y)
{
    // x = prevY
    // y = prevX - a / b * prevY

    ll xx = y = 0;
    ll yy = x = 1;

    while( b )
    {
        ll q = a / b;
        ll t = b;   b = a % b;   a = t;
        t = xx; xx = x - q * xx; x = t;
        t = yy; yy = y - q * yy; y = t;
    }

    return a; /// -- Gcd -- ///
}

/********************************
* X0 ,Y0 are one solution pair. *
* there are OO solutions        *
*                               *
* Xn = X0 + b/d * n             *
* Yn = Y0 - a/d * n             *
*                               *
* where:                        *
*       d = gcd(a,b)            *
*       n is integer            *
*                               *
* to get positive answers only: *
*       for loop the n from     *
*           -x0 * d / b         *
*       to  +y0 * d / a         *
********************************/

ll modInverse(ll b ,ll Mod)
{
    // work if gcd(b ,Mod) = 1 only
    ll x ,y;

    // can't get (1/b)%Mod
    if( extEuclid(b ,Mod ,x ,y) != 1 ) return -1;

    // sure that x > 0
    return (x % Mod + Mod) % Mod;
}

// ------------------------ //

ll _pow(ll n ,ll p)
{
    if( !p ) return 1;

    if( p & 1 ) return n * _pow(n ,p - 1);

    return _pow(n * n ,p >> 1);
}

ll _powMod(ll n ,ll p ,ll MOD)
{
    if( p == 0 ) return 1;

    if( p  & 1 ) return n * _powMod(n ,p - 1 ,MOD) % MOD;

    return _powMod(n * n % MOD ,p >> 1 ,MOD) % MOD;
}

// ------------------------- //

ll getNum(string s)
{
    stringstream st; st << s;

    ll num; st >> num;

    return num;
}

string getString(ll n)
{
    stringstream st; st << n;

    string s; st >> s;

    return s;
}

// ------------------------ //

ll SAPS(ll numOfElement ,ll diff ,ll firstElement)
{
    /// --- Sum Of Arithmetic Progression Series --- ///
    /// --- diff = s[i + 1] - s[i] --- ///

    return numOfElement * firstElement + numOfElement * (numOfElement - 1ll) * diff / 2ll;
}

ll SGPS(ll numOfElement ,ll diff ,ll firstElement)
{
    /// --- Sum Of Geometric Progression Series --- ///
    /// --- firstElement = s[i + 1] / s[i] --- ///

    return firstElement * ( (1 - _pow(diff ,numOfElement)) / (1 - diff) );
}

// ------------------------ //

ll fact[2e6 + 1];

ll C(ll n ,ll k)
{
    return
    // fact[n] / (fact[k] * fact[n - k]);
    // (((fact[n] * modInverse(fact[k] ,MOD)) % MOD) * modInverse(fact[n - k])) % MOD;
}

// ------------------------------------------------------ //
// --------------------- Matrix ------------------------- //

typedef long long ll;
typedef vector< ll > Row;
typedef vector< Row > Matrix;

/// --- Get Zero Matrix --- ///
Matrix zeroMat(int n ,int m)
{
    return Matrix(n ,Row(m ,0));
}

/// --- Get Identity Matrix --- ///
Matrix identityMat(int n)
{
    Matrix identity = zeroMat(n ,n);

    for(int i = 0 ; i < n ; i++) identity[i][i] = 1;

    return identity;
}

/// --- Sum Of Diagonal Matrix --- ///
ll matTrace(Matrix a)
{
    ll res = 0;

    for(int i = 0 ; i < (int)a.size() ; i++) res += a[i][i];

    return res;
}

/// --- Sum Two Matrix  --- ///
Matrix addIdentity(Matrix a)
{
    Matrix res = a;

    for(int i = 0 ; i < (int)res.size() ; i++) res[i][i] += 1;

    return res;
}

/// --- Sum Two Matrix  --- ///
Matrix addMat(Matrix a ,Matrix b)
{
    Matrix res = zeroMat(a.size() ,b[0].size());

    for(int i = 0 ; i < (int)a.size() ; i++)
        for(int j = 0 ; j < (int)a[0].size() ; j++)
            res[i][j] = a[i][j] + b[i][j];

    return res;
}

/// --- Multiplication Two Matrix  --- ///
Matrix multMat(Matrix a ,Matrix b)
{
    Matrix res = zeroMat(a.size() ,b[0].size());

    for(int i = 0 ; i < (int)a.size() ; i++)
        for(int k = 0 ; k < (int)a[0].size() ; k++)
            if( a[i][k] != 0 ) /// --- Optimization --- ///
                for(int j = 0 ; j < (int)b[0].size() ; j++)
                    res[i][j] += a[i][k] * b[k][j];

    return res;
}

/// --- Multiplication Two Matrix With MOD --- ///
Matrix multModMat(Matrix a ,Matrix b)
{
    Matrix res = zeroMat(a.size() ,b[0].size());

    for(int i = 0 ; i < (int)a.size() ; i++)
        for(int k = 0 ; k < (int)a[0].size() ; k++)
            if( a[i][k] != 0 ) /// --- Optimization --- ///
                for(int j = 0 ; j < (int)b[0].size() ; j++){
                    res[i][j] += (a[i][k] % MOD * b[k][j] % MOD) % MOD;
                    res[i][j] %= MOD; }

    return res;
}

/// --- Power(Matrix ,k) --- ///
Matrix powMat(Matrix a ,ll k)
{
    if( k == 0 ) return identityMat(a.size());

    if( k  & 1 ) return multMat(a ,powMat(a ,k - 1));

    return powMat(multMat(a ,a) ,k >> 1);
}

/// --- Power(Matrix ,k) With MOD --- ///
Matrix powModMat(Matrix a ,ll k)
{
    if( k == 0 ) return identityMat(a.size());

    if( k  & 1 ) return multModMat(a ,powModMat(a ,k - 1));

    return powModMat(multModMat(a ,a) ,k >> 1);
}

/// --- a^1 + a^2 + ... + a^k --- ///
Matrix sumPows(Matrix a ,ll k)
{
    if( k == 0 ) return zeroMat(a.size() ,a.size());

    if( k  & 1 ) return multMat(a ,addIdentity(sumPows(a ,k - 1)));

    return multMat(sumPows(a ,k / 2) ,addIdentity( powMat(a ,k / 2) ));
}

// --------------------------------------------------- //
// --------------------- FFT ------------------------- //

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

// ----------------------------------------------------------- //
// --------------------- SparseTable ------------------------- //

class SparseTable
{
    private:
        vector< vector< long long > > SpT;    // Sparse Table Matrix

        vector< long long > A;     // main array
        vector< long long > P;     // power of 2
        vector< long long > L;     // logtm of 2

        int size;    // size of array
        int logS;     // log2 of size

        void init()
        {
            P.assign(logS + 1 ,0ll);
            L.assign((1ll << logS) + 1 ,0ll);

            for(int i = 0 ; i <= logS ; i++)
            {
                P[i] = (1ll << i);
                L[(1ll << i)] = i;
            }

            for(int i = 2 ; i <= P[logS] ; i++)
                if( L[i] == 0ll )
                    L[i] = L[i - 1];
        }

        void BLD()
        {
            // build function able to change according to needed SpT
            SpT.assign(L[size] + 1 ,vector< long long >(size));

            for(int i = 0 ; i < size ; i++) SpT[0][i] = i;

            for(int j = 1 ; P[j] <= size ; j++)
            {
                for(int i = 0 ; i + P[j] - 1 < size ; i++)
                {
                    long long x = SpT[j - 1][i];
                    long long y = SpT[j - 1][i + P[j - 1]];

                    if( A[x] < A[y] ) {
                        SpT[j][i] = x;
                    } else {
                        SpT[j][i] = y;
                    }
                }
            }

        }

    public:
        SparseTable(vector< long long > &initA)
        {
            this -> A      = initA;
            this -> size = (int)initA.size();
            this -> logS = (int)log2(size)+1;

            init(); // init vectors P & L
            BLD();  // Building the SpT;
        }

        long long QRY(int left ,int right)
        {
            // return the idx in the orginal array A
            long long k = L[right - left + 1];

            long long x = SpT[k][left];
            long long y = SpT[k][right - P[k] + 1];

            if( A[x] < A[y] ) {
                return x;
            }

            return y;
        }
};

// --------------------------------------------------- //
// --------------------- LCA ------------------------- //

class LcaSpT
{
    private:
        vector< vector< pair<int , int> > > SpT;    // Sparse Table Matrix

        vector< int > order;     // dfs order
        vector< int > depth;     // vrx depth

        vector< long long > P;     // power of 2
        vector< long long > L;     // logtm of 2

        int size;    // size of array
        int logS;     // log2 of size

        void init()
        {
            P.assign(logS + 1 ,0ll);
            L.assign((1ll << logS) + 1 ,0ll);

            for(int i = 0 ; i <= logS ; i++)
            {
                P[i] = (1ll << i);
                L[(1ll << i)] = i;
            }

            for(int i = 2 ; i <= P[logS] ; i++)
                if( L[i] == 0ll )
                    L[i] = L[i - 1];
        }

        void BLD()
        {
            // build function able to change according to needed SpT
            SpT.assign(L[size] + 1 ,vector< pair<int , int> >(size));

            for(int i = 0 ; i < size ; i++) SpT[0][i] = make_pair(order[i] ,depth[i]);

            for(int j = 1 ; P[j] <= size ; j++)
            {
                for(int i = 0 ; i + P[j] - 1 < size ; i++)
                {
                    pair<int , int> x = SpT[j - 1][i];
                    pair<int , int> y = SpT[j - 1][i + P[j - 1]];

                    if( x.second < y.second ) {
                        SpT[j][i] = x;
                    } else {
                        SpT[j][i] = y;
                    }
                }
            }
        }

    public:
        LcaSpT(vector< int > &order ,vector< int > &depth)
        {
            this -> order = order;
            this -> depth = depth;

            this -> size = (int)order.size();
            this -> logS = log2(size) + 1;

            init(); // init vectors P & L
            BLD();  // Building the SpT;
        }

        int QRY(int left ,int right)
        {
            /// --- {main} SpT.QRT(idx[u] ,idx[v]) && BE SURE: idx[v] >= idx[u] --- ///

            long long k = L[right - left + 1];

            pair<int , int> x = SpT[k][left];
            pair<int , int> y = SpT[k][right - P[k] + 1];

            pair<int , int> lca = x.second < y.second ? x : y;
            return lca.first;
        }
};

vector< int > depth;
vector< int > order;
vector< int > idx;

void init()
{
    order.clear();
    depth.clear();
    idx.resize(n);
}

void DFS(int u ,int p ,int h)
{
    idx[u] = (int)order.size();
    order.push_back(u);
    depth.push_back(h);

    for(auto v : al[u]) if( v != p )
    {
        DFS(v ,u ,h + 1);
        order.push_back(u);
        depth.push_back(h);
    }
}

// ----------------------------------------------------------- //
// --------------------- FenwickTree ------------------------- //

class FenTree
{
    /// --- Note: Every Thing Is long long Here --- ///
    private:
        vector< long long > ft;

    public:
        FenTree(int m)
        {
            ft.assign(m + 1 ,0ll);
        }

        FenTree(const vector< long long > &f)
        {
            // build FenTree from a cnt array
            BLD(f);
        }

        FenTree(const vector< long long > &a ,int m)
        {
            // make a cnt array then build FenTree from the cnt array
            vector< long long > f(m + 1 ,0ll);
            for(auto i : a) f[i] += 1;
            BLD(f);
        }

        void BLD(const vector< long long > &f)
        {
            // build FenTree from a cnt array
            int m = (int)f.size() - 1;  // f[0] = 0;

            ft.assign(m + 1 ,0ll);
            for(int i = 1 ; i <= m ; i++)
            {
                ft[i] += f[i];
                if( i + LSOne(i) <= m ){
                    ft[i + LSOne(i)] += ft[i];
                }
            }
        }

        ll QRY(int j)
        {
            ll sum = 0;
            while(j)
            {
                sum += ft[j];
                j -= LSOne(j);
            }

            return sum;
        }

        ll QRY(int i ,int j)
        {
            // (inc/exc)lusion
            return QRY(j) - QRY(i - 1);
        }

        void UPD(int i ,ll v)
        {
            while(i < (int)ft.size())
            {
                ft[i] += v;
                i += LSOne(i);
            }
        }

        int select1(int k)
        {
            // kth element in log2(N)
            int p = 1 ,i = 0;
            while( p * 2 < (int)ft.size() ) p *= 2;

            while( p )
            {
                if( i + p < (int)ft.size() )
                {
                    if( k > ft[i + p] )
                    {
                        k -= ft[i + p];
                        i += p;
                    }
                }

                p /= 2;
            }

            return i + 1;
        }

        int select2(int k)
        {
            // kth element in log2(N) ^ 2
            int loop = 23;
            int L = 1 ,R = (int)ft.size() - 1;

            while( loop -- )
            {
                int Mid = (L + R) >> 1;
                (QRY(Mid) >= k) ? R = Mid
                                   : L = Mid;
            }

            return R;
        }
};

/// --- Range Update Point Query --- ///
class RUPQ
{
    private:
        FenTree ft;

    public:
        RUPQ(int m) : ft(FenTree(m)) {}

        void rangeUPD(int i ,int j ,ll v)
        {
            ft.UPD(  i   ,+v);
            ft.UPD(j + 1 ,-v);
        }

        ll pointQRY(int i)
        {
            return ft.QRY(i);
        }
};

/// --- Range Update Range Query --- ///
class RURQ
{
    private:
        FenTree purq;
        RUPQ rupq;

    public:
        RURQ(int m) :purq(FenTree(m)) ,rupq(RUPQ(m)){}

        void rangeUPD(int i ,int j ,ll v)
        {
            rupq.rangeUPD(i ,j ,v);
            purq.UPD(  i   ,+v * (i - 1));
            purq.UPD(j + 1 ,-v * j);
        }

        ll QRY(int j)
        {
            return rupq.pointQRY(j) * j - purq.QRY(j);
        }

        ll QRY(int i ,int j)
        {
            return QRY(j) - QRY(i - 1);
        }
};

// --------------------------------------------------- //
// --------------------- DSU ------------------------- //

class UnionFind
{
    private:
        int numSet;
        vector< int > p;
        vector< int > rank;
        vector< int > setSize;
/*
 * You Can Make Any vector And Store Information Of
 * Sets On The Root Of Set "like setSize above"
 */

    public:
        UnionFind(int _N)
        {
            numSet = _N;
            rank.assign(_N ,0);
            setSize.assign(_N ,1);
            p.resize(_N); for(int i = 0 ; i < _N ; ++i) p[i] = i;
        }

        int numDisjointSets()
        {
            return numSet;
        }

        int sizeOfSet(int i)
        {
            return setSize[ findSet(i) ];
        }

        int findSet(int i)
        {
            // you can update some thing here
            // 1- get parent in variable
            // 2- update what you need
            // 3- assign the parent to the node
            return (p[i] == i) ? i : (p[i] = findSet(p[i]));
        }

        bool isSameSet(int i ,int j)
        {
            return findSet(i) == findSet(j);
        }

        void unionSet(int i ,int j)
        {
            if( isSameSet(i ,j) ) return;

            int x = findSet(i);
            int y = findSet(j);

            if( rank[x] > rank[y] ) swap(x ,y);
            p[x] = y;

            if( rank[x] == rank[y] ) rank[y] += 1;
            setSize[y] += setSize[x];
            numSet -= 1;
        }
};

// ---------------------------------------------------------- //
// ------------- Articulation Point And Bridges ------------- //

vector< bool > articulation_vertex;
vector< int > dfs_parent;
vector< int > dfs_low;
vector< int > dfs_num;
int dfsNumberCounter;
int rootChildren;
int dfsRoot;

void init()
{
    dfsRoot = 0;
    rootChildren = 0;
    dfsNumberCounter = 0;
    dfs_low.assign(n ,0);
    dfs_num.assign(n ,0);
    dfs_parent.assign(n ,-1);
    articulation_vertex.assign(n ,false);
}

void articulationPointAndBridges(int u)
{
    dfs_num[u] = dfs_low[u] = dfsNumberCounter++;

    for(auto v : al[u])
    {
        if( dfs_num[v] == 0 )
        {
            dfs_parent[v] = u;
            rootChildren += (u == dfsRoot);

            articulationPointAndBridges(v);

            if( dfs_low[v] >= dfs_num[u] ){
                articulation_vertex[u] = true;
            }
            if( dfs_low[v] > dfs_num[u] ){
                // (u ,v) is Bridge
            }

            dfs_low[u] = min(dfs_low[u] ,dfs_low[v]);
        }
        else if( v != dfs_parent[u] ) dfs_low[u] = min(dfs_low[u] ,dfs_num[v]);
    }

    if( u == dfsRoot ) articulation_vertex[u] = (rootChildren > 1);
}


// --------------------------------------------------- //
// --------------------- MST ------------------------- //
// ------------------- Kruskal ----------------------- //

vector< vi > mstAl;   // MST Adj List
map< ii , ll > mstEL; // MST Edg List

ll Kruskal(vector< iii > EL) // Orginal Edg List
{
    ll mstCost = 0;

    UnionFind UF(n);

    sort(EL.begin() ,EL.end());

    for(auto i : EL)
    {
        int u = i.S.F;
        int v = i.S.S;

        if( !UF.isSameSet(u ,v) )
        {
            mstCost += i.F;
            UF.unionSet(u ,v);

            mstAL[u].PB(v);
            mstAL[v].PB(u);
            mstEL[ pll(u ,v) ] = i.F;
            mstEL[ pll(v ,u) ] = i.F;
        }
    }

    return mstCost;
}

// ---------------------------------- //
// ============= Prim =============== //

priority_queue< ii , vii , greater< ii > > pq;
vector< vii > al;

void process(int u)
{
    vis[u] = true;
    for(ii v : al[u])
        if( !vis[v.F] )
            pq.push( ii(v.S ,v.F) );
}

int main()
{
    // ....
    // ....


    vis.assign(n ,false);
    process(0);

    ll mstCost = 0;
    while( !pq.empty() )
    {
        int u = pq.top().S;
        int w = pq.top().F;
        pq.pop();

        if( !vis[u] )
        {
            mstCost += w;
            process(u);
        }
    }

}

// --------------------------------- //
// ============= SCC =============== //

vector< vector< int > > al ,al_t;
vector< int > dfs_num ,S;
int n ,m;

void init()
{
    S.clear();
    dfs_num.assign(n ,0);
    al.assign(n ,vector< int >());
    al_t.assign(n ,vector< int >());
}

void kosaraju1(int u)
{
    dfs_num[u] = 1;

    for(int v : al[u]) if( !dfs_num[v] ) kosaraju1(v);

    S.push_back(u);
}

void kosaraju2(int u ,UnionFind &UF)
{
    dfs_num[u] = 1;

    for(int v : al_t[u]) if( !dfs_num[v] )
    {
        UF.unionSet(u ,v);
        kosaraju2(v ,UF);
    }
}

void Solve()
{
    scanf("%d%d" ,&n ,&m);

    init();
    while( m-- )
    {
        int u; scanf("%d" ,&u); u--;
        int v; scanf("%d" ,&v); v--;
        al_t[v].push_back(u); // Note This
        al[u].push_back(v);
    }

    for(int i = 0 ; i < n ; i++)
        if( !dfs_num[i] )
            kosaraju1(i);

    UnionFind UF(n);
    dfs_num.assign(n ,0);
    for(int i = n - 1 ; i >= 0 ; i--)
        if( !dfs_num[ S[i] ] )
            kosaraju2(S[i] ,UF);
}

// ------------------------------------- //
// ============= Strings =============== //
// ------------------------------------- //

string s ,t;
int n ,m;

inline string SubStr(string &Str ,int Start ,int Len = 1e9)
{
    /// --- Give String + StartIdx (If You Want To The End Of String) --- ///
    /// --- Give String + StartIdx + Len (If You Want Len Of SubStr) ---- ///

    string Res;

    int N = (int)Str.size();
    Len   = max(0 ,Len);
    Start = max(0 ,Start);

    for(int i = Start ; (i < N && i < Start + Len) ; i++){
        Res += Str[i];
    }
    return Res;
}

/// ---------------------- ///
/// -------- \KMP -------- ///
/// ---------------------- ///

    vector< int > KmpPreProcess(string &s ,int n)
    {
        /// --- KMP BackTable Maker --- ///
        /// --- The BackTable Of Main String --- ///

        vector< int >  BackTable(n);
        int i = 0 ,j = BackTable[0] = -1;

        while( i < n )
        {
            while( j >= 0 && s[i] != s[j] ) j = BackTable[j];
            BackTable[ ++i ] = ++j;
        }
        return BackTable;
    }

    int KmpSearch(string &s ,int n ,string &t ,int m ,vector< int > &BackTable)
    {
        int i = 0 , j = 0;
        int Res = 0;

        while( i < n )
        {
            while( j >= 0 && s[i] != t[j] ) j = BackTable[j];
            i ++ , j ++;

            if( j == m )
            {
                // -- Found In The Position i - j -- //
                j = BackTable[j];
                Res += 1;
            }
        }

        return Res;
    }

/// ---------------------- ///
/// --- \Suffix \Array --- ///
/// ---------------------- ///

    void CountSort(vector< int > &SA ,vector< int > &RA ,int k ,int n)
    {
        int N = max(300 ,n);
        vector< int > Cnt(N ,0);
        vector< int > tempSA(n);

        /// --- Count The Repetitions --- ///
        for(int i = 0 ; i < n ; i++){
            Cnt[ (i + k >= n) ? 0 : RA[i + k] ] ++;
        }

        /// --- Find The Correct Index Of Each Repetition --- ///
        for(int i = 0, sum = 0 ; i < N ; i++)
        {
            int t = Cnt[i];
            Cnt[i] = sum;
            sum += t;
        }

        /// --- Put Each Repetition In It's Right Place --- ///
        for(int i = 0 ; i < n ; i++){
            tempSA[ Cnt[ ((SA[i] + k) < n) ? RA[ SA[i] + k ] : 0] ++ ] = SA[i];
        }

        /// --- UPD Suffix Array --- ///
        SA = tempSA;
    }

    void RadixSort(vector< int > &SA ,vector< int > &RA ,int s ,int f ,int n)
    {
        CountSort(SA ,RA ,s ,n); /// --- Sort By Second --- ///
        CountSort(SA ,RA ,f ,n); /// --- Sort By First  --- ///

        /// --- Sort The Pair ii(F ,S) --- ///
    }

    vector< int > ConstructSA(string &s ,int n)
    {
        vector< int > tempRA(n ,0);
        vector< int > SA(n ,0) ,RA(n ,0);

        for(int i = 0 ; i < n ; i++) RA[i] = (int)s[i];
        for(int i = 0 ; i < n ; i++) SA[i] = i;

        for(int k = 1 ; k < n && (RA[ SA[n - 1] ] != n - 1) ; k <<= 1 )
        {
            /// --- Sort pairs (RA[i] ,RA[i + k]) --- ///
            RadixSort(SA ,RA ,k ,0 ,n);

            /// --- Give New Ranks After Sorting --- ///
            int r = tempRA[ SA[0] ] = 0;
            for(int i = 1 ; i < n ; i++)
            {
                bool flagF = (RA[ SA[i] ] == RA[ SA[i - 1] ]);
                bool flagS = (RA[ (SA[i] + k) >= n ? 0 : SA[i] + k ] ==
                              RA[ (SA[i - 1] + k) >= n ? 0 : SA[i - 1] + k ]);
                tempRA[ SA[i] ] = (flagF && flagS) ? r : ++r;
            }

            /// --- UPD Rank Array --- ///
            RA = tempRA;
        }

        return SA;
    }

    /// --- Find Str t in Str s --- ///
    bool Search(vector< int > &Suff ,string &s ,int n ,string &t ,int m)
    {
        bool Res = false;

        /// --- Binary Search The Suffixes --- ///
        int L = 0 ,R = n - 1;
        while( L <= R && !Res )
        {
            int Mid = (L + R) >> 1;

            string SubSuffString = SubStr(s ,Suff[Mid] ,m);

                 if( SubSuffString < t ) L = Mid + 1;
            else if( SubSuffString > t ) R = Mid - 1;
            else Res = true;
        }

        return Res;
    }

    /// --- Count Occurs Of Str t in Str s --- ///
    int CntOfOccInStr(vector< int > &Suff ,string &s ,int n ,string &t ,int m)
    {

        /// --- Binary Search The Suffixes Get LowerBound --- ///
        int OccF;{
            int L = 0 ,R = n - 1;
            while( L <= R )
            {
                int Mid = (L + R) >> 1;

                string SubSuffString = SubStr(s ,Suff[Mid] ,m);

                     if( SubSuffString >= t ) R = Mid - 1;
                else if( SubSuffString <  t ) L = Mid + 1;
            }

            string  SubSuffString = SubStr(s ,Suff[L] ,m);
            OccF = (SubSuffString == t) ? L : -1;
        }

        /// --- Binary Search The Suffixes Get UpperBound --- ///
        int OccL;{
            int L = 0 ,R = n - 1;
            while( L <= R )
            {
                int Mid = (L + R) >> 1;

                string SubSuffString = SubStr(s ,Suff[Mid] ,m);

                     if( SubSuffString >  t ) R = Mid - 1;
                else if( SubSuffString <= t ) L = Mid + 1;
            }

            string  SubSuffString = SubStr(s ,Suff[R] ,m);
            OccL = (SubSuffString == t) ? R : -2;
        }

        int Cnt = OccL - OccF + 1;
        /// --- Ans = Idx OF UpperBound - Idx Of LowerBound + 1 --- ///
        return Cnt;
    }

    vector< int > GetLCP(vector< int > &Suff ,string &s ,int n)
    {
        vector< int > PLCP(n); /// --- LCP in UnSorted Suffixes Order --- ///
        vector< int > LCP(n);  /// --- LCP in   Sorted Suffixes Order --- ///
        vector< int > Phi(n);  /// --- Phi Give Me The Last Suffix Before Suffix[i] In Sorted Order -- ///
                               /// --- Phi[ Suff[i] ] = Suff[i - 1]; --- ///

        /// --- Fill Phi[n] --- ///
        Phi[ Suff[0] ] = -1;
        for(int i = 1 ; i < n ; i++) Phi[ Suff[i] ] = Suff[i - 1];

        /// --- LCP Algorithm  --- ///
        /// --- Compare Suff[i] With Phi[ Suff[i] ] And Move To Suff[i + 1] --- ///
        for(int i = 0 ,Len = 0 ; i < n ; i ++)
        {
            if( Phi[i] != -1 )
            {
                while( (i + Len < n) && (Phi[i] + Len < n)
                      && (s[i + Len] == s[Phi[i] + Len]) ){
                        Len += 1;
                }

                PLCP[i] = Len;
                Len = max(Len - 1 ,0);
            }
            else PLCP[i] = 0;
        }

        /// --- Fix LCP vector --- ///
        for(int i = 0 ; i < n ; i++) LCP[i] = PLCP[ Suff[i] ];
        return LCP;
    }

    ll CntNumOfDiffSubStr(vector< int > &Suff ,vector< int > &LCP ,int n)
    {
        /// --- Count The Number Of Different Sub String --- ///
        /// --- Is Equal To Sum Of Different Between Len Of Suffix And LCP --- ///

        ll Sum = 0ll;
        for(int i = 1 ; i < n ; i++) Sum += ( (n - 1 - Suff[i]) - LCP[i] );
        return Sum;
    }

    int LCS(string &s ,string &t ,int n ,int m)
    {
        /// --- Note: Don't Compute SuffixA Or LCP Before Call This Function --- ///
        /// --- Find Longest Common SubString Of Tow Strings --- ///
        string S = s + '#' + t + '$';
        int N    = n + m + 2;

        /// --- Get LCP Array Of Tow Strings --- ///
        vector< int > Suff = ConstructSA(S ,N);
        vector< int > LCP = GetLCP(Suff ,S ,N);

        /// --- Put Each Suffix In One Of Tow Classes --- ///
        /// --- One For Suffix before '#' And One For After --- ///
        vector< ii > LcpWithType(N);
        for(int i = 0 ; i < N ; i++)
        {
            LcpWithType[i].S = LCP[i];
            LcpWithType[i].F = (Suff[i] < n) ? 1 : 2;
        }

        /// --- Calculate The LCP With Condition That Suffixes Should Be From Different Classes --- ///
        int Res = INT_MIN;
        for(int i = 1 ; i < N ; i++){
            if( LcpWithType[i].F != LcpWithType[i - 1].F ){
                Res = max(Res ,LcpWithType[i].S);
            }
        }

        return Res;
    }

    inline int Cmp(vector< int > &Suff ,vector< int > &Pos ,int i ,int j ,int k)
    {
        ii a = ii(Pos[ Suff[i] ] ,Pos[ Suff[i + k < n ? i + k : 0] ]);
        ii b = ii(Pos[ Suff[j] ] ,Pos[ Suff[j + k < n ? j + k : 0] ]);
        return a == b ? 0 : a < b ? -1 : 1;
    }

int main()
{
    n = (int)(s = Read()).size();
    m = (int)(t = Read()).size();

    vector< int > b = KmpPreProcess(s ,n);
    int Res = KmpSearch(s ,n ,t ,m ,b);
    cout << Res << endl;

    int LongestSubStr = LCS(s ,t ,n ,m);
    printf("Longest Common SubString Of s & t = %d\n" ,LongestSubStr);

    vector< int > Suff = ConstructSA(s ,n);
    vector< int > LCP = GetLCP(Suff ,s ,n);
    ll NumOfDiffSubStr = CntNumOfDiffSubStr(Suff ,LCP ,n);

    printf("i   SA[i]   LCP[i]   Suffix \n");
    for(int i = 0 ; i < n ; i++ , puts(""))
    {
        printf("%d     %d       %d        " ,i ,Suff[i] ,LCP[i]);
        for(auto i : s.substr(Suff[i]))          printf("%c" ,i);
    }
    printf("\n The Number Of Different Sub String = %lld \n" ,NumOfDiffSubStr);
}

// ----------------------------------------------------------------- //
