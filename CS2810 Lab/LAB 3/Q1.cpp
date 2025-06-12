#include <bits/stdc++.h>
using namespace std;

class QNS{
    private:
    int powerLevel;
    int durability;
    int energyStorage;
    int heatLevel;

    public:
    int& getPower(){
        return powerLevel;
    }
    int& getDurability(){
        return durability;
    }
    int& getEnergy(){
        return energyStorage;
    }
    int& getHeatLevel(){
        return heatLevel;
    }

    QNS(){
        powerLevel = 1000;
        durability = 500;
        energyStorage = 300;
        heatLevel = 0;
    }
    QNS(int powerLevel1, int durability1, int energyStorage1,int heatLevel1){
        powerLevel = powerLevel1;
        durability = durability1;
        energyStorage = energyStorage1;
        heatLevel = heatLevel1;
    }
    QNS(const QNS& Q1){
        powerLevel = Q1.powerLevel;
        durability = Q1.durability;
        energyStorage = Q1.energyStorage;
        heatLevel = Q1.heatLevel;
    }

    QNS& operator +(QNS& Q1){
        powerLevel+=Q1.energyStorage;
        durability+=Q1.durability;
        energyStorage+=Q1.powerLevel;
        powerLevel = min(5000,powerLevel);
        return *this;
    }
    QNS& operator -(int x){
        durability-=x;
        energyStorage+=x;
        heatLevel+=x;
        return *this;
    }
    QNS& operator *(int x){
        powerLevel+=(powerLevel*x)/100;
        energyStorage+=5*x;
        heatLevel+=x;
        powerLevel = min(5000,powerLevel);
        return *this;
    }
    QNS& operator /(int x){
        durability+=x;
        heatLevel-=x;
        heatLevel = max(heatLevel,0);
        return *this;
    }
    void boostPower(int factor){
        *this * factor;
    }
    void boostPower(QNS otherSuit){
        *this + otherSuit;
    }
    bool operator ==(QNS& Q2){
        if(powerLevel==Q2.powerLevel and durability==Q2.durability)return true;
        return false;
    }
    bool operator <(QNS& Q2){
        if(powerLevel+durability < Q2.powerLevel+Q2.durability)return true;
        else return false;
    }
};

class Avenger{
    private:
    string name;
    QNS suit;
    int attackStrength;

    public:
    QNS& getQNS(){
        return suit;
    }
    string& getName(){
        return name;
    }
    int& getAttackStrength(){
        return attackStrength;
    }
    Avenger(string avName, QNS avSuit, int strength){
        name = avName;
        suit = avSuit;
        attackStrength = strength;
    }
    void attack(Avenger& enemy){
        enemy.suit - attackStrength;
    }
    void upgradeSuit(QNS& newSuit){
        suit + newSuit;
    }
    void repair(int x){
        suit / x;
    }
    void printStatus(){
        cout<<name<<" "<<suit.getPower()<<" "<<suit.getDurability()<<" "<<suit.getEnergy()<<" "<<suit.getHeatLevel()<<"\n";
    }

};

class Battle{
    private:
    int k,n,m;
    vector < Avenger > heroes;
    vector < Avenger > enemies;
    vector < string > battleLog;
    vector < QNS > suits;
    int idx;

