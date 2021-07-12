#include"onlynum.h"
using namespace std;
extern array<int,81> chessMan::chess;
extern vector<cake> cakeStars::cakeStarsList;
extern array<int,81> priMap::priorityMap;
extern set<int> method::nums;

//cake's defination
//initialize with the container not empty!
inline int cake::top_val()
{
    return valStack.top();
}
inline int cake::top_pos()
{
    return posStack.top();
}
inline void cake::pop_pos()
{
    posStack.pop();
}
inline void cake::pop_val()
{
    valStack.pop();
}
inline int cake::getCode()
{
    if(valStack.size()>1)return 1;
    if(posStack.size()!=1)return 2;
    else return 3;
}
//Promise it is not empty!
inline void cake::assignPos(set<int> &p)
{
    if(p.empty())
    throw runtime_error("empty initialized!");
    for_each(p.begin(),p.end(),[&](auto &pos){this->posStack.push(pos);});
}
inline void cake::assignVal(set<int> &v)
{
    if(v.empty())
    throw runtime_error("empty initialized!");
    for_each(v.begin(),v.end(),[&](auto &val){this->valStack.push(val);});
}
//仅负责一二级的回溯
void cake::goBack()
{
    int code = this->getCode();
    if(code>2)
    throw runtime_error("beyond bound");
    if(code==1)
    {
        this->pop_val();
    }
    else
    {
        //pop_pos first;then get the val of the pos
        this->pop_pos();
        set<int> temp;
        chessMan::getVal(temp,this->top_pos());
        this->assignVal(temp);
    }
}

//check a related pos 
inline bool check_helper(const int &pri,int p,int v)
{
    if(!chessMan::isExisted(p,v))return true;
    else return false;
}
//priMap's defination

//priMap is mapping to chess ,always after chess
void priMap::goAhead(int p)
{
    priorityMap[p] = 0;
    refresh_after_chess(p);
}
//always after chess
void priMap::goBack(int p)
{
    priorityMap[p] = chessMan::posPriLev(p);
    refresh_after_chess(p);
}
void priMap::refresh_after_chess(int p)
{
    set<int> temp;
    method::relatedPos(temp,p);
    method::travalAllAndOperateWihtPos(temp,refreshPriMap,priorityMap);
}
void refreshPriMap(int &val,int p)
{
    if(chessMan::chess[p]!=0)return;
    val = chessMan::posPriLev(p);
}
//this function promise the posSet of the next chess is avaliable for at least one val to write.
bool priMap::check(int p,int v)
{
    set<int> temp;
    method::relatedPos(temp,p);
    if(method::ifOfAllWithPos(temp,bind(check_helper,_1,_2,v),priorityMap)==0)return true;
    return false;
}


inline bool findByVal(const int &lval,int rval)
{
    return lval == rval;
}
inline bool findByValWithout0(const int &lval,int rval)
{
    if(lval == 0)return true;
    return lval == rval;
}
//chessMan's defination
//Just write a new val
inline void chessMan::goAheah(int p,int v)
{
    chess[p]=v;
}
//Just write value 0
inline void chessMan::goBack(int p)
{
    chess[p]=0;
}
//get val from posset
inline void chessMan::posMappingVal(set<int>& oripos,set<int>& res)
{
    for_each(oripos.begin(),oripos.end(),[&](auto &pos){res.insert(chess[pos]);});
    res.erase(0);
}
void chessMan::posPriSet(set<int> &s,int p)
{
    set<int> pos;
    method::relatedPos(pos,p);
    posMappingVal(pos,s);
}
int chessMan::posPriLev(int p)
{
    set<int> temp;
    method::relatedPos(temp,p);
    return method::ifOfAll(temp,bind(findByVal,_1,0),chess);
}
//if a val is existed in priset of paticular pos,return true
bool chessMan::isExisted(int p,int v)
{
    set<int> temp;
    method::relatedPos(temp,p);
    if(method::ifOfAll(temp,bind(findByValWithout0,_1,v),chess)!=temp.size())
    return true;
    else
    return false;
}
//初始化chess
void chessMan::init(string &s)
{
    if(s.size()!=81)
    throw runtime_error("please enter correct number of num");
    int pos = 0;
    auto toNum = [&](auto &a){chess[pos++]=stoi(string(1,a));};
    for_each(s.begin(),s.end(),toNum);
    cout<<"chess intialized"<<endl;
}
//耦合priorityMap，获取最大值序列的set
void chessMan::getPos(set<int> &temp)
{
    int max = 0;
    for(int pos=0;pos<81;++pos)
    {
        if(priMap::priorityMap[pos]==0||priMap::priorityMap[pos]<max)continue;
        if(priMap::priorityMap[pos]==max)temp.insert(pos);
        if(priMap::priorityMap[pos]>max)
        {
            max = priMap::priorityMap[pos];
            temp.clear();
            temp.insert(pos);
        }
    }
    if(temp.empty())throw runtime_error("pos empty!");
}
//耦合chessMan
void chessMan::getVal(set<int> &valset,int p)
{
    set<int> temp;
    posPriSet(temp,p);
    set_symmetric_difference(method::nums.begin(),method::nums.end(),valset.begin(),valset.end(),inserter(valset,valset.begin()));
    if(valset.empty())throw runtime_error("val empty!");
}

