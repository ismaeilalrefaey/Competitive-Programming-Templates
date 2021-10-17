#include <bits/stdc++.h>
using namespace std;

typedef pair<int , int> ii;
typedef long long Int;
#define S second
#define F first

string s ,t;
int n ,m;

string Read(){
    fflush(stdin);
    string Buff;
    getline(cin ,Buff);
    return Buff;
}

inline string SubStr(string &Str ,int Start ,int Len = 1e9){
    /// --- Give String + StartIdx (If You Want To The End Of String) --- ///
    /// --- Give String + StartIdx + Len (If You Want Len Of SubStr) ---- ///

    string Res;

    int N = (int)Str.size();
    Len   = max(0 ,Len);
    Start = max(0 ,Start);

    for(int i = Start ; (i < N && i < Start + Len) ; i++)
        Res += Str[i];
    return Res;
}

/// ---------------------- ///
/// -------- \KMP -------- ///
/// ---------------------- ///

    vector< int > KmpPreProcess(string &s ,int n){
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

    int KmpSearch(string &s ,int n ,string &t ,int m ,vector< int > &BackTable){
        int i = 0 , j = 0;
        int Res = 0;

        while( i < n )
        {
            while( j >= 0 && s[i] != t[j] ) j = BackTable[j];
            i ++ , j ++;

            if( j == m ){
                // -- Found In The Position i - j -- //
                j = BackTable[j];
                Res += 1;
            }
        }

        return Res;
    }

/// --------------------------------------------------------------------------------------------------- ///


/// ---------------------- ///
/// --- \Suffix \Array --- ///
/// ---------------------- ///

    void CountSort(vector< int > &SA ,vector< int > &RA ,int k ,int n){
        int N = max(300 ,n);
        vector< int > Cnt(N ,0);
        vector< int > tempSA(n);

        /// --- Count The Repetitions --- ///
        for(int i = 0 ; i < n ; i++)
            Cnt[ (i + k >= n) ? 0 : RA[i + k] ] ++;

        /// --- Find The Correct Index Of Each Repetition --- ///
        for(int i = 0, sum = 0 ; i < N ; i++){
            int t = Cnt[i];
            Cnt[i] = sum;
            sum += t;
        }
	
        /// --- Put Each Repetition In It's Right Place --- ///
        for(int i = 0 ; i < n ; i++)
            tempSA[ Cnt[ ((SA[i] + k) < n) ? RA[ SA[i] + k ] : 0] ++ ] = SA[i];

        /// --- UPD Suffix Array --- ///
        SA = tempSA;
    }

    void RadixSort(vector< int > &SA ,vector< int > &RA ,int s ,int f ,int n){
        CountSort(SA ,RA ,s ,n); /// --- Sort By Second --- ///
        CountSort(SA ,RA ,f ,n); /// --- Sort By First  --- ///

        /// --- Sort The Pair ii(F ,S) --- ///
    }

    vector< int > ConstructSA(string &s ,int n){
        vector< int > tempRA(n ,0);
        vector< int > SA(n ,0) ,RA(n ,0);

        for(int i = 0 ; i < n ; i++) RA[i] = (int)s[i];
        for(int i = 0 ; i < n ; i++) SA[i] = i;

        for(int k = 1 ; k < n && (RA[ SA[n - 1] ] != n - 1) ; k <<= 1 ){
            /// --- Sort pairs (RA[i] ,RA[i + k]) --- ///
            RadixSort(SA ,RA ,k ,0 ,n);

            /// --- Give New Ranks After Sorting --- ///
            int r = tempRA[ SA[0] ] = 0;
            for(int i = 1 ; i < n ; i++){
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
    bool Search(vector< int > &Suff ,string &s ,int n ,string &t ,int m){
        bool Res = false;

        /// --- Binary Search The Suffixes --- ///
        int L = 0 ,R = n - 1;
        while( L <= R && !Res ){
            int Mid = (L + R) >> 1;

            string SubSuffString = SubStr(s ,Suff[Mid] ,m);

                 if( SubSuffString < t ) L = Mid + 1;
            else if( SubSuffString > t ) R = Mid - 1;
            else Res = true;
        }

        return Res;
    }

    /// --- Count Occurs Of Str t in Str s --- ///
    int CntOfOccInStr(vector< int > &Suff ,string &s ,int n ,string &t ,int m){

        /// --- Binary Search The Suffixes Get LowerBound --- ///
        int OccF;{
            int L = 0 ,R = n - 1;
            while( L <= R ){
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
            while( L <= R ){
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

    vector< int > GetLCP(vector< int > &Suff ,string &s ,int n){
        vector< int > PLCP(n); /// --- LCP in UnSorted Suffixes Order --- ///
        vector< int > LCP(n);  /// --- LCP in   Sorted Suffixes Order --- ///
        vector< int > Phi(n);  /// --- Phi Give Me The Last Suffix Before Suffix[i] In Sorted Order -- ///
                               /// --- Phi[ Suff[i] ] = Suff[i - 1]; --- ///

        /// --- Fill Phi[n] --- ///
        Phi[ Suff[0] ] = -1;
        for(int i = 1 ; i < n ; i++) Phi[ Suff[i] ] = Suff[i - 1];

        /// --- LCP Algorithm  --- ///
        /// --- Compare Suff[i] With Phi[ Suff[i] ] And Move To Suff[i + 1] --- ///
        for(int i = 0 ,Len = 0 ; i < n ; i ++){
            if( Phi[i] != -1 ){
                while( (i + Len < n) && (Phi[i] + Len < n)
                      && (s[i + Len] == s[Phi[i] + Len]) )
                        Len += 1;
                PLCP[i] = Len;
                Len = max(Len - 1 ,0);
            } else PLCP[i] = 0;
        }

        /// --- Fix LCP vector --- ///
        for(int i = 0 ; i < n ; i++) LCP[i] = PLCP[ Suff[i] ];
        return LCP;
    }

    Int CntNumOfDiffSubStr(vector< int > &Suff ,vector< int > &LCP ,int n){
        /// --- Count The Number Of Different Sub String --- ///
        /// --- Is Equal To Sum Of Different Between Len Of Suffix And LCP --- ///

        Int Sum = 0ll;
        for(int i = 1 ; i < n ; i++) Sum += ( (n - 1 - Suff[i]) - LCP[i] );
        return Sum;
    }

    int LCS(string &s ,string &t ,int n ,int m){
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
        for(int i = 0 ; i < N ; i++){
            LcpWithType[i].S = LCP[i];
            LcpWithType[i].F = (Suff[i] < n) ? 1 : 2;
        }

        /// --- Calculate The LCP With Condition That Suffixes Should Be From Different Classes --- ///
        int Res = INT_MIN;
        for(int i = 1 ; i < N ; i++)
            if( LcpWithType[i].F != LcpWithType[i - 1].F )
                Res = max(Res ,LcpWithType[i].S);

        return Res;
    }

    inline int Cmp(vector< int > &Suff ,vector< int > &Pos ,int i ,int j ,int k){
        ii a = ii(Pos[ Suff[i] ] ,Pos[ Suff[i + k < n ? i + k : 0] ]);
        ii b = ii(Pos[ Suff[j] ] ,Pos[ Suff[j + k < n ? j + k : 0] ]);
        return a == b ? 0 : a < b ? -1 : 1;
    }

/// --------------------------------------------------------------------------------------------------- ///

int main() {

}

/// --------------------------------------------------------------------------------------------------- ///

/*
/// --- Template --- ///
int main(){
    n = (int)(s = Read()).size();
    m = (int)(t = Read()).size();

    vector< int > b = KmpPreProcess(s ,n);
    int Res = KmpSearch(s ,n ,t ,m ,b);
    cout << Res << endl;

    int LongestSubStr = LCS(s ,t ,n ,m);
    printf("Longest Common SubString Of s & t = %d\n" ,LongestSubStr);

    vector< int > Suff = ConstructSA(s ,n);
    vector< int > LCP = GetLCP(Suff ,s ,n);
    Int NumOfDiffSubStr = CntNumOfDiffSubStr(Suff ,LCP ,n);

    printf("i   SA[i]   LCP[i]   Suffix \n");
    for(int i = 0 ; i < n ; i++ , puts("")){
        printf("%d     %d       %d        " ,i ,Suff[i] ,LCP[i]);
        for(auto i : s.substr(Suff[i]))          printf("%c" ,i);
    }
    printf("\n The Number Of Different Sub String = %lld \n" ,NumOfDiffSubStr);
}
*/
