#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define int long long
class Comparator{
    public:
    bool operator()(int l, int r){
        return l <= r;
    }
};
class Matrix{
    private:
    vector < vector < int > > mat;

    public:
    Matrix(vector < vector < int > >& mat1){
        mat = mat1;
    }
    void sortRows(Comparator comparator,string& order){
        int n = mat.size();
        for(int i = 0; i < n; i ++){
            mergeSort(mat[i],comparator);
            if(order == "descending")reverse(mat[i].begin(), mat[i].end());
        }
    }
    void mergeSort(vector < int >& v,Comparator& comparator){
        int n = v.size();
        if(n == 1)return;
        vector < int > v1(n/2),v2(n-n/2);
        for(int i = 0; i < n/2; i ++)v1[i] = v[i];
        for(int i = n/2; i < n; i ++)v2[i - n/2] = v[i];
        mergeSort(v1,comparator);
        mergeSort(v2,comparator);
        int p1 = 0, p2 = 0 , i = 0;
        while(p1 != n/2 and p2 != n - n/2){
            if(comparator(v1[p1],v2[p2])){
                v[i] = v1[p1];
                i ++;
                p1 ++;
            }
            else{
                v[i] = v2[p2];
                i ++;
                p2 ++;
            }
        }
        while(p1 != n/2){
            v[i] = v1[p1];
            i ++;
            p1 ++;
        }
        while(p2 != n - n/2){
            v[i] = v2[p2];
            i ++;
            p2 ++;
        }
    }
    int countInversions(){
        int n = mat.size();
        int N = n*n;
        vector < int > v(N);
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < n; j ++){
                v[(i * n) + j] = mat[i][j];
            }
        }
        return countInversions(v);
        // function < int (vector < int >& , int, int) > fun = [](){};
    }
    int countInversions(vector < int >& v){
        int n = v.size();
        if(n == 1)return 0;
        int inversions = 0;
        vector < int > v1(n/2),v2(n-n/2);
        for(int i = 0; i < n/2; i ++)v1[i] = v[i];
        for(int i = n/2; i < n; i ++)v2[i - n/2] = v[i];
        inversions += countInversions(v1);
        inversions += countInversions(v2);
        int p1 = 0, p2 = 0 , i = 0;
        while(p1 != n/2 and p2 != n - n/2){
            if(v1[p1] <= v2[p2]){
                v[i] = v1[p1];
                i ++;
                p1 ++;
            }
            else{
                v[i] = v2[p2];
                i ++;
                p2 ++;
                inversions += (n/2 - p1);
            }
        }
        while(p1 != n/2){
            v[i] = v1[p1];
            i ++;
            p1 ++;
        }
        while(p2 != n - n/2){
            v[i] = v2[p2];
            i ++;
            p2 ++;
        }
        return inversions;
    }
    void display(){
        for(int i = 0;i < mat.size(); i ++){
            for(int j = 0;j < mat.size();j ++){
                cout << mat[i][j] << " ";
            }
            cout << "\n";
        }
    }
};

bool magic(pair < int , int >& l, pair < int , int >& r){
    if(l.S != r.S)return l.S < r.S;
    else return l.F < r.F;
};
void modify(vector < int >& v, map < pair < int , int > , int >& mp){
    if(mp[make_pair(v[0],v[1])] > mp[make_pair(v[2],v[3])]){
        swap(v[0],v[2]);
        swap(v[1],v[3]);
    }
}
int dist(vector < int >& v){
    int x1 = v[0],y1 = v[1];
    int x2 = v[2],y2 = v[3];
    int dist_sq = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
    return dist_sq;
    // return sqrt(dist_sq);
}
void fun(vector < int >& min_v, vector < int >& v, int& delta, map < pair < int , int > , int >& mp){
    int cur_dist = dist(v);
    if(cur_dist < delta){
        min_v = v;
        delta = cur_dist;
    }
    else if(cur_dist == delta){
        if(min_v[0] > v[0]){
            min_v = v;
        }
        else if(min_v[0] < v[0]){
            //do nothing
        }
        else if(min_v[1] > v[1]){
            min_v = v;
        }
        else if(min_v[1] < v[1]){
            //do nothing
        }
        else if(min_v[2] > v[2]){
            min_v = v;
        }
        else if(min_v[2] < v[2]){
            //do nothing
        }
        else if(min_v[3] > v[3]){
            min_v = v;
        }
        else if(min_v[3] < v[3]){
            //do nothing
        }
    }
}
class Plane{
    private:
    vector < pair < int , int > > xsort;
    map < pair < int , int > , int > mp;

