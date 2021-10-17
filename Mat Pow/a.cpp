#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector< ll > Row;
typedef vector< Row > Matrix;

const int MOD = 1e9 + 7;

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

