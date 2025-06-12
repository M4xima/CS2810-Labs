#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second

int S = 0, D = 0;
class Sentinel{
    private:
    int id;
    string name;
    string rank;

    public:
    Sentinel(int id1, string& name1, string& rank1){
        id = id1;
        name = name1;
        rank = rank1;
    }
    int getid(){
        return id;
    }
    string getrank(){
        return rank;
    }
    Sentinel(){}
    virtual int countHigherRanked(){
        return 1;
    }
};

class Senapati : public Sentinel{
    public:
    Senapati(){}
    int countHigherRanked(){
        return 0;
    }
};
class Dandanayaka : public Sentinel{
    public:
    Dandanayaka(){}
    int countHigherRanked(){
        return S;
    }
};
class Chaturangini : public Sentinel{
    public:
    Chaturangini(){}
    int countHigherRanked(){
        return S + D;
    }
};

template < typename T >
bool magic(T a, T b){
    if(a.getrank() != b.getrank())return a.getrank() > b.getrank();
    else return a.getid() < b.getid();
}

template < typename T >
bool operator < (T a, T b){
    if(a.getrank() != b.getrank())return a.getrank() > b.getrank();
    else return a.getid() < b.getid();
}

template < typename T >
class Kingdom{
    private:
    vector < vector < int > > adj;
    vector < T > nodes;
    vector < string > ranks;
    vector < pair < int , int > > dp;

    public:
    Kingdom(){}
    Kingdom(vector < vector < int > >& adj1, vector < string >& ranks1, vector < Sentinel >& nodes1){
        adj = adj1;
        ranks = ranks1;
        nodes = nodes1;
        dp.resize(ranks.size(), make_pair(0, 1));
        //for type 1
        vector < int > vis(ranks.size());
        dfs(0, vis);
        //for type 2
        sort(nodes.begin(), nodes.end());
        //for type 3
        for(int i = 0 ; i < ranks.size(); i ++){
            if(ranks[i] == "SENAPATI")S++;
            else if(ranks[i] == "DANDANAYAKA")D++;
        }
    }
    int min_active_sentinels(){
        return min(dp[0].F, dp[0].S);
    }
    pair < int , int > dfs(int u, vector < int >& vis){
        vis[u] = true;
        dp[u].F = 0;
        dp[u].S = 1;
        for(int i = 0 ; i < adj[u].size() ; i ++){
            int v = adj[u][i];
            if(!vis[v]){
                pair < int , int > child = dfs(v, vis);
                dp[u].F += child.S;
                dp[u].S += min(child.S, child.F);
            }
        }
        return dp[u];
    }
    void print(){
        for(int i  = 0; i < nodes.size() ; i ++){
            cout << nodes[i].getid() << " ";
        }
        cout << "\n";
    }
    int number_of_sentinels(int x){
        if(ranks[x] == "SENAPATI")return 0;
        else if(ranks[x] == "DANDANAYAKA")return S;
        else return S + D;
    }
};

int32_t main(){
    int n; cin >> n;
    vector < vector < int > > adj(n);
    vector < string > ranks(n);
    vector < Sentinel > nodes(n);
    for(int i = 0; i < n - 1; i ++){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for(int i = 0; i < n; i ++){
        string name; cin >> name;
        string rank; cin >> rank;
        ranks[i] = rank;
        nodes[i] = Sentinel(i, name, rank);
    }
    Kingdom < Sentinel > kgd(adj, ranks, nodes);
    int q; cin >> q;
    while(q --){
        int type; cin >> type;
        if(type == 1){
            cout << kgd.min_active_sentinels() << "\n";
        }
        else if(type == 2){
            kgd.print();
        }
        else{
            int x; cin >> x;
            cout << kgd.number_of_sentinels(x) << "\n";
        }
    }
}
