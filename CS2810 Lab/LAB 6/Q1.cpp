#include <bits/stdc++.h>
using namespace std;

#define F first 
#define S second
int t = 0;
#ifdef IOS
#include "debug.h" 
#else
#define debug(...)
#endif

bool magic(pair < int , int >& l, pair < int , int >& r){
    return l.F > r.F;
}

class GraphAlgorithm{
    public:
    virtual void Query(){}
    GraphAlgorithm(vector < int >& hypescore1, vector < vector < int > >& adj1){
        hypescore = hypescore1;
        adj = adj1;
    }

    protected:
    int len;
    vector < int > hypescore;
    vector < vector < int > > adj;
};
class isCycle : public GraphAlgorithm{
    public:
    isCycle(vector < int >& hypescore1, vector < vector < int > >& adj1
        ):GraphAlgorithm(hypescore1, adj1){}
    void Query(){
        int n = adj.size();
        vector < int > vis(n);
        for(int i = 0; i < n; i ++){
            if(vis[i] == 0 and dfs(i,vis)){
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
    }
    bool dfs(int u, vector < int >& vis){
        vis[u] = 2;
        bool a = 0;
        for(int i = 0; i < adj[u].size(); i ++){
            if(vis[adj[u][i]] == 2){
                vis[u] = 1;
                return true;
            }    
            if(vis[adj[u][i]] == 0)a |= dfs(adj[u][i], vis);
        }
        vis[u] = 1;
        return a;
    }
};
class indepComponent : public GraphAlgorithm{
    private:
    vector < vector < int > > adjT;
    public:
    indepComponent(vector < int >& hypescore1, vector < vector < int > >& adj1, 
        vector < vector < int > >& adjT1):GraphAlgorithm(hypescore1, adj1){
        adjT = adjT1;
    }
    vector < int > topoSort(){
        int n = adj.size();
        vector < pair < int , int > > f(n);
        vector < int > vis(n);
        t = 0;
        for(int i = 0; i < n; i++){
            if(!vis[i])dfs1(i, vis, f);
        }
        for(int i = 0 ; i < n ; i ++){
            f[i].S = i;
        }
        vector < int > v(n);
        sort(f.begin(), f.end(), magic);
        for(int i = 0 ; i < n ; i ++){
            v[i] = f[i].S;
        }
        return v;
    }
    void dfs1(int u, vector < int >& vis, vector < pair < int , int > >& f){
        t++;
        vis[u] = 1;
        for(int i = 0; i < adj[u].size(); i ++){
            if(!vis[adj[u][i]])dfs1(adj[u][i], vis, f);
        }
        t++;
        f[u].F = t;
    }
    int dfs2(int u, vector < int >& vis){
        vis[u] = 1;
        int sum = 1;
        for(int i = 0; i < adjT[u].size(); i ++){
            if(!vis[adjT[u][i]])sum += dfs2(adjT[u][i], vis);
        }
        return sum;
    }
    void Query(){
        vector < int > v = topoSort();
        int n = v.size();
        vector < int > vis(n);
        int x = 0, maxSum = 0;
        for(int i = 0 ; i < n; i ++){
            if(!vis[v[i]]){
                x++;
                maxSum = max(maxSum, dfs2(v[i], vis));
            }    
        }
        cout << x << " " << maxSum << "\n";
    }
};
class validOrder : public GraphAlgorithm{
    public:
    validOrder(vector < int >& hypescore1, vector < vector < int > >& adj1
        ):GraphAlgorithm(hypescore1, adj1){}
    bool cycle(){
        int n = adj.size();
        vector < int > vis(n);
        for(int i = 0; i < n; i ++){
            if(vis[i] == 0 and dfs(i,vis)){
                return true;
            }
        }
        return false;
    }
    bool dfs(int u, vector < int >& vis){
        vis[u] = 2;
        bool a = 0;
        for(int i = 0; i < adj[u].size(); i ++){
            if(vis[adj[u][i]] == 2){
                vis[u] = 1;
                return true;
            }    
            if(vis[adj[u][i]] == 0)a |= dfs(adj[u][i], vis);
        }
        vis[u] = 1;
        return a;
    }
    void Query(){
        if(cycle()){
            cout << "NO\n";
            return;
        }
        int n = adj.size();
        vector < int > indeg(n);
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ; j < adj[i].size() ; j ++){
                indeg[adj[i][j]]++;
            }
        }
        map < int , int > mp;
        for(int i = 0 ; i < n ; i ++){
            if(indeg[i] == 0)mp[i] = 1;
        }
        while(!mp.empty()){
            int u = mp.begin()->F;
            for(int j = 0 ; j < adj[u].size() ; j ++){
                int v = adj[u][j];
                indeg[v]--;
                if(indeg[v] == 0)mp[v] = 1;
            }
            mp.erase(u);
            cout << u + 1 << " ";
        }
        cout << "\n";
    }
};
class maxHype : public GraphAlgorithm{
    private:
    vector < vector < int > > adjT;
    public:
    maxHype(vector < int >& hypescore1, vector < vector < int > >& adj1, 
        vector < vector < int > >& adjT1):GraphAlgorithm(hypescore1, adj1){
        adjT = adjT1;
    }
    vector < int > topoSort(){
        int n = adj.size();
        vector < pair < int , int > > f(n);
        vector < int > vis(n);
        t = 0;
        for(int i = 0; i < n; i++){
            if(!vis[i])dfs1(i, vis, f);
        }
        for(int i = 0 ; i < n ; i ++){
            f[i].S = i;
        }
        vector < int > v(n);
        sort(f.begin(), f.end(), magic);
        for(int i = 0 ; i < n ; i ++){
            v[i] = f[i].S;
        }
        return v;
    }
    void dfs1(int u, vector < int >& vis, vector < pair < int , int > >& f){
        t++;
        vis[u] = 1;
        for(int i = 0; i < adj[u].size(); i ++){
            if(!vis[adj[u][i]])dfs1(adj[u][i], vis, f);
        }
        t++;
        f[u].F = t;
    }
    int dfs2(int u, vector < int >& vis, int j, vector < int >& a){
        vis[u] = 1;
        a[u] = j;
        int x = hypescore[u];
        for(int i = 0; i < adjT[u].size(); i ++){
            if(!vis[adjT[u][i]]){
                x += dfs2(adjT[u][i], vis, j, a);
            }    
        }
        return x;
    }
    int dfs3(int u, vector < int >& sum, vector < int >& vis, vector < set < int > >& adjnew){
        vis[u] = true;
        int N = adjnew.size();
        int temp = 0;
        for(auto& x: adjnew[u]){
            if(!vis[x]){
                temp = max(temp, dfs3(x,sum,vis,adjnew));
            }
        }
        return temp + sum[u];
    }
    void Query(){
        vector < int > v = topoSort();
        int n = v.size();
        // debug(v);
        vector < int > vis(n),a(n),sum(n);
        int N = 0;
        for(int i = 0 ; i < n; i ++){
            if(!vis[v[i]]){
                sum[N] = dfs2(v[i], vis, N, a);
                N ++;
            }    
        }
        // debug(a);
        // debug(sum);
        // debug(N);
        vector < set < int > > adjnew(N);
        for(int i = 0 ; i < n ; i ++){
            for(int j = 0 ;j < adj[i].size() ; j ++){
                if(a[i] != a[adj[i][j]]){
                    adjnew[a[i]].insert(a[adj[i][j]]);
                }
            }
        }
        // debug(adjnew);
        vector < int > indeg(N);
        for(int i = 0 ; i < N ; i ++){
            for(auto& x : adjnew[i]){
                indeg[x] ++;
            }
        }

        int maxi = 0;
        for(int i = 0 ; i < N ; i ++){
            vis.clear();
            vis.resize(N);
            if(indeg[i] == 0){
                maxi = max(maxi, dfs3(i, sum, vis, adjnew));
            }
        }
        cout << maxi << "\n";
    }
};

int main(){
    int n, m; cin >> n >> m;
    vector < int > hypescore(n);
    vector < vector < int > > adj(n),adjT(n);
    for(int i = 0; i < n ; i ++){
        cin >> hypescore[i];
    }
    while(m --){
        int u, v; cin >> u >> v;
        adj[u - 1].push_back(v - 1);
        adjT[v - 1].push_back(u - 1);
    }
    isCycle obj1(hypescore, adj);
    indepComponent obj2(hypescore, adj, adjT);
    validOrder obj3(hypescore, adj);
    maxHype obj4(hypescore, adj, adjT);
    int q; cin >> q;
    GraphAlgorithm* graph;
    while(q --){
        int type; cin >> type;
        if(type == 1){
            graph = &obj1;
            graph->Query();
        }
        else if(type == 2){
            graph = &obj2;
            graph->Query();
        }
        else if(type == 3){
            graph = &obj3;
            graph->Query();
        }
        else{
            graph = &obj4;
            graph->Query();
        }
    }
}
