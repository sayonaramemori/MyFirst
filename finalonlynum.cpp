using namespace std;
#include<algorithm>
#include<array>
#include<string>
#include<set>
#include<vector>
#include<memory>
#include<functional>
#include<iostream>
int pri_num[3][3] = {0,3,6,27,30,33,54,57,60};
array<int,81> chess,priMap;
vector<set<int>> row_sets,colum_sets,nine_set;

class posVal;
void do_work();
bool is_related(int pos1,int pos2);
bool check_map(array<int,81> &chess,posVal &pv);
pair<int*,int> get_val(int pos);
pair<int*,int> get_Pos();
void relatedPos(int p,set<int> &temp);

class setManager;
class priorityMap;
class chessManager;
inline pair<int,int> posTocr(int pos)
{
    int row = pos/9;
    int col = pos%9;
    return make_pair(row,col);
}
inline int posToninePos(int pos)
{
    int r = pos/27;
    int c = pos%9;
    return r*3+c/3;
}

class datas
{
// friend bool priorityMap::check(datas &);
friend class priorityMap;
public:
    datas(int* pos, int* val,int ps,int vs):p(pos),v(val),v_size(vs),p_size(ps)
    {}
    int getCode()
    {
        enum codes{one=1,two,three};//回溯代码
        if(v_size != 1)return one;
        else{return p_size!=1?two:three;}
    }
    void otherPos(vector<int> &temp)
    {
        if(p_size==1)return;
        for(int i=0;i<p_size-1;++i)
        temp.push_back(p[i]);
    }
    int top_pos()
    {
        return p[p_size - 1];
    }

    int top_val()
    {
        return v[v_size - 1];
    }

    void pop_pos()
    {
        --p_size;
    }

