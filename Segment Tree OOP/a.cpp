#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5e1;
typedef vector<int> vi;
#define rg (p << 1) | 1
typedef long long ll;
#define OO 0x7fffffff
#define lf (p << 1)

int n ,m;

class SegTree {
    private:
        vector<ll> Seg;

        ll Compain(ll a ,ll b){
            return a + b;
        }

        void UPD(int i ,ll v ,int p ,int L ,int R){
            if( i > R || i < L ) return;
            if( L == R ){
                Seg[p] = v; return;}

            int Mid = (L + R) >> 1;
            UPD(i ,v ,lf ,L ,Mid);
            UPD(i ,v ,rg ,Mid + 1 ,R);
            Seg[p] = Compain(Seg[lf] ,Seg[rg]);
        }

        ll QRY(int i ,int j ,int p ,int L ,int R){
            if( i >  R || j <  L ) return 0;
            if( i <= L && R <= j ) return Seg[p];

            int Mid = (L + R) >> 1;
            ll LF = QRY(i ,j ,lf ,L ,Mid);
            ll RG = QRY(i ,j ,rg ,Mid + 1 ,R);
            return Compain(LF ,RG);
        }

    public:
        SegTree(int n){
            Seg.assign(4 * n ,0LL);
        }

        void UPD(int i ,ll v){
            UPD(i ,v ,1 ,1 ,n);
        }

        ll QRY(int L ,int R){
            return QRY(L ,R ,1 ,1 ,n);
        }
};
