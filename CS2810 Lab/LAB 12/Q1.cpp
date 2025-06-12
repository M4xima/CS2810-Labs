#include <bits/stdc++.h>
using namespace std;

class Event{
    protected:
    int type;
    int startTime;
    int endTime;
    double profit;

    public:
    int getStart(){
        return startTime;
    }
    int getEnd(){
        return endTime;
    }
    void setStart(int t){
        startTime = t;
    }
    void setEnd(int t){
        endTime = t;
    }
    int getType(){
        return type;
    }
    Event(){}
    Event(int t){
        type = t;
    }
    double getprofit(){
        return profit;
    }
    void setprofit(double p){
        profit = p;
    }
    virtual double calculateProfit(){
        return 0;
    }
    friend istream& operator >> (istream& stream,Event& event);
};


class Concert : public Event{
    private:
    int TicketPrice;
    int TicketsSold;
    int ArtisteFee;
    int LogisticCost;

    public:
    Concert():Event(1){}
    double calculateProfit(){
        double TicketRevenue = (TicketPrice * TicketsSold);
        TicketRevenue = TicketRevenue - 0.18* TicketRevenue;
        double cost = LogisticCost + ArtisteFee;
        double profit = TicketRevenue - cost;
        double NetProfit = (profit > 2 * cost) ? 0.7 * profit : profit;
        return NetProfit;
    }
    int getTicketPrice(){
        return TicketPrice;
    }
    int getTicketsSold(){
        return TicketsSold;
    }
    int getArtisteFee(){
        return ArtisteFee;
    }
    int getLogisticCost(){
        return LogisticCost;
    }
    void setTicketPrice(int TicketPrice1){
        TicketPrice = TicketPrice1;
    }
    void setTicketsSold(int TicketsSold1){
        TicketsSold = TicketsSold1;
    }
    void setArtisteFee(int ArtisteFee1){
        ArtisteFee = ArtisteFee1;
    }
    void setLogisticCost(int LogisticCost1){
        LogisticCost = LogisticCost1;
    }
    friend istream& operator >> (istream& stream,Concert& concert);
};
istream& operator >> (istream& stream,Concert& concert){
    int startTime1, endTime1;
    cin >> startTime1 >> endTime1;
    concert.setStart(startTime1);
    concert.setEnd(endTime1);
    int TicketPrice, TicketsSold, ArtisteFee, LogisticCost;
    cin >> TicketPrice >> TicketsSold >> ArtisteFee >> LogisticCost;
    concert.setTicketPrice(TicketPrice);
    concert.setTicketsSold(TicketsSold);
    concert.setArtisteFee(ArtisteFee);
    concert.setLogisticCost(LogisticCost);
    concert.setprofit(concert.calculateProfit());
    // cout << concert.getprofit();
    return stream;
}
class TheaterShow: public Event{
    private:
    int BaseTicketPrice;
    int TotalSeats;
    int VenueCost;

    public:
    TheaterShow():Event(2){}
    double calculateProfit(){
        double TicketRevenue = 0.25 * TotalSeats * (2 * BaseTicketPrice) + 0.75 * TotalSeats * BaseTicketPrice;
        TicketRevenue = TicketRevenue - 0.18 * TicketRevenue;
        double PopcornPrice = 150;
        double PopcornRevenue = 0.25 * TotalSeats * PopcornPrice;
        double NetProfit = TicketRevenue + PopcornRevenue - VenueCost;
        // profit = NetProfit;
        return NetProfit;
    }
    int getBaseTicketPrice(){
        return BaseTicketPrice;
    }
    int getTotalSeats(){
        return TotalSeats;
    }
    int getVenueCost(){
        return VenueCost;
    }
    void setBaseTicketPrice(int BaseTicketPrice1){
        BaseTicketPrice = BaseTicketPrice1;
    }
    void setTotalSeats(int TotalSeats1){
        TotalSeats = TotalSeats1;
    }
    void setVenueCost(int VenueCost1){
        VenueCost = VenueCost1;
    }
};
istream& operator >> (istream& stream,TheaterShow& theatershow){
    int startTime1, endTime1;
    cin >> startTime1 >> endTime1;
    theatershow.setStart(startTime1);
    theatershow.setEnd(endTime1);
    int BasePrice, TotalSeats, VenueCost;
    cin >> BasePrice >> TotalSeats >> VenueCost;
    theatershow.setBaseTicketPrice(BasePrice);
    theatershow.setTotalSeats(TotalSeats);
    theatershow.setVenueCost(VenueCost);
    theatershow.setprofit(theatershow.calculateProfit());
    return stream;
}
class Wedding : public Event{
    private:
    int BaseAmount;
    int DecorationCost;
    int GuestCount;
    int VenueCost;