    void pop_val()
    {
        --v_size;
    }
    void changeVal(int *vptr,int size)
    {
        v_size = size;
        v.reset(vptr);
    }

private:
    unique_ptr<int[]> p;
    unique_ptr<int[]> v;
    int p_size = 0;
    int v_size = 0;
};
// 初始化在set和chess之后
class priorityMap
{
public:
    priorityMap()
    {
        init();
    }
    //在当前Map下返回最大pri的pos数组的指针
    pair<int*,int> getPos()
    {
        int max = 0;
        set<int> temp;
        for(int i=0;i<81;++i)
        {
            if(Map[i]==0)continue;
            if(Map[i]==max)temp.insert(i);
            if(Map[i]>max)
            {
                max = Map[i];
                temp.clear();
                temp.insert(i);
            }
        }
        if(temp.empty())exit(233);
        int *p = new int[temp.size()]();
        int i = 0;
        for_each(temp.begin(),temp.end(),[&](auto &a){p[i++]=a;});
        return make_pair(p,temp.size());
    }
    //需要当前的set
    void gonext(int p,int v)
    {
        Map[p] = 0;
        auto it = posTocr(p);
        for(int i = 0;i<9;++i)       //检查行
        {
            int pos = it.first*9+i;
            if(Map[pos]==0)          //检查是否已填
            continue;
            if(is_repeated(pos,v))   //检查写入的值是否与检查位置的值set重复
            ++Map[pos];
        }
        for(int i = 0;i<9;++i)       //检查列
        {
            int pos = it.second + i*9;
            if(Map[pos]==0)
            continue;
            if(is_repeated(pos,v))
            ++Map[pos];
        }
        vector<int> temp;
        getNinePos(p,temp);
        for(auto it = temp.begin();it!=temp.end();++it)
        {
            if(Map[*it]==0)
            continue;
            if(is_repeated(*it,v))
            ++Map[*it];
        }
    }
    static bool check(datas &tailValue)
    {
        if(tailValue.p_size==1)return true;
        vector<int> temp;
        tailValue.otherPos(temp);
        int top = tailValue.top_pos();
        int val = tailValue.top_val();
        for(int i=0;i<temp.size();++i)
        if(is_relate(top,temp[i])&&is_repeated(temp[i],val)&&temp[i]>=8)return false;
        return true;
    }
    //需要在setManager goback后
    void goback(int p,int v);
    static array<int,81> Map;
private:
    void init();
    static bool is_relate(int p1,int p2)
    {
        auto res1 = posTocr(p1);
        auto res2 = posTocr(p2);
        return res1.first==res2.first || res1.second==res2.second || posToninePos(p1)==posToninePos(p2);
    }
    //使用当前的set
    static bool is_repeated(int p,int v);
    void getNinePos(int pos,vector<int> &tem)
    {
        set<int> temp;
        int res = posToninePos(pos);
        int r = res/3;
        int c = res%3;
        res = r*9+c*3;
        for(int i=0;i<3;++i)
        {
            int p = res+i*9;
            temp.insert(p);
            temp.insert(p+1);
            temp.insert(p+2);
        }
        temp.erase(pos);
        set<int> contain;
        for_each(temp.begin(),temp.end(),[&](auto &a)
        {
            if(abs(a-pos)<3 || abs(a-pos)%9==0)contain.insert(a);
        });
        tem.resize(temp.size()-contain.size());
        set_symmetric_difference(temp.begin(),temp.end(),contain.begin(),contain.end(),tem.begin());
    }
};
class data_list
{
public:
    data_list(chessManager &cm,setManager &sm,priorityMap &pm)
    {
        gonext(cm,sm,pm);
    }
    //默许尾元素通过checkMap，并在当前的chess，set，map下在尾部生成下一个待检查的对象
    void gonext(chessManager &cm,setManager &sm,priorityMap &pm);
    datas& last()
    {
        return dataList.back();
    }
    pair<int,int> gobackValue()
    {
        return make_pair(dataList.back().top_pos(),dataList.back().top_val());
    }
    void oneLevel()
    {
        dataList.back().pop_val();
    }
    void goback()
    {
        dataList.pop_back();
    }
    void twoLevel();
    //返回尾元素的code
    int getCode()
    {
        return dataList.back().getCode();
    }

private:
    vector<datas> dataList;

};
class chessManager
{
friend class setManager;
friend class priorityMap;
public:
    chessManager(string &s)
    {
        to_chess(s);
    }
    //仅写值
    void gonext(int pos,int val)
    {
        cur_pos = pos;
        cur_val = val;
        chess[pos] = val;
    }
    void goback(int pos)
    {
        chess[pos] = 0;
    }
private:
    void get_col_set(set<int> &temp,int col)
    {
        int i = 0;
        while(i<9)
        {
            temp.insert(chess[col+i*9]);
            ++i;
        }
        temp.erase(0);
    }
    void get_row_set(set<int> &temp,int row)
    {
        auto it = chess.begin()+row*9;
        temp.insert(it,it+9);
        temp.erase(0);
    }
    void get_nine_set(set<int> &temp,int number)
    {
        if(number>=0&&number<=8)
        {
            int r = number/3;
            int c = number%3;
            int p = r*27+c*3;
            for(int i = 0;i<3;++i)
            {
                auto it = chess.begin()+p+i*9;
                temp.insert(it,it+3);
            }
            temp.erase(0);
        }
        else
        {
            cout<<"range_error"<<endl;
            exit(-1);
        }
    }