    public:
    Plane(vector < pair < int , int > >& points1){
        xsort = points1;
        for(int i = 0; i < xsort.size(); i ++){
            mp[xsort[i]] = i;
        }
        sort(xsort.begin(),xsort.end());
    }
    int dist(vector < int >& v){
        return (v[0] - v[1])*(v[0] - v[1]) + (v[2] - v[3])*(v[2] - v[3]);
    }
    void closestPair(){
        vector < int > ans = closestPair(xsort);
        for(int i = 0; i < 4; i ++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    vector < int > closestPair(vector < pair < int , int > >& xsort){
        int n = xsort.size();
        if(n == 2){
            vector < int > min_v(4);
            min_v[0] = xsort[0].F;
            min_v[1] = xsort[0].S;
            min_v[2] = xsort[1].F;
            min_v[3] = xsort[1].S;
            modify(min_v,mp);
            return min_v;
        }
        if(n == 3){
            vector < int > v1(4),v2(4),v3(4),min_v(4);
            v1[0] = xsort[0].F; v1[1] = xsort[0].S; v1[2] = xsort[2].F; v1[3] = xsort[2].S;
            v2[0] = xsort[0].F; v2[1] = xsort[0].S; v2[2] = xsort[1].F; v2[3] = xsort[1].S;
            v3[0] = xsort[1].F; v3[1] = xsort[1].S; v3[2] = xsort[2].F; v3[3] = xsort[2].S;
            int delta = INT64_MAX;
            fun(min_v,v1,delta,mp);
            fun(min_v,v2,delta,mp);
            fun(min_v,v3,delta,mp);
            modify(min_v,mp);
            return min_v;
        }
        int delta = INT64_MAX;
        vector < int > min_v(4),v1(4),v2(4);
        vector < pair < int , int > > left(n/2),right(n - n/2);
        for(int i = 0; i < n/2; i ++)left[i] = xsort[i];
        for(int i = n/2; i < n; i ++)right[i - n/2] = xsort[i];
        v1 = closestPair(left);
        v2 = closestPair(right);
        fun(min_v,v1,delta,mp);
        fun(min_v,v2,delta,mp);
        int line = xsort[n/2].F;
        vector < pair < int , int > > temp;
        for(int i = n/2; (line - xsort[i].F)*(line - xsort[i].F) < delta and
            i < xsort.size(); i ++){
            temp.push_back(xsort[i]);
        }
        for(int i = n/2 - 1; (line - xsort[i].F)*(line - xsort[i].F) < delta and
            i >= 0; i --){
            temp.push_back(xsort[i]);
        }
        sort(temp.begin(),temp.end(),magic);
        for(int i = 0; i < temp.size(); i ++){
            vector < int > v(4); v[0] = temp[i].F; v[1] = temp[i].S;
            for(int j = i + 1; j - i < 8 and j < temp.size(); j++){
                v[2] = temp[j].F; v[3] = temp[j].S;
                fun(min_v,v,delta,mp);
            }
        }
        modify(min_v,mp);
        return min_v;
    }
};
int32_t main(){
    string s; cin>>s;
    while(s == "CLOSEST_2D"){
        int n; cin >> n;
        vector < pair < int , int > > b(n);
        for(int i = 0; i < n; i ++){
            cin >> b[i].F >> b[i].S;
        }
        Plane plane(b);
        plane.closestPair();
        cin >> s;
    }
    if(s == "END")return 0;
    int n; cin >> n;
    vector < vector < int > > mat (n, vector < int > (n));
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            cin >> mat[i][j];
        }
    }
    Matrix* M = new Matrix (mat);
    cin >> s;
    while(1){
        if(s == "SORT_2D" ){
            string order; cin >> order;
            M->sortRows(Comparator(),order);
        }
        else if(s == "INVERSION_2D" ){
            cout << M->countInversions() << "\n";
        }
        else if(s == "DISPLAY_2D" ){
            M->display();
        }
        else if(s == "CLOSEST_2D"){
            int n; cin >> n;
            vector < pair < int , int > > b(n);
            for(int i = 0; i < n; i ++){
                cin >> b[i].F >> b[i].S;
            }
            Plane plane(b);
            plane.closestPair();
        }
        else{
            break;
        }
        cin>>s;
    }
}
