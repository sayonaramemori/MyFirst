#include"num.h"
using namespace std;
extern int chess::arr[10][10];
extern int priority::arr[10][10];
extern vector<recordings> recording_list::dataList;
/*This function exclude the original pos*/
void method::related_pos(XYpos pos,set<XYpos> &dest)
{
    int row = pos.first;
    int col = pos.second;
    for(int i = 1;i<10;i++)
    {
        dest.insert(make_pair(i,col));
        dest.insert(make_pair(row,i));
    }
    fourPos(pos,dest);
    dest.erase(pos);
}
void method::fourPos(XYpos pos,set<XYpos> &poses)
{
    int arr[3] = {2,5,8};
    int row = (pos.first-1)/3;
    int col = (pos.second-1)/3;
    XYpos center = make_pair(arr[row],arr[col]);
    for(int i=center.first-1;i<center.first+2;++i)
    {
        if(i==pos.first)continue;
        for(int j=center.second-1;j<center.second+2;++j)
        {
            if(j==pos.second)continue;
            poses.insert(make_pair(i,j));
        }
    }
}
void method::get_pos(set<XYpos> &pos)
{
    priority::find_max(pos);
}
void method::get_val(set<int> &val,XYpos pos)
{
    set<int> valset;
    chess::get_valset(pos,valset);
    set_symmetric_difference(allval.begin(),allval.end(),valset.begin(),valset.end(),inserter(val,val.begin()));
    if(val.empty())throw runtime_error("GAME OVER");
}
bool method::check(XYpos pos,int val)
{
    chess::go_ahead(pos,val);
    set<XYpos> poses;
    for(auto it=poses.begin();it!=poses.end();it++)
    {
        if(chess::arr[it->first][it->second]!=0)continue;
        if(chess::get_priority(*it)==9)
        {
            chess::go_back(pos);
            return false;
        }
    }
    return true; 
}



chess::chess(const char *s)
{
    init(s);
}
void chess::init(const char *s)
{
    for(int i = 0;i<10;i++)
    for(int j=0;j<10;j++)
    {
        this->arr[i][j]=0;
    }
    for(int i=1;i<10;++i)
        for(int j=1;j<10;++j)
        {
            int index = 9*i+j-10; 
            this->arr[i][j] = stoi(string(1,s[index]));
        }
}
void chess::go_ahead(XYpos pos,int val)
{
    arr[pos.first][pos.second] = val;
}
void chess::go_back(XYpos pos)
{
    arr[pos.first][pos.second] = 0;
}
/*Calling this function means that
 the pos is ready to be written for chess*/
int chess::get_priority(XYpos pos)
{

    return valset.size();
}
void chess::get_valset(XYpos pos,set<int> &valset)
{
    if(arr[pos.first][pos.second]!=0)throw runtime_error("YOU LOST!!!");
    set<XYpos> poses;
    method::related_pos(pos,poses);
    for_each(poses.begin(),poses.end(),[&](auto &cp)
    {
        valset.insert(arr[cp.first][cp.second]);
    });
    valset.erase(0);
}



void priority::init()
{
    for(int i = 0;i<10;i++)
        for(int j=0;j<10;j++)
        {
            arr[i][j]=0;
        }
    for(int i=1;i<10;++i)
        for(int j=1;j<10;++j)
        {
            if(chess::arr[i][j]!=0)continue;
            arr[i][j] = chess::get_priority(make_pair(i,j));
        }
}
priority::priority()
{
    init();
}
void priority::find_max(set<XYpos>& dest)
{
    int mark = 0;
    for(int i=1;i<10;++i)
    for(int j=1;j<10;++j)
    {
        if(arr[i][j]==0||arr[i][j]<mark)continue;
        if(arr[i][j]==mark)dest.insert(make_pair(i,j));
        if(arr[i][j]>mark)
        {
            dest.clear();
            dest.insert(make_pair(i,j));
            mark = arr[i][j];
        }
    }
}
void priority::go_ahead(XYpos pos)
{
    refrelatedpos(pos);
    //将相关位置更改后，改变当前位置的 priority
    arr[pos.first][pos.second] = 0;
}
void priority::go_back(XYpos pos)
{
    refrelatedpos(pos);
    arr[pos.first][pos.second] = chess::get_priority(pos);
}
void priority::refrelatedpos(XYpos pos)
{
    set<XYpos> dest;
    method::related_pos(pos,dest);
    for_each(dest.begin(),dest.end(),[&](auto &cp)
    {
        /*make sure the changes happen on the position
        is empty of the chess*/
        if(chess::arr[cp.first][cp.second]==0)
        arr[cp.first][cp.second] = chess::get_priority(cp);
    });
}


