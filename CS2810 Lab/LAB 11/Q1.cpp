#include <bits/stdc++.h>
using namespace std;

#define int long long
#define F first
#define S second

long double dist(int x1, int y1, int x2, int y2){
    return sqrtl((x1 -x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

class Island{
    private:
    int x;
    int y;
    long double r;
    string ID;

    public:
    Island(){}
    Island(int x1, int y1, long double radius, string ID1){
        x = x1;
        y = y1;
        r = radius;
        ID = ID1;
    }
    int getx(){
        return x;
    }
    void setx(int x1){
        x = x1;
    }
    int gety(){
        return y;
    }
    void sety(int y1){
        y = y1;
    }
    long double getr(){
        return r;
    }
    void setr(long double r1){
        r = r1;
    }
    string getID(){
        return ID;
    }
    void setID(string ID1){
        ID = ID1;
    }
    friend ostream& operator << (ostream& stream, Island& island);
    friend istream& operator >> (istream& stream, Island& island);
};

ostream& operator << (ostream& stream, Island& island){
    stream << island.getID();
    return stream;
}

istream& operator >> (istream& stream, Island& island){
    string s; cin >> s;
    if(s == "RECTANGLE"){
        string ID; cin >> ID;
        island.setID(ID);
        int x1, y1, x2, y2, x3, y3, x4, y4;
        stream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        island.setx((x1 + x2 + x3 + x4)/4);
        island.sety((y1 + y2 + y3 + y4)/4);
        island.setr(dist(island.getx(), island.gety(), x1, y1));
    }
    else if(s == "TRIANGLE"){
        string ID; stream >> ID;
        island.setID(ID);
        int x1, y1, x2, y2, x3, y3;
        stream >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        island.setx((x1 + x2 + x3)/3);
        island.sety((y1 + y2 + y3)/3);
        long double max_dist = 0; int x = island.getx(); int y = island.gety();
        max_dist = max(max_dist, dist(x, y, x1, y1));
        max_dist = max(max_dist, dist(x, y, x2, y2));
        max_dist = max(max_dist, dist(x, y, x3, y3));
        island.setr(max_dist);
    }
    else{
        string ID; stream >> ID;
        island.setID(ID);
        int x, y, r;
        stream >> x >> y >> r;
        island.setx(x);
        island.sety(y);
        island.setr(r);
    }
    return stream;
}

class Rectangle : public Island{
    public:
    Rectangle():Island(){}
};

class Triangle : public Island{
    public:
    Triangle():Island(){}
};

class Circle : public Island{
    public:
    Circle():Island(){}
};

class Graph{
    private:
    vector < vector < int > > adj;
    vector < Island* > islands;

    public:
    Graph(){}
    Graph(vector < vector < int > >& adj1, vector < Island* >& islands1){
        adj = adj1;
        islands = islands1;
    }
    void discoverIslands(){
        int n = adj.size();
        vector < vector < int > > dp (n, vector < int > (1 << n, -1));
        vector < vector < int > > parent (n, vector < int > (1 << n, -1));

        for(int i = 0 ; i < n ; i ++){
            dp[i][(1 << i)] = 1;
            parent[i][(1 << i)] = -1;
        }

        for(int mask = 0 ; mask < (1 << n) ; mask++){
            for(int j = 0 ; j < n ; j++){
                if(mask & (1 << j)){
                    for(int k = 0 ; k < n ; k++){
                        if(k != j && (mask & (1 << k)) && adj[k][j]
                            && dp[k][mask ^ (1 << j)] != -1){
                            if(dp[k][mask ^ (1 << j)] + 1 > dp[j][mask]){
                                dp[j][mask] = dp[k][mask ^ (1 << j)] + 1;
                                parent[j][mask] = k;
                            }
                        }
                    }
                }
            }
        }

        vector < int > path;
        int last = -1, final_mask = (1 << n) - 1;

        for(int j = 0 ; j < n ; j ++){
            if(dp[j][final_mask] == n){
                last = j;
                break;
            }
        }

        if(last != -1){
            cout << "YES\n";
            int mask = final_mask;
            while(last != -1){
                path.push_back(last);
                int temp = parent[last][mask];
                mask ^= (1 << last);
                last = temp;
            }
        } else {
            cout << "NO\n";
            int maxlen = 0, best_mask = 0;
            for(int mask = 0; mask < (1 << n); mask++){
                for(int j = 0; j < n; j++){
                    if(dp[j][mask] > maxlen){
                        maxlen = dp[j][mask];
                        last = j;
                        best_mask = mask;
                    }
                }
            }
            int mask = best_mask;
            while(last != -1){
                path.push_back(last);
                int temp = parent[last][mask];
                mask ^= (1 << last);
                last = temp;
            }
            cout << path.size() << "\n";
        }

        reverse(path.begin(), path.end());

        for(int i = path.size() - 1; i >= 0 ; i--){
            cout << *islands[path[i]] << " ";
        }
        cout << "\n";
    }

    friend class Island;


};


int32_t main(){
    int n; cin >> n;
    vector < Island* > islands(n);
    for(int i = 0 ; i < n ; i ++){
        Island* island = new Island();
        cin >> *island;
        islands[i] = island;
    }

    vector < vector < int > > adj(n, vector < int > (n));
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < i ; j ++){
            long double distance = dist(islands[i]->getx(), islands[i]->gety(),
                                islands[j]->getx(), islands[j]->gety());
            if(distance <= islands[i]->getr() + islands[j]->getr()){
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
    }
    Graph g(adj, islands);
    g.discoverIslands();
}
