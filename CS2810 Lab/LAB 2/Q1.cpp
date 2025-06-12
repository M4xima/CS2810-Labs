#include <bits/stdc++.h>
using namespace std;

class Graph{

    private:
    int n;
    vector < set < int > > adj;
    
    public:
    set < int >& getSet(int i){
        return adj[i];
    }
    int& no_of_vertices(){
        return n;
    }
    vector < set < int > >& getVector(){
        return adj;
    }
    Graph(int n1,vector < set < int > > adj1){
        n = n1;
        adj = adj1;
    }
    Graph(){ }
    Graph operator +(Graph& G2){
        int N = max(n,G2.no_of_vertices());
        vector < set < int > > temp(N);
        for(int i=0;i<n;i++){
            for(auto x:adj[i]){
                temp[i].insert(x);
            }
        }
        for(int i=0;i<G2.no_of_vertices();i++){
            for(auto x:G2.getSet(i)){
                temp[i].insert(x);
            }
        }
        return Graph(N,temp);
    }
    Graph operator -(Graph& G2){
        int N = max(n,G2.no_of_vertices());
        vector < set < int > > temp(N);
        for(int i=0;i<G2.no_of_vertices();i++){
            for(auto x:G2.getSet(i)){
                if(adj[i].find(x)!=adj[i].end()){
                    temp[i].insert(x);
                }
            }
        }
        return Graph(N,temp);
    }
    Graph operator !(){
        vector < set < int > > temp(n);
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(adj[i].find(j)==adj[i].end() and i!=j){
                    temp[i].insert(j);
                }
            }
        }
        return Graph(n,temp);
    }
    bool dfs(int node,int target,vector < int > &vis){
        vis[node] = 1;
        if(node==target)return true;
        bool a = 0;
        for(auto child:adj[node]){
            if(vis[child]!=1){
                a|=dfs(child,target,vis);
            }
        }
        return a;
    }
    bool isReachable(int u,int v){
        vector < int > vis(n);
        return dfs(u,v,vis);
    }
    void add_edge(int i,int j){
        adj[i].insert(j);
        adj[j].insert(i);
    }
    void remove_edge(int i,int j){
        adj[i].erase(j);
        adj[j].erase(i);
    }
    void print(){
        for(int i=0;i<n;i++){
            cout<<"Vertex "<<i<<": ";
            for(auto x:adj[i])cout<<x<<" ";
            cout<<"\n";
        }
    }

    friend istream& operator >> (istream& stream,Graph& G);

};

ostream& operator << (ostream& stream, Graph& G){
    G.print();
    return stream;
}

istream& operator >> (istream& stream,Graph& G){
    int n,m;
    stream>>n>>m;
    G.getVector().resize(n);
    G.no_of_vertices() = n;
    // set < int > s1;
    // for(int i=0;i<n;i++)G.getVector().push_back(s1);
    while(m--){
        int i,j; cin>>i>>j;
        G.getVector()[i].insert(j);
        G.getVector()[j].insert(i);
    }
    return stream;
}

int main(){
    string s; cin>>s;
    Graph g; cin>>g;
    cin>>s;
    while(s!="end"){
        if(s=="union"){
            string t; cin>>t;
            Graph g1; cin>>g1;
            g = g+g1;
        }
        else if(s=="intersection"){
            string t; cin>>t;
            Graph g1; cin>>g1;
            g = g-g1;
        }
        else if(s=="complement"){
            g = !g;
        }
        else if(s=="isReachable"){
            int u,v; cin>>u>>v;
            if(g.isReachable(u,v))cout<<"Yes\n";
            else cout<<"No\n";
        }
        else if(s=="add_edge"){
            int u,v; cin>>u>>v;
            g.add_edge(u,v);
        }
        else if(s=="remove_edge"){
            int u,v; cin>>u>>v;
            g.remove_edge(u,v);
        }
        else if(s=="printGraph"){
            cout<<g;
        }
        cin>>s;
    }
}