int recordings::cur_val()
{
    return valStack.top();
}
XYpos recordings::cur_pos()
{
    return posStack.top();
}
int recordings::getLevel()
{
    if(valStack.size() == 1)return 3;
    if(posStack.size() == 1)return 2;
    else                                   return 1;
}
//if posstack is not empty after pop,valstack change as well
void recordings::pop_pos_chval()
{
    posStack.pop();
    if(posStack.size()!=0)
    {
        set<int> val;
        method::get_val(val,this->cur_pos());
        this->assignVal(val);
    }
}
void recordings::assignPos(const set<XYpos> &pos)
{
    if(pos.size()==0)
    throw runtime_error("terminate or error occur");
    while(!this->posStack.empty())this->posStack.pop();
    for_each(pos.begin(),pos.end(),[&](auto &b)
    {
        this->posStack.push(b);
    });
}
void recordings::assignVal(const set<int> &val)
{
    if(val.size()==0)
    throw runtime_error("terminate or error occur");
    while(!this->valStack.empty())this->valStack.pop();
    for_each(val.begin(),val.end(),[&](auto &a)
    {
        this->valStack.push(a);
    });
}
void recordings::pop_val()
{
    valStack.pop();
}
//only handle level one and two
void recordings::go_back()
{
    int code = this->getLevel();
    switch (code)
    {
    case 1:
        this->pop_val();
        break;
    case 2:
        this->pop_pos_chval();
        break;
    default:
        throw runtime_error("TRY TO FIND ME!!");
        break;
    }
}


recordings recording_list::cut()
{
    auto temp = dataList.back();
    dataList.pop_back();
    return temp;
}
void recording_list::push(const recordings &posval)
{
    dataList.push_back(posval);
}

/*handle the cut food from the goodfoods
there are two results that discarded or could
be used again */
void engine::handletail()
{
    //keep a copy file
    //And cut the last,handle special
    auto junkfood = goodFoods.cut();
    //remove the change
    CPgoback(junkfood.cur_pos());
    //if level ==3 ,it shall be discarded!
    if(junkfood.getLevel()==3)
    {  
        handletail();
    }
    //if not,remove the top pv pair,try other under top
    else
    {
        //remove top
        junkfood.go_back();
        //find a new pv pair matched
        //Caution:Pass para by refference
        bool res = cookman(junkfood);
        if(!res)handletail();
    }
}
void engine::master()
{
    bool res = true;
    int num = 10;
    while(num--)
    {         
        if(res)
        {
            auto food = generate_next();
            res = cookman(food);
        }
        else
        {
            //After handle the last food must be ok
            handletail();
            res = true;
        }
        monitor();
    }
}
//if cooked well ,it will be push to the goodfoods and return true
//else do nothing ,and return false;
bool engine::cookman(recordings food)
{
    bool res = check_food(food);
    if(res)
    {
        goodFoods.push(food);
        CPgohead(food.cur_pos(),food.cur_val());
        return true;
    }
    else
    {
        return false;
    }
}
void engine::CPgoback(XYpos pos)
{
    chess::go_back(pos);
    priority::go_back(pos); 
}
bool engine::check_food(recordings &posval)
{
    while(!posval.posStack.empty())
    {
        while (!posval.valStack.empty())
        {
            auto top_pos = posval.cur_pos();
            auto top_val = posval.cur_val();
            if(method::check(top_pos,top_val))return true;
            else posval.pop_val();
        }
        posval.pop_pos_chval();
    }
    return false;
}
recordings engine::generate_next()
{
    recordings res;
    set<XYpos> pos;
    set<int> val;
    method::get_pos(pos);
    //get vals by the last pos of this set.
    method::get_val(val,*pos.rbegin());
    res.assignVal(val);
    res.assignPos(pos);
    return res;
}
void engine::CPgohead(XYpos pos,int val)
{
    chess::go_ahead(pos,val);
    priority::go_ahead(pos);
}




void print(int a[][10])
{
    for(int i=0;i<100;i++)
    {
        if(i%10==0)
        {
            cout<<endl;
        }
        cout<<*(*a+i)<<"|";
    }
    cout<<endl;
}
template<typename T>
void printPos(T& val)
{
    for_each(val.begin(),val.end(),[](auto &a){cout<<"( "<<a.first<<","<<a.second<<" )  ";});
    cout<<endl;
}
void printrecord(recordings rec)
{
    cout<<"-------record-------"<<endl;
    cout<<"pos:";
    while(!rec.posStack.empty())
    {
        cout<<"("<<rec.cur_pos().first<<","<<rec.cur_pos().second<<")";
        rec.posStack.pop();
    }
    cout<<endl;
    cout<<"val: ";
    while(!rec.valStack.empty())
    {
        cout<<rec.cur_val()<<" ";
        rec.pop_val();
    }
    cout<<endl;
}
void test()
{
    const char* str = "080900607020000000009010000200030400000001920507000000100600000030000240070840009";
    engine worker(str);
    worker.master();
}
void engine::monitor()
{
    cout<<"-------chess--------"<<endl;
    print(recipe.arr);
    printrecord(goodFoods.dataList.back());
    cout<<"------priority------"<<endl;
    print(cookskill.arr);
    cout<<"----------------------------------------"<<endl;
}

int main()
{
    auto start = clock();
    test();
    printf("Time takens %fs",(double)(clock()-start)/CLOCKS_PER_SEC);
    return 0;
}