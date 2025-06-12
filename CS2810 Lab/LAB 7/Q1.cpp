#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define F first
#define S second

string operator *(string s, int x){
    string s1 = "";
    while(x--)s1 += s;
    return s1;
}

int power(int x, int n){
    int ans = 1;
    while(n){
        if(n % 2)ans *= x;
        x *= x;
        n /= 2;
    }
    return ans;
}

int roof(float x){
    if((int)x == x){
        return x;
    }
    return (int)x + 1;
}

class Complex{
    private:
    int real;
    int img;

    public:
    int getReal(){
        return real;
    }
    int getimg(){
        return img;
    }
    Complex(int real1, int img1){
        real = real1;
        img = img1;
    }
    Complex(){
        real = 0;
        img = 0;
    }
    Complex operator *(Complex& com1){
        Complex mul(real * com1.getReal() - img * com1.getimg(),
            real * com1.getimg() + img * com1.getReal());
        return mul;
    }
    Complex operator +(Complex& com1){
        Complex add(real + com1.getReal(), img + com1.getimg());
        return add;
    }
    Complex operator -(Complex& com1){
        Complex sub(real - com1.getReal(), img - com1.getimg());
        return sub;
    }
    void operator +=(Complex& com1){
        real += com1.getReal();
        img += com1.getimg();
    }
    Complex operator *(int x){
        Complex mul(real * x, img * x);
        return mul;
    }
};

template <typename T>
class MultiPoly{
    private:
    int n;
    vector < T > poly;

    public:
    vector < T >& getPoly(){
        return poly;
    }
    MultiPoly(vector < T >& coeff1){
        poly = coeff1;
        n = poly.size();
        // cout << "old " << n << "\n";
        n = power(2, roof(log2(n)));
        // cout << "new " << n << "\n";
        poly.resize(n);
    }
    MultiPoly(MultiPoly < T >& coeff1, int l, int r){
        n = r - l + 1;
        n = power(2, roof(log2(n)));
        poly.resize(n);
        for(int i = l ; i <= r ; i ++){
            poly[i - l] = coeff1.getPoly()[i];
        }
    }
    MultiPoly(){}
    int getN(){
        return n;
    }
    MultiPoly < T > operator *(MultiPoly < T > poly1){
        int newsize = max(n, poly1.getN());
        poly.resize(newsize);
        poly1.getPoly().resize(newsize);
        MultiPoly < T > poly2 = *this;
        // cout << poly1.getPoly().size() << " " << poly2.getPoly().size() << "\n";
        return Karatsuba(poly2, poly1);
    }
    MultiPoly < T > operator -(MultiPoly < T >& poly1){
        vector < T > newvector(poly.size());
        for(int i = 0 ; i < n ; i ++){
            newvector[i] = poly[i] - poly1.getPoly()[i];
        }
        return MultiPoly < T > (newvector);
    }
    MultiPoly < T > operator +(MultiPoly < T >& poly1){
        vector < T > newvector(poly.size());
        for(int i = 0 ; i < n ; i ++){
            newvector[i] = poly[i] + poly1.getPoly()[i];
        }
        return MultiPoly < T > (newvector);
    }
};

template < typename T >
MultiPoly < T > Karatsuba(MultiPoly < T >& poly1, MultiPoly < T >& poly2){
    int n = poly1.getPoly().size();
    int m = n/2;
    if(n == 1){
        vector < T > ans(1);
        ans[0] = poly1.getPoly()[0] * poly2.getPoly()[0];
        // cout << ans[0] << "\n";
        return MultiPoly < T > (ans);
    }
    // cout << poly1.getPoly().size() << " " << poly2.getPoly().size() << "\n";
    MultiPoly < T > x0(poly1, 0, n/2 - 1);
    MultiPoly < T > x1(poly1, n/2, n - 1);
    MultiPoly < T > y0(poly2, 0, n/2 - 1);
    MultiPoly < T > y1(poly2, n/2, n - 1);
    MultiPoly < T > x2 = x0 - x1;
    MultiPoly < T > y2 = y0 - y1;
    MultiPoly < T > z0 = Karatsuba(x0, y0);
    MultiPoly < T > z2 = Karatsuba(x1, y1);
    MultiPoly < T > z3 = Karatsuba(x2, y2);
    MultiPoly < T > z1 = z0 + z2 - z3;
    // cout << z1.getPoly()[0] << "\n";
    vector < T > ans(2 * n);
    for(int i = 0 ; i < z0.getPoly().size(); i ++){
        ans[i] += z0.getPoly()[i];
    }
    for(int i = 0 ; i < z1.getPoly().size(); i ++){
        ans[i + m] += z1.getPoly()[i];
    }
    for(int i = 0 ; i < z2.getPoly().size(); i ++){
        ans[i + 2 * m] += z2.getPoly()[i];
    }
    return MultiPoly < T > (ans);
}