//cakeStars's defination
//基于更新后的chess和 priMap,creat the mapping cake for chess or Map
void cakeStars::push_cake(cake good)
{
    cakeStarsList.push_back(good);
}
cake cakeStars::cut_cake()
{
    auto res = cakeStarsList.back();
    cakeStarsList.pop_back();
    return res;
}


//worker's defination
void worker::goAhead(cake good_food)
{
    chessMan::goAheah(good_food.top_pos(),good_food.top_val());
    priMap::goAhead(good_food.top_pos());
    cakeStars::push_cake(good_food);
}
void worker::goBack()
{
    cake bad_food = cakeStars::cut_cake();
    removeTopInf(bad_food.top_pos());
    if(bad_food.getCode()!=3)
    {
        bad_food.goBack();
        if(check_food(bad_food))
        goAhead(bad_food);
        else goBack();
    }
    else goBack();

}
void worker::removeTopInf(int p)
{
    chessMan::goBack(p);
    priMap::goBack(p);
}
void worker::doWork()
{
    int num = 1000;
    while (num--)
    {
        auto food = make_cake();
        if(check_food(food))goAhead(food);
        else goBack();
    } 
}
//food should not be empty
bool worker::check_food(cake &food)
{
    int code = 0;
    while((code = food.getCode())!=3)
    if(priMap::check(food.top_pos(),food.top_val()))
    return true;
    else
    food.goBack();
    return priMap::check(food.top_pos(),food.top_val());
}
//generate next based current chess
cake worker::make_cake()
{
    set<int> pos,val;
    chessMan::getPos(pos);
    chessMan::getVal(val,*pos.rbegin());
    cake food(pos,val);
    return food;
}


//获取一个位置的行列值，0到 8之间，返回pair
inline pair<int,int> method::posToRC(int p)
{
    int row = p/9;
    int col = p%9;
    return make_pair(row,col);
}
//返回一个位置对应的九宫格位置
inline int method::posToninePos(int pos)
{
    int r = pos/27;
    int c = pos%9;
    return r*3+c/3;
}
void method::getRowColpos(set<int>& temp,int p)
{
    auto res = posToRC(p);
    for(int i=0;i<9;++i)
    {
        temp.insert(res.first*9+i);
        temp.insert(res.second+i*9);
    }
}
void method::getNinePos(set<int>& temp,int p)
{
    int num = posToninePos(p);
    int pos = quickpos[num];
    for(int i = 0;i<3;++i)
    {
        int it = pos+i*9;
        temp.insert(it);
        temp.insert(it+1);
        temp.insert(it+2);
    }
}
//not include p itself.
void method::relatedPos(set<int> &temp,int p)
{
    getNinePos(temp,p);
    getRowColpos(temp,p);
    temp.erase(p);
}
inline int method::ifOfAllWithPos(set<int>& pos,function<bool(const int &val,int p)> func,array<int,81>&arr)
{
    int flag = 0;
    for_each(pos.begin(),pos.end(),[&](auto &p){if(!func(arr[p],p))++flag;});
    return flag;
}
inline int method::ifOfAll(set<int>& pos,function<bool(const int &val)> func,array<int,81> &arr)
{
    int res = 0;
    for_each(pos.begin(),pos.end(),[&](auto &p){if(!func(arr[p]))++res;});
    return res;
}
inline void method::travalAllAndOperateWihtPos(set<int>& pos,function<void(int &val,int p)> func,array<int,81> &arr)
{
    for_each(pos.begin(),pos.end(),[&](auto &p){func(arr[p],p);});
}
inline void method::travalAllAndOperate(set<int>& pos,function<void(int &val)> func,array<int,81> &arr)
{
    for_each(pos.begin(),pos.end(),[&](auto &p){func(arr[p]);});
}

void test()
{
    string input = "080900607020000000009010000200030400000001920507000000100600000030000240070840009";
    chessMan chess(input);
    priMap priorityMap;
    cakeStars cakes;
    worker man;
    man.doWork();
}

int main()
{
    clock_t start = clock();
    printf("Time taken:%.5fs\n",double(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}
