#include<set>
#include<algorithm>
#include<vector>
#include<string>
#include<iostream>
#include<array>
#include<functional>
#include<numeric>
#include<stack>
#include<ctime>
// #define IS_REVERSED 
using namespace std;
using namespace std::placeholders;
//位置及值参数均用 p和 v表示
class cake;
class priMap;
class cakeStars;
class chessMan;
class worker;

void refreshPriMap(int &val,int p);
void test();
void GoBack();
void printOtherPos(const vector<int>& vec);
void printOtherVal(const vector<int> &vec);

class method
{
public:
    static void getNinePos(set<int>& temp,int p);
    static void relatedPos(set<int> &temp,int p);
    static void getRowColpos(set<int>& temp,int p);
    static pair<int,int> posToRC(int p);
    static int posToninePos(int pos);
private:
    static array<int,9> quickpos;
    static array<int,9> init();
public:
    static int ifOfAll(set<int>& pos,function<bool(const int &val)> func,array<int,81> &arr);
    static int ifOfAllWithPos(set<int>& pos,function<bool(const int &val,int p)> func,array<int,81> &arr);
    static void travalAllAndOperateWihtPos(set<int>& pos,function<void(int &val,int p)> func,array<int,81> &arr);
    static void travalAllAndOperate(set<int> &pos,function<void(int &val)> func,array<int,81> &arr);
    static set<int> nums;
};
auto method::init() -> array<int,9>
{
    for(int i=1;i<10;++i)
    {
        nums.insert(i);
    }
    for(int i=0;i<3;++i)
    {
        quickpos[i] = i*3;
        quickpos[i+3] = quickpos[i]+27;
        quickpos[i+6] = quickpos[i]+54;
    }
    return quickpos;
}
array<int,9> method::quickpos=method::init();



class worker
{
public:
    void doWork();
    cake make_cake();
    void goAhead(cake good_food);
    void goBack();
    void removeTopInf(int p);
private:
    bool check_food(cake &food);
};

class chessMan
{
    friend void test();
public:
    chessMan(){}
    chessMan(string &s)
    {
        init(s);
    }
    static void goAheah(int p,int v);
    static void goBack(int p);
    static void getVal(set<int>&,int);
    static void getPos(set<int>&);
    static void posPriSet(set<int>&,int p);
    static int posPriLev(int p);
    static bool isExisted(int p,int v);
    static array<int,81> chess;
private:
    void init(string&);
    static void posMappingVal(set<int>& oripos,set<int> &res);
};

class priMap
{
public:
    static void goAhead(int p);
    static void goBack(int p);
    static bool check(int p,int v);
    static array<int,81> priorityMap;
private:
    static void init();
    static void refresh_after_chess(int p);
};
void priMap::init()
{
    priorityMap.fill(0);
    for(int i=0;i<81;++i)
    {
        //find the unwrite place
        if(chessMan::chess[i]!=0)continue;
        priorityMap[i] = chessMan::posPriLev(i);
    }
    // cout<<"priMap initialized"<<endl;
}
void priMap::init();

class cake
{
public:
    cake(set<int> &p,set<int> &v)
    {
        assignPos(p);
        assignVal(v);
    }
    int top_val();
    int top_pos();
    void pop_val();
    void pop_pos();
    int getCode();
    void goBack();
    void assignPos(set<int> &p);
    void assignVal(set<int> &v);
private:
    stack<int> valStack;
    stack<int> posStack;
};

class cakeStars
{
friend void cake::goBack();
public:
    static void push_cake(cake);
    static cake cut_cake();
    // static bool checkLoop();
private:
    static vector<cake> cakeStarsList;
};
// vector<cake> cakeStars::cakeStarsList

//the return num is the false times

constexpr int getsize()
{
    return 81;
}

template<typename T>
void print(T &t)
{
    int i=0;
    for_each(t.begin(),t.end(),[&](auto &a){if((i++%9)==0)cout<<endl;cout<<a<<" ";});
    cout<<endl;
}

void doublePrint(array<int,getsize()> &a1,array<int,getsize()> &a2)
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            cout<<a1[i*9+j]<<" ";
        }
        cout<<"       ";
        for(int j=0;j<9;j++)
        {
            cout<<a2[i*9+j]<<" ";
        }
        cout<<endl;
    }
}

void debugtest(int val,int pos, bool status,cakeStars* dbptr)
{
}