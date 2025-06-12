#include <bits/stdc++.h>
using namespace std;

#define int long long
#define F first
#define S second
const int SIZE = 100005;

class Card{
    private:
    int height;
    int base;
    string s;
    int area;
    Card* par;

    public:
    Card(){
        par = NULL;
    }
    Card(int x){
        area = x;
        par = NULL;
    }
    int getarea(){return area;}
    string getS(){return s;}
    int getheight(){return height;}
    int getbase(){return base;}
    Card* getpar(){return par;}
    void setheight(int x){ height = x;}
    void setbase(int x){ base = x;}
    void setarea(int x){area = x;}
    void setS(string s1){s = s1;}
    void setpar(Card* par1){par = par1;}
};

ostream& operator << (ostream& stream, Card& card){
    if(card.getS() == "TRIANGLE" or card.getS() == "RECTANGLE"){
        cout << card.getS() << " " << card.getheight() << " " << card.getbase() << "\n";
    }
    else{
        cout << card.getS() << " " << card.getheight() << "\n";
    }
    return stream;
}

istream& operator >> (istream& stream,Card& card){
    string s1; cin >> s1;
    card.setS(s1);
    if(s1 == "TRIANGLE"){
        int h, b; cin >> h >> b;
        card.setheight(h);
        card.setbase(b);
        card.setarea((h * b) / 2);
    }
    else if(s1 == "SQUARE"){
        int s; cin >> s;
        card.setheight(s);
        card.setbase(s);
        card.setarea(s * s);
    }
    else{
        int h, b; cin >> h >> b;
        card.setheight(h);
        card.setbase(b);
        card.setarea(h * b);
    }
    return stream;
}

class Triangle : public Card{
    public:
    Triangle():Card(){}
};
class Square : public Card{
    public:
    Square():Card(){}
};

class Rectangle : public Card{
    public:
    Rectangle():Card(){}
};

// bool operator < (Card* l, Card* r){
//     return l->getarea() < r->getarea();
// }

bool cmp(Card* l, Card* r){
    return l->getarea() >= r->getarea();
}

class CardOrganizer{
    private:
    set < int > s;
    vector < Card* > dp;
    int ans;

    public:
    CardOrganizer(){
        Card* abc1 = new Card(INT64_MAX);
        dp.resize(SIZE,abc1);
        Card* abc2 = new Card(0);
        dp[0] = abc2;
        ans = 0;
    }
    void addCard(Card* card){
        //FOR TYPE 2
        int a = card->getarea();
        auto idx = s.lower_bound(a);
        if(idx != s.end()){
            s.erase(*idx);
        }
        s.insert(a);
        //FOR TYPE 3
        // int idx1 = lower_bound(dp.begin(), dp.end(), *card) - dp.begin() - 1;
        //BINARY SEARCH FOR LOWER BOUND
        int l = 0, r = 100004;
        while(l < r){
            int mid = (l + r) / 2;
            if(cmp(dp[mid], card)){
                r = mid;
            }
            else{
                l = mid + 1;
            }
        }
        int idx1 = l - 1;
        dp[idx1 + 1LL] = card;
        card -> setpar(dp[idx1]);
        ans = max(ans, idx1 + 1);
    }
    size_t getPileCount() const{
        return s.size();
    }
    void getLIS() {
        // for(auto& x: Cards){
        //     cout << x.S;
        // }
        Card* temp = dp[ans];
        vector < Card > v;
        while(temp -> getpar() != NULL){
            v.push_back(*temp);
            temp = temp -> getpar();
        }
        cout << ans << "\n";
        for(int i = v.size() - 1 ; i >= 0 ; i --){
            cout << v[i];
        }
    }
};

int32_t main(){
    CardOrganizer deck;
    int q; cin >> q;
    while(q --){
        int type; cin >> type;
        if(type == 1){
            Card* card = new Card();
            cin >> *card;
            deck.addCard(card);
        }
        else if(type == 2){
            cout << deck.getPileCount() << "\n";
        }
        else{
            deck.getLIS();
        }
    }
}