template <typename T>
class EvalPoly{
    private:
    int n;
    vector < T > poly;

    public:
    EvalPoly(vector < T >& coeff1){
        poly = coeff1;
        n = poly.size();
    }
    T evaluate(T ans, int x){
        int powern = power(x, n - 1);
        for(int i = n - 1 ; i >= 0 ; i --){
            ans += (poly[i] * powern);
            powern /= x;
        }
        return ans;
    }
};

template <typename T>
class PolyDiff{
    private:
    int n;
    vector < T > poly;

    public:
    PolyDiff(vector < T >& coeff1){
        poly = coeff1;
        n = poly.size();
    }
    void differentiate(){
        for(int i = 1; i < n ; i ++){
            cout << fixed << setprecision(6) << i * poly[i] << " ";
        }
        cout << "\n";
    }
};
int32_t main(){
    int q; cin >> q;
    while(q --){
        int op; cin >> op;
        if(op == 1){
            string s; cin >> s;
            if(s == "integer"){
                int n; cin >> n;
                int mulsize = n; //mark this
                vector < int > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                MultiPoly < int > poly1(coeff);
                cin >> n;
                mulsize += n; //mark this too
                coeff.resize(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                MultiPoly < int > poly2(coeff);
                MultiPoly < int > mul = poly1 * poly2;
                for(int i = 0 ; i < mulsize - 1; i ++)cout << mul.getPoly()[i] << " ";
                cout << "\n";
            }
            else if(s == "float"){
                int n; cin >> n;
                int mulsize = n; //mark this
                vector < float > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                MultiPoly < float > poly1(coeff);
                cin >> n;
                mulsize += n; //mark this too
                coeff.resize(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                MultiPoly < float > poly2(coeff);
                MultiPoly < float > mul = poly1 * poly2;
                for(int i = 0 ; i < mulsize - 1; i ++)cout << fixed << setprecision(6) << mul.getPoly()[i] << " ";
                cout << "\n";
            }
            else{
                int n; cin >> n;
                int mulsize = n; //mark this
                vector < Complex > coeff(n);
                for(int i = 0 ; i < n ; i ++){
                    int real, img;
                    cin >> real >> img;
                    Complex temp(real, img);
                    coeff[i] = temp;
                }
                MultiPoly < Complex > poly1(coeff);
                cin >> n;
                mulsize += n; //mark this too
                coeff.resize(n);
                for(int i = 0 ; i < n ; i ++){
                    int real, img;
                    cin >> real >> img;
                    Complex temp(real, img);
                    coeff[i] = temp;
                }
                MultiPoly < Complex > poly2(coeff);
                MultiPoly < Complex > mul = poly1 * poly2;
                for(int i = 0 ; i < mulsize - 1; i ++){
                    cout << mul.getPoly()[i].getReal() << " "
                    << mul.getPoly()[i].getimg() << " ";
                }
                cout << "\n";
            }
        }
        else if(op == 2){
            string s; cin >> s;
            if(s == "integer"){
                int n; cin >> n;
                vector < int > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                EvalPoly < int > poly(coeff);
                int x; cin >> x;
                cout << poly.evaluate(0LL, x) << "\n";
            }
            else if(s == "float"){
                int n; cin >> n;
                vector < float > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                EvalPoly < float > poly(coeff);
                int x; cin >> x;
                cout << fixed << setprecision(6) << poly.evaluate((float)0, x) << "\n";
            }
            else{
                int n; cin >> n;
                vector < string > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                EvalPoly < string > poly(coeff);
                int x; cin >> x;
                cout << poly.evaluate("", x) << "\n";
            }
        }
        else{
            string s; cin >> s;
            if(s == "integer"){
                int n; cin >> n;
                vector < int > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                PolyDiff < int > poly(coeff);
                poly.differentiate();
            }
            else{
                int n; cin >> n;
                vector < float > coeff(n);
                for(int i = 0 ; i < n ; i ++)cin >> coeff[i];
                PolyDiff < float > poly(coeff);
                poly.differentiate();
            }
        }
    }
}