    public:
    Wedding():Event(3){}
    double calculateProfit(){
        double TotalVenueCost = (GuestCount > 200) ? VenueCost*3 : VenueCost;
        double CateringCost =  (GuestCount > 100) ? GuestCount * 70 :  GuestCount * 100;
        double NetProfit = BaseAmount - TotalVenueCost - DecorationCost -  CateringCost;
        return NetProfit;
    }
    void setBaseAmount(int BaseAmount1){
        BaseAmount = BaseAmount1;
    }
    void setDecorationCost(int DecorationCost1){
        DecorationCost = DecorationCost1;
    }
    void setGuestCount(int GuestCount1){
        GuestCount = GuestCount1;
    }
    void setVenueCost(int VenueCost1){
        VenueCost = VenueCost1;
    }
};
istream& operator >> (istream& stream,Wedding& wedding){
    int startTime1, endTime1;
    cin >> startTime1 >> endTime1;
    wedding.setStart(startTime1);
    wedding.setEnd(endTime1);
    int BaseAmount, DecorationCost, GuestCount, VenueCost;
    cin >> BaseAmount >> DecorationCost >> GuestCount >> VenueCost;
    wedding.setBaseAmount(BaseAmount);
    wedding.setDecorationCost(DecorationCost);
    wedding.setGuestCount(GuestCount);
    wedding.setVenueCost(VenueCost);
    wedding.setprofit(wedding.calculateProfit());
    return stream;
}

bool magic(Event* L, Event* R){
    return L->getEnd() < R->getEnd();
}
bool operator < (Event L, Event R){
    return L.getEnd() < R.getEnd();
}
class EventScheduler{
    private:
    vector < Event > events;
    vector < double > dp;

    public:
    EventScheduler(vector < Event > events1){
        events = events1;
        int n = events.size();
        sort(events.begin(), events.end());
        dp.resize(events.size());
    }
    void maxProfit(){
        int n = events.size();
        dp[0] = events[0].getprofit();
        // for(int i = 0 ; i < n ; i ++){
        //     cout << events[i].getprofit() << " ";
        // }
        // cout << "\n";
        // for(int i = 0 ; i < n ; i ++){
        //     cout << events[i].getStart() << " ";
        // }
        // cout << "\n";
        // for(int i = 0 ; i < n ; i ++){
        //     cout << events[i].getEnd() << " ";
        // }
        // cout << "\n";
        Event temp;
        for(int i = 1 ; i < n ; i ++){
            temp.setEnd(events[i].getStart());
            int idx = upper_bound(events.begin(), events.end(),temp) - events.begin() - 1;
            if(idx != -1)dp[i] = max(dp[i - 1], dp[idx] + events[i].getprofit());
            else dp[i] = max(dp[i - 1], events[i].getprofit());
        }
        cout << fixed << setprecision(2) << dp[n - 1] << "\n";

    }
};
int main(){
    int n; cin >> n;
    vector < Event > events;
    for(int i = 0 ; i < n ; i ++){
        int type; cin >> type;
        if(type == 1){
            Concert* concert = new Concert();
            cin >> *concert;
            Event* e = concert;
            events.push_back(*e);
        }
        else if(type == 2){
            TheaterShow* theatershow = new TheaterShow();
            cin >> *theatershow;
            Event* e = theatershow;
            events.push_back(*e);
        }
        else{
            Wedding* wedding = new Wedding();
            cin >> *wedding;
            Event* e = wedding;
            events.push_back(*e);
        }
    }
    EventScheduler eventScheduler1(events);
    eventScheduler1.maxProfit();
}


