#include <bits/stdc++.h>
using namespace std;

#define int long long
const int MOD = 1e9+7;

class Matrix{
    public:
    int a[2][2];
    Matrix (){
        a[0][0] = 0;
        a[0][1] = 0;
        a[1][0] = 0;
        a[1][1] = 0;
    }
    void operator *(Matrix& sec){
        Matrix ans;
        ans.a[0][0] = ((a[0][0]*sec.a[0][0])%MOD + (a[0][1]*sec.a[1][0])%MOD)%MOD;
        ans.a[0][1] = ((a[0][0]*sec.a[0][1])%MOD + (a[0][1]*sec.a[1][1])%MOD)%MOD;
        ans.a[1][0] = ((a[1][0]*sec.a[0][0])%MOD + (a[1][1]*sec.a[1][0])%MOD)%MOD;
        ans.a[1][1] = ((a[1][0]*sec.a[0][1])%MOD + (a[1][1]*sec.a[1][1])%MOD)%MOD;
        a[0][0] = ans.a[0][0];
        a[0][1] = ans.a[0][1];
        a[1][0] = ans.a[1][0];
        a[1][1] = ans.a[1][1];
        // this->a = ans.a;
        // return ans;
    }
    void power(int n){
        Matrix m = *this;
        Matrix ans;
        ans.a[0][0] = 1; ans.a[1][1] = 1;
        while(n){
            if(n%2){
                ans * m;
            }
            m * m;
            n/=2;
        }
        cout<<ans.a[0][0]<<"\n";
        // this->a = ans.a;
        // return *this;
    }
};

class CurrencySorter{
    public:
    void operator()(vector < int >& a){
        //quick sort
        a = quicksort(a);

    }
    vector < int > quicksort(vector < int > a){
        if(a.size()<=1)return a;
        vector < int > b,c;
        int pivot = a[0];
        for(int i=1;i<a.size();i++){
            if(a[i]<pivot)b.push_back(a[i]);
            else c.push_back(a[i]);
        }
        b = quicksort(b);
        c = quicksort(c);
        vector < int > result;
        for(int i=0;i<b.size();i++)result.push_back(b[i]);
        result.push_back(pivot);
        for(int i=0;i<c.size();i++)result.push_back(c[i]);
        return result;
    }
};

class FibonacciGenerator{
    public:
    void operator()(int i){
        Matrix m;
        m.a[0][0] = 1; m.a[0][1] = 1;
        m.a[1][0] = 1; m.a[1][1] = 0;
        m.power(i-1);
        // cout<<ans.a[0][0]<<"\n";
    }
};

class PrimeCalculator{
    public:
    void printPrimes(int l, int r){
        vector < int > prime(sqrt(r) + 5, true);
        vector < int > primeLR(r - l + 1, true);
        for(int p = 2; p * p <= r; p++){
            if(prime[p]){
                for(int i = p * p; i <= sqrt(r) ; i += p){
                    prime[i] = false;
                }
                for(int i = ((l + p - 1) / p) * p; i <= r; i += p){
                    if(i != p){
                        primeLR[i - l] = false;
                    }
                }
            }
        }
        if(l == 1){
            primeLR[0] = false;
        }
        for(int i = 0; i < r - l + 1; i++){
            if(primeLR[i]){
                cout << l + i << " ";
            }
        }
        cout << "\n";
    }
    void printPrimeSum(int l, int r){
        vector < int > prime(sqrt(r) + 5, true);
        vector < int > primeLR(r - l + 1, true);
        for(int p = 2; p * p <= r; p++){
            if(prime[p]){
                for(int i = p * p; i <= sqrt(r) ; i += p){
                    prime[i] = false;
                }
                for(int i = ((l + p - 1) / p) * p; i <= r; i += p){
                    if(i != p){
                        primeLR[i - l] = false;
                    }
                }
            }
        }
        if(l == 1){
            primeLR[0] = false;
        }
        int sum = 0;
        for(int i = 0; i < r - l + 1; i++){
            if(primeLR[i]){
                sum += l + i;
            }
        }
        cout << sum << "\n";
    }

};


class NumberAnalyzer{
    public:
    bool isSquareFree(int& n){
        if(n%4==0)return false;
        for(int i=3;i*i<=n;i += 2){
            if(n%i==0 and (n/i)%i==0)return false;
        }
        return true;
    }
    int countDivisors(int& N){
        int n = N,ans = 1;
        for(int i=2;i*i<=n;i++){
            int cnt = 0;
            while(n%i==0){
                n/=i;
                cnt++;
            }
            ans*=(cnt+1);
        }
        if(n!=1)ans*=2;
        return ans;
    }
    int sumOfDivisors(int& N){
        int n = N,ans = 1;
        for(int i=2;i*i<=n;i++){
            int pdt = 1;
            while(n%i==0){
                n/=i;
                pdt*=i;
            }
            ans*=((pdt*i-1)/(i-1));
        }
        if(n!=1)ans*=(n+1);
        return ans;
    }
};

int32_t main(){
    int type; cin>>type;
    if(type==1){
        int t; cin>>t;
        while(t--){
            int n; cin>>n;
            vector < int > a(n);
            for(int i=0;i<n;i++)cin>>a[i];
            CurrencySorter()(a);
            for(int i=0;i<n;i++)cout<<a[i]<<" ";
            cout<<"\n";
        }
    }
    else if(type==2){
        int t; cin>>t;
        while(t--){
            int i; cin>>i;
            FibonacciGenerator()(i);
        }
    }
    else if(type==3){
        int t; cin>>t;
        PrimeCalculator obj;
        while(t--){
            string s; cin>>s;
            int l,r; cin>>l>>r;
            if(s=="printPrimes"){
                obj.printPrimes(l,r);
            }
            else{
                obj.printPrimeSum(l,r);
            }
        }
    }
    else{
        int t; cin>>t;
        NumberAnalyzer obj;
        while(t--){
            string s; cin>>s;
            int n; cin>>n;
            if(s=="isSquareFree"){
                if(obj.isSquareFree(n))cout<<"yes\n";
                else cout<<"no\n";
            }
            else if(s=="countDivisors"){
                cout<<obj.countDivisors(n)<<"\n";
            }
            else{
                cout<<obj.sumOfDivisors(n)<<"\n";
            }
        }
        
    }
}