    void to_chess(string &str)
    {
        int i = 0;
        for_each(str.begin(),str.end(),[&](auto &c)
        {
            chess[i] = stoi(string(1,c));
            if(chess[i]==0)++close;
            ++i;
        });
    }
    static array<int,81> chess;
    int cur_pos = 0;
    int cur_val = 0;
    int open = 0;
    int close = 0;

};
//由chessManager初始化
class setManager
{
public:
    setManager(chessManager &chM)
    {
        init(chM);
    }
    //对应位置的行列九宫格set
    static void posPriSet(set<int> &temp,int pos)
    {
        auto pv = posTocr(pos);
        int ninePos = posToninePos(pos);
        temp.insert(rowSets[pv.first].begin(),rowSets[pv.first].end());
        temp.insert(colSets[pv.second].begin(),colSets[pv.second].end());
        temp.insert(nineSets[ninePos].begin(),nineSets[ninePos].end());
    }
    static int posPri(int pos)
    {
        set<int> temp;
        posPriSet(temp,pos);
        return temp.size();
    }
    //对三个set进行插入更新；
    void gonext(int pos,int val)
    {
        auto res = posTocr(pos);
        rowSets[res.first].insert(val);
        colSets[res.second].insert(val);
        nineSets[posToninePos(pos)].insert(val);
    }
    void goback(int pos,int val)
    {
        auto res = posTocr(pos);
        rowSets[res.first].erase(val);
        colSets[res.second].erase(val);
        nineSets[posToninePos(pos)].erase(val);
    }
    //在当前set，chess，Map下
    static pair<int*,int> getVal(int pos)
    {
        set<int> temp;
        setManager::posPriSet(temp,pos);
        set<int> subtr = {1,2,3,4,5,6,7,8,9};
        int size = subtr.size()-temp.size();
        int *p = new int[size]();
        set_symmetric_difference(temp.begin(),temp.end(),subtr.begin(),subtr.end(),p);
        return make_pair(p,size);
    }

private:
    void init(chessManager &chM)
    {
        set<int> temp;
        for(int i=0;i<9;++i)
        {
            chM.get_col_set(temp,i);
            colSets.push_back(temp);
            temp.clear();
            chM.get_row_set(temp,i);
            rowSets.push_back(temp);
            temp.clear();
            chM.get_nine_set(temp,i);
            nineSets.push_back(temp);
            temp.clear();
        }
    }
    static vector<set<int>> rowSets,colSets,nineSets;
};
void goback(int code,data_list &dl,setManager &sm,priorityMap &pm,chessManager &cm)
{
    if(code!=3)
    {
        if(code == 1)
        dl.oneLevel();
        else 
        dl.twoLevel();
    }
    else
    {
        dl.goback();
        auto res = dl.gobackValue();        //
        sm.goback(res.first,res.second);
        cm.goback(res.second);
        pm.goback(res.first,res.second);
        goback(dl.getCode(),dl,sm,pm,cm);
    }
}
class workManager
{
public:
    workManager() = default;
    void work(data_list &dl,setManager &sm,priorityMap &pm,chessManager &cm)
    {
        while(true)
        {
            if(priorityMap::check(dl.last()))
            gonext(dl,sm,pm,cm);
            else
            goback(dl.getCode(),dl,sm,pm,cm);
        }

    }
private:
    void gonext(data_list &dl,setManager &sm,priorityMap &pm,chessManager &cm)
    {
        auto res = dl.gobackValue();
        dl.gonext(cm,sm,pm);//先提供 值对 即可
        pm.gonext(res.first,res.second);
        sm.gonext(res.first,res.second);
        cm.gonext(res.first,res.second);//无耦合
    }
};

void priorityMap::goback(int p,int v)
{
    auto it = posTocr(p);
    for(int i = 0;i<9;++i)       //检查行
    {
        int pos = it.first*9+i;
        if(Map[pos]==0)          //检查是否已填
        continue;
        if(is_repeated(pos,v))   //检查写入的值是否与检查位置的值set重复
        --Map[pos];
    }
    for(int i = 0;i<9;++i)       //检查列
    {
        int pos = it.second + i*9;
        if(Map[pos]==0)
        continue;
        if(is_repeated(pos,v))
        --Map[pos];
    }
    vector<int> temp;
    getNinePos(p,temp);
    for(auto it = temp.begin();it!=temp.end();++it)
    {
        if(Map[*it]==0)
        continue;
        if(is_repeated(*it,v))
        --Map[*it];
    }
    Map[p] = setManager::posPri(p);
}
void priorityMap::init()
{
    for(int i = 0;i<81;++i)
    {
        if(chessManager::chess[i]!=0)continue;
        Map[i] = setManager::posPri(i);
    }
}
bool priorityMap::is_repeated(int p,int v)
{
    set<int> temp;
    setManager::posPriSet(temp,p);
    return temp.insert(v).second;
}
void data_list::gonext(chessManager &cm,setManager &sm,priorityMap &pm)
{
    auto p = pm.getPos();
    auto v = sm.getVal(p.first[p.second-1]);
    dataList.emplace_back(p.first,v.first,p.second,v.second);
}
void data_list::twoLevel()
{
    dataList.back().pop_pos();
    int pos = dataList.back().top_pos();
    auto res = setManager::getVal(pos);
    dataList.back().changeVal(res.first,res.second);
}


void test()
{
    
}

int main()
{
    // string str = "080900607020000000009010000200030400000001920507000000100600000030000240070840009";
    // chessManager chess(str);
    // setManager setes(chess);
    // priorityMap priMap;
    // data_list dali(chess,setes,priMap);
    // workManager worker;
    // worker.work(dali,setes,priMap,chess);

    test();
    return 0;
}