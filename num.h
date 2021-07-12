#include<algorithm>
#include<functional>
#include<map>
#include<iostream>
#include<vector>
#include<numeric>
#include<string>
#include<set>
#include<ctime>
#include<stack>
using namespace std;
typedef pair<int,int> XYpos;
class recordings;
class engine;
void test();
void printrecord(recordings rec);
class method
{
public:
    static bool check(XYpos pos,int val);
    static void related_pos(XYpos pos,set<XYpos> &dest);
    static void get_val(set<int> &val,XYpos pos);
    static void get_pos(set<XYpos> &pos);
private:
    static set<int> allval;
    static void fourPos(XYpos pos,set<XYpos> &poses);
};
set<int> method::allval = {1,2,3,4,5,6,7,8,9};

class priority
{
friend class method;
friend void test();
private:
    void init();
    static void refrelatedpos(XYpos pos);
public:
    static int arr[10][10];
    static void find_max(set<XYpos> &dest);
    static void go_ahead(XYpos pos);
    static void go_back(XYpos pos);
    priority();
};
class chess
{
friend void test();
friend class priority;
friend class engine;
friend class method;
private:
    void init(const char*s);
    static void get_valset(XYpos pos,set<int> &valset);
    static int arr[10][10];
public:
    chess(const char*s);
    static void go_ahead(XYpos pos,int val);
    static void go_back(XYpos pos);
    static int get_priority(XYpos pos);
};

class engine;
class recordings
{
friend void printrecord(recordings rec);
friend void test();
friend class engine;
private:
    stack<XYpos> posStack;
    stack<int> valStack;
public:
    XYpos cur_pos();
    void assignVal(const set<int> &val);
    void assignPos(const set<XYpos> &pos);
    int cur_val();
    void pop_val();
    void pop_pos_chval(); 
    int getLevel();  
    void go_back();
};

class recording_list
{
friend class engine;
    static vector<recordings> dataList;
public:
    void push(const recordings &posval);
    recordings cut();
};

class engine
{
friend void test();
public:
    recordings generate_next();
    bool check_food(recordings &posval);
    engine(const char *liter):recipe(liter){};
    bool cookman(recordings food);
    void monitor();
    void master();
    void handletail();
    static void CPgoback(XYpos pos);
    static void CPgohead(XYpos pos,int val);
private:
    chess recipe;
    priority cookskill;
    recording_list goodFoods;
};