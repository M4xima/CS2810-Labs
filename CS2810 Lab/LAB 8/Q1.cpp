#include <bits/stdc++.h>
using namespace std;

#define int long long
#define F first
#define S second

#ifdef IOS
#include "debug.h"
#else
#define debug(...)
#endif

class Node{
    private:
    string ID;
    int evenDist;
    int oddDist;

    public:
    int getevenDist(){
        return evenDist;
    }
    void setevenDist(int dist1){
        evenDist = dist1;
    }
    int getoddDist(){
        return oddDist;
    }
    void setoddDist(int dist1){
        oddDist = dist1;
    }
    string getID(){
        return ID;
    }
    Node(string& ID1, int dist1, int dist2){
        ID = ID1;
        evenDist = dist1;
        oddDist = dist2;
    }
    Node(){}
    void print(){
        cout << "ID " << ID << " evendist " << evenDist <<
             " odddist " << oddDist << "\n";
    }

};

bool operator >(Node l,Node r){
    return min(l.getevenDist(), l.getoddDist()) > min(r.getevenDist(), r.getoddDist());
}

bool CustomCmp(Node& a, Node& b){
    return min(a.getevenDist(), a.getoddDist()) > min(b.getevenDist(), b.getoddDist());
}

template < typename T >
class PriorityQueue{
    private:
    vector < T > a;
    int size;

    public:
    PriorityQueue(){
        a.resize(1);
        size = 0;
    }
    void percolateUp(int cur){
        T ele = a[cur];
        while(cur >= 2 and CustomCmp(a[cur/2], ele)){   //a[cur/2] > a[cur]
            a[cur] = a[cur/2];
            cur = cur/2;
        }
        a[cur] = ele;
    }
    void percolateDown(int cur){
        T ele = a[cur];
        while(1){
            int child1 = 2 * cur;
            int child2 = 2 * cur + 1;
            if(child1 <= size and child2 <= size){
                if(!CustomCmp((a[child1], a[child2]), ele)){
                    if(!CustomCmp(a[child1], a[child2])){   //a[child1] < a[child2]
                        a[cur] = a[child1];
                        cur = child1;
                    }
                    else{
                        a[cur] = a[child2];
                        cur = child2;
                    }
                }
                else break;
            }
            else if(child1 <= size){
                if(!CustomCmp(a[child1], ele)){
                    a[cur] = a[child1];
                    cur = child1;
                }
                else break;
            }
            else break;
        }
        a[cur] = ele;
    }
    const size_t find_size(){
        return (size_t)size;
    }
    void push(const T& newele){
        size ++;
        if(a.size() < size + 1)a.resize(size + 1);
        a[size] = newele;
        percolateUp(size);
    }
    void pop(){
        a[1] = a[size];
        size --;
        // debug(size);
        if(size == 0)return;
        percolateDown(1);
    }
    T& top(){
        return a[1];
    }
    const bool empty(){
        return (size == 0)? true : false;
    }
    void print(){
        for(int i = 0 ; i < a.size() ;i ++){
            cout << a[i] << " ";
        }
        cout << "\n";
    }
};

void Dijkstra(vector < string >& a, map < string, vector < pair < string, int > > >& adj,
        string& src, string& des){

    PriorityQueue < Node > pq;
    // priority_queue < Node , vector < Node > , greater < Node > > pq;
    map < string , pair < int , int > > ans;
    map < pair < string , string > , int > vis;
    for(int i = 0 ; i < (int) a.size() ; i ++){
        ans[a[i]] = make_pair(INT_MAX, INT_MAX);
    }
    
    pq.push(Node(src, 0, INT_MAX));
    ans[src] = make_pair(0, INT_MAX);
    while(!pq.empty()){
    // for(int i = 0 ; i < 2 ; i ++){
        Node u = pq.top();
        pq.pop();
        // cout << pq.find_size() << "\n";
        int even = ans[u.getID()].F;
        int odd = ans[u.getID()].S;
        if(u.getevenDist() > even and u.getoddDist() > odd)continue;
        ans[u.getID()].F = min(even, u.getevenDist());
        ans[u.getID()].S = min(odd, u.getoddDist());
        for(auto& v : adj[u.getID()]){
            // if(!vis[make_pair(u.getID(),v.F)]){
            //     vis[make_pair(u.getID(),v.F)] = true;
                // vis[make_pair(v.F,u.getID())] = true;
                // Node(v.F, ans[u.getID()].S + v.S, ans[u.getID()].F + v.S).print();
            int new_even = min(ans[u.getID()].S + v.S, (int)INT_MAX);
            int new_odd = min(ans[u.getID()].F + v.S, (int)INT_MAX);
            int first = ans[v.F].F ;
            int second = ans[v.F].S;
            if (new_even < first || new_odd < second) {
                ans[v.F].F = min(first, new_even);
                ans[v.F].S = min(second, new_odd);
                pq.push(Node(v.F, ans[v.F].F, ans[v.F].S));
            }
            // }
        }
    }
    // for(auto& x: ans){
    //     cout << x.F << " " << x.S.F << " " << x.S.S << "\n";
    // }
    if(ans[des].F != INT_MAX)cout << ans[des].F << "\n";
    else cout << "-1\n";
}


int32_t main(){
    int n, m; cin >> n >> m;
    vector < string > a(n);
    for(int i = 0; i < n ; i ++)cin >> a[i];
    map < string, vector < pair < string, int > > > adj;
    while(m --){
        string u, v; cin >> u >> v;
        int dist; cin >> dist;
        adj[u].push_back(make_pair(v,dist));
        adj[v].push_back(make_pair(u,dist));
    }
    string src, des; cin >> src >> des;
    Dijkstra(a, adj, src, des);
    
}
