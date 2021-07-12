#include<iostream>
#include<map>
#include<set>
#include<algorithm>

using namespace std;
//position  = (x , y);
typedef pair<int,int> position;
typedef set<pair<position,position>> SlopeGroup;

bool mycompare(const pair<double,int>& lhs,const pair<double,int>& rhs)
{
    return lhs.second>rhs.second;
}
bool mycompareforset(const pair<double,set<position>>& s1,const pair<double,set<position>>& s2)
{
    return s1.second.size()>s2.second.size();
}

class solution
{
public:
    solution(set<position>& ini)
    {
        init(ini);
        getSize();
    }
    void printSlope()
    {
        for(auto &a:mydata )
        {
            cout<<a.first<<" ";
        }
        cout<<endl;
    }
    void printRes(set<position>& p)
    {
        cout<<"position:"<<endl;
        for_each(p.begin(),p.end(),[&](auto &a){cout<<"("<<a.first<<","<<a.second<<")"<<endl;});
    }
private:
    void init(set<position>& ini);
    void getSize();
    double getslopdistance(const position& p,const double& slop);
    void getMax(const SlopeGroup& sp,const double& slope,set<position>& temp);
    bool getslope(const position&,const position&,double&);
    map<double,SlopeGroup> mydata;
    map<double,int> results;
    SlopeGroup badpos;
};
bool solution::getslope(const position &p1,const position &p2,double &val)
{
    double r1 = p1.second-p2.second;
    double r2 = p1.first-p2.first;
    if(r2!=0)
    {
        val = r1/r2;
        return true;
    }
    else 
    {
        badpos.insert(make_pair(p1,p2));
        return false;
    }
}
void solution::init(set<position>& ini)
{
    auto tail = ini.rbegin();
    for(auto it = ini.begin(),last = ini.end();it != tail.base(); ++it)
    {
        auto behind_one = it;
        ++behind_one;
        double slope = 0;
        for(;behind_one != last;++behind_one)
        {    
            if(getslope(*it,*behind_one,slope))
            mydata[slope].insert(make_pair(*it,*behind_one));
        }
    }
}
void solution::getSize()
{
    set<position> temp;
    for_each(mydata.begin(),mydata.end(),[&](auto& a)
    {
        getMax(a.second,a.first,temp);
        results[a.first]=temp.size();
        temp.clear();
    });
    pair<double,int> res = *max_element(results.begin(),results.end(),mycompare);
    getMax(mydata[res.first],res.first,temp);
    printRes(temp);
}
void solution::getMax(const SlopeGroup& sp,const double& slope,set<position>& temp)
{
    // map<double,int> res; //斜距，数量
    map<double,set<position>> res;
    for_each(sp.begin(),sp.end(),[&](const pair<position,position>& a)
    {
        auto it = getslopdistance(a.first,slope);
        res[it].insert(a.first);
        res[it].insert(a.second);
    });
    const auto result = max_element(res.begin(),res.end(),mycompareforset);
    temp.insert(result->second.begin(),result->second.end());
}
inline double solution::getslopdistance(const position& p,const double& slope)
{
    return p.second-p.first*slope;
}

int main()
{
    set<position> p{{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}};
    solution q(p);
    q.printSlope();
    return 0;
}