    public:
    void debug(){
        cout<<"heroes:\n";
        for(int i=0;i<(int)heroes.size();i++){
            heroes[i].printStatus();
        }
        cout<<"enemies:\n";
        for(int i=0;i<(int)enemies.size();i++){
            enemies[i].printStatus();
        }
    }
    void startBattle(){
        cin>>k>>n>>m;
        for(int i=0;i<k;i++){
            int P,D,E,H; cin>>P>>D>>E>>H;
            P = min(P,5000);
            QNS suit1(P,D,E,H);
            suits.push_back(suit1);
        }
        idx = 0;
        int i = 0;
        for(;i<n and idx<k;i++,idx++){
            string name;
            int strength; cin>>name>>strength;
            Avenger* A = new Avenger(name,suits[idx],strength);
            heroes.push_back(*A);
        }
        for(;i<n;i++){
            string name;
            int strength; cin>>name>>strength;
            cout<<name<<" is out of fight\n";
        }
        int j = 0;
        for(;j<m and idx<k;j++,idx++){
            string name;
            int strength; cin>>name>>strength;
            Avenger A(name,suits[idx],strength);
            enemies.push_back(A);
        }
        for(;j<m;j++){
            string name;
            int strength; cin>>name>>strength;
            cout<<name<<" is out of fight\n";
        }
    }
    void printBattleLog(){
        for(int i=0;i<(int)battleLog.size();i++){
            cout<<battleLog[i]<<"\n";
        }
    }
    Avenger& getAveneger(string name){
        for(int i=0;i<(int)heroes.size();i++){
            if(heroes[i].getName() == name)return heroes[i];
        }
        for(int i=0;i<(int)enemies.size();i++){
            if(enemies[i].getName()== name)return enemies[i];
        }
        return heroes[0];
    }
    void removeAvenger(string name){
        for(int i=0;i<(int)heroes.size();i++){
            if(heroes[i].getName() == name){
                heroes.erase(heroes.begin()+i);
                return;
            }
        }
        for(int i=0;i<(int)enemies.size();i++){
            if(enemies[i].getName() == name){
                enemies.erase(enemies.begin()+i);
                return;
            }
        }
    }
    int Result(){
        int heroSum = 0,enemySum = 0;
        for(int i=0;i<(int)heroes.size();i++)if(heroes[i].getQNS().getDurability()>0)heroSum+=heroes[i].getQNS().getDurability()+heroes[i].getQNS().getPower();
        for(int i=0;i<(int)enemies.size();i++)if(enemies[i].getQNS().getDurability()>0)enemySum+=enemies[i].getQNS().getDurability()+enemies[i].getQNS().getPower();
        if(heroSum>enemySum)return 1;
        else if(heroSum==enemySum)return 0;
        else return -1;
    }
    void attack(){
        string A,B; cin>>A>>B;
        Avenger& a1 = getAveneger(A);
        Avenger& a2 = getAveneger(B);
        if(a1.getQNS().getDurability()>0 and a1.getQNS().getHeatLevel()<=500
            and a2.getQNS().getDurability()>0){
            battleLog.push_back(A+" attacks "+B);
            a1.attack(a2);
            if(a2.getQNS().getDurability()<0){
                battleLog.push_back(B+" suit destroyed");
                // removeAvenger(B);
            }
            else if(a2.getQNS().getHeatLevel()>500){
                battleLog.push_back(B+" suit overheated");
            }
        }
    }
    void addLog(string s){
        battleLog.push_back(s);
    }
    void upgrade(string A){
        Avenger& a1 = getAveneger(A);
        if(idx<k){
            a1.upgradeSuit(suits[idx]);
            battleLog.push_back(A+" upgraded");
            idx++;
            return;
        }
        battleLog.push_back(a1.getName()+" upgrade Fail");
    }

};
int main(){
    Battle battle;
    battle.startBattle();
    string s; cin>>s;
    do{
        cin>>s;
        if(s=="Attack"){
            battle.attack();
        }
        else if(s=="Repair"){
            string A; cin>>A;
            int x; cin>>x;
            battle.getAveneger(A).repair(x);
            battle.addLog(A+" repaired");
        }
        else if(s=="BoostPowerByFactor"){
            string A; cin>>A;
            int x; cin>>x;
            battle.getAveneger(A).getQNS().boostPower(x);
            battle.addLog(A+" boosted");
            if(battle.getAveneger(A).getQNS().getHeatLevel()>500)battle.addLog(A+" suit overheated");
        }
        else if(s=="BoostPower"){
            string A; cin>>A;
            int P,D,E,H; cin>>P>>D>>E>>H;
            QNS suit1(P,D,E,H);
            battle.getAveneger(A).upgradeSuit(suit1);
            battle.addLog(A+" upgraded");
        }
        else if(s=="AvengerStatus"){
            string A; cin>>A;
            battle.getAveneger(A).printStatus();
        }
        else if(s=="Upgrade"){
            string A; cin>>A;
            battle.upgrade(A);
        }
        else if(s=="PrintBattleLog"){
            battle.printBattleLog();
        }
        else if(s=="BattleStatus"){
            int state = battle.Result();
            if(state == 1)cout<<"heroes are winning\n";
            else if(state == 0)cout<<"tie\n";
            else cout<<"enemies are winning\n";
        }
    }while(s!="End");
}
