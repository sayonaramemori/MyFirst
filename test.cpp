#include<iostream>
#include<deque>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<numeric>
#include<cstdlib>
#include<cassert>
#include<memory>
#include<functional>
#include<map>
#include<list>
#include<stack>
#include<ctime>
using namespace std;


template<typename T>
T myplus(T lhv,T rhv)
{
    return lhv+rhv;
}
template<typename T>
T mycheng(T lhv,T rhv)
{
    return lhv*rhv;
}
// template<typename T>
// void print(const T& t)
// {
//     for(auto it = t.begin(),last = t.end();it!=last;++it)
//     {
//         cout<<*it<<" ";    }
//     cout<<endl;
// }

void test()
{
vector<int> t;
// t.at();
// t.capacity();
// t.data();
// t.emplace();
// t.emplace_back();
// t.erase();//one iterator or a range
// t.front();
// t.get_allocator();
// t.insert();//(p,rv(lr))  (p,il) (p,n,t);
// t.max_size();
// t.reserve();
// t.resize();
// t.swap();
string s;
// s.append();
// s.assign();
// s.at();
// s.back();
// s.c_str();
// s.compare();
// s.copy();
// s.data();
// s.erase();//(sizet pos,n)(pos_itr)
// s.find();
// s.find_first_not_of();
// s.substr();
// s.reserve();
// s.replace();
// s.pop_back();
// s.insert();
// s.erase();
const char* st = "abcdefghijklmn";
string x(st,5);
string y(x,4);  
string z(x,0,100);
cout<<x<<endl;
cout<<y<<endl;
cout<<z<<endl;
}

void tttt()
{
    string s;
    const char* c = "yyyyyyyy";
    // s.copy(c,2,2);
    // cout<<s;
}


void test2()
{
    vector<int> jj{0,2,0,4};
    deque<int> mm;
    auto it = inserter(jj,jj.begin());
    // auto it = back_inserter(jj);
    // auto it = front_inserter(mm);
    for(int i=0;i<100;i++)
    {
        it=i;
    }
    // print(jj);
}
void test3()
{
    set<int> s1{3,1,3},s2{1,4,1},dest;
    // sort(s1.begin(),s1.end());
    set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(dest,dest.begin()));
    // print(dest);
    dest.clear();
    set_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(dest,dest.begin()));
    // print(dest);
    dest.clear();
    set_symmetric_difference(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(dest,dest.begin()));
    // print(dest);
    dest.clear();
    set_union(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(dest,dest.begin()));
    // 6
    dest.clear();
    vector<int> s3{2,3,4,1},s4{1,2,3};
    cout<<includes(s3.begin(),s3.end(),s4.begin(),s4.end());

}
void test4()
{
    vector<int> vec;
    fill_n(back_inserter(vec),4,9);
    // print(vec);
    iota(vec.begin(),vec.end(),4);
    // print(vec);
    // cout<<inner_product(vec.begin(),vec.end(),vec.begin(),0);
    cout<<inner_product(vec.begin(),vec.end(),vec.begin(),1,mycheng<int>,myplus<int>)<<endl;
    cout<<accumulate(vec.begin(),vec.end(),1,mycheng<int>);
}

class tttone
{
    public:
    ~tttone()=default;
    tttone()=default;
tttone(int a){special1 = a;}
    int a1=1;
    virtual void one(){cout<<"father is public"<<endl;}
    private:
    int c1=1;
    protected:
    int b1=1;
    int special1;
    unique_ptr<int[]> p;
};
class ttttwo : public tttone
{
    public:
    void one() 
    {
        cout<<"son1 is private"<<endl;
    }
    int a2=2;
~ttttwo()=default;
ttttwo()=default;
ttttwo(int a):tttone(a){special2 = a;}
    protected:
    int special2;
    int b2=2;
    private:
    int c3=2;

};

class ttthree : public ttttwo
{
    public:
ttthree(int a):ttttwo(a){a3 = a;}
ttthree()=default;
ttthree(const ttthree& para)
{

}
~ttthree(){cout<<"t.a的值为"<<a3<<"的对象被释放"<<endl;}
    int a3=3;
    void printf()
    {
        cout<<a1<<a2<<a3<<endl;
        cout<<b1<<b2<<b3<<endl;
        cout<<special2<<special1<<endl;
    }
    protected:
    int b3=3;
    private:
    void one() override
    {
        cout<<"son2 is private"<<endl;
    }
    int c3=3;
};

void test5()
{
    ttthree t3(3);
    tttone t1(1);
    ttttwo t2(2);
    // t.printf();
    // tttone *one=&t3;
    // one->one();
    ttttwo *two=&t3;
    two->one();
    //作用域运算符只起到编译器查找的起点位置的定位的作用，如果没找到则向上查找
    //如果虚函数没有被覆盖则向上查找，可越过基指针查找至顶层
    //只要基类的虚函数是可访问的，则它儿子通过基类指针的调用不受儿子类的访问控制符的影响，即使儿子类的虚函数是可访问的而基类的虚函数是不可访问的，则也不能访问
    // two->one();
}

void test6()
{
    unique_ptr<ttthree[]> p1(new ttthree[3]{2,2,2});
    // auto p = new ttthree(2);
    p1.reset();
    p1.release();
    p1[2];
    cout<<"函数栈执行完毕"<<endl;
}

void test7()
{
    auto p = make_shared<ttthree>(2);
    // cout<<p.unique()<<endl;
    // cout<<p.use_count()<<endl;
    auto q = p;
    p.reset();
    // cout<<p.owner_before()<<endl;
    cout<<"函數調用棧結束"<<endl;
}

struct mycompare
{
// private:
    bool operator()(const ttthree &lhs,const ttthree &rhs)
    {
        return lhs.a1>rhs.a1;
    }
};

bool myCompare(const ttthree &lhs,const ttthree &rhs)
{
    return lhs.a1>rhs.a1;
}

void test8()
{
    int * p = new int (10);
    shared_ptr<int> a (new int (20));
    shared_ptr<int> b (a); 
    set<ttthree,mycompare> s1;
    set<ttthree,decltype(myCompare)*> s2(myCompare);
    assert(s1.empty());
    cout<<"assert";
    // set<ttthree> s2;
    // s2 = s1;
}

void test9()
{
    const int j=0;
    int i = 0;
    int& r = i;
    decltype(j) a = 9;
    decltype(r+2) b;
    decltype((i)) c = i;
    auto e = j;//忽略顶层const
    const auto f = j;
    auto &h = j;//引用会保留顶层const
    const auto &k = 42;
    auto l = j,p = 3;
}

void test10()
{
    struct compare
    {
        typedef const int& cir;
        bool operator()(cir lhs,cir rhs)
        {
            return lhs>rhs;
        }
    }mcompare;
    
    map<int,int,decltype(mcompare)> m1={{1,2}};
    m1.emplace_hint(m1.begin(),2,7);
}

template<typename T,typename U,typename R>
T testtemp(const U& v1,const R& v2)
{
    return T();
}

// template<typename T> void print(const T&t);
// template<typename T,typename ... Arg> void print(const T& t,const Arg& ... rest);
// //match the last char*
// inline void print(const char* p)
// {
//     cout<<p<<endl;
// }
// //para for char* in the mid or begin
// template<typename ... Arg> inline
// void print(const char* const p,const Arg& ... rest)
// {
//     cout<<p<<",";
//     print(rest...); 
// }
// //for last
// template<typename T> inline 
// void print(const T&t)
// {
//     cout<<t<<endl;
// }
// //not for last
// template<typename T,typename ... Arg> inline 
// void print(const T& t,const Arg& ... rest)
// {
//     cout<<t<<",";
//     print(rest...);
// }



void test11()
{
    int a =1;
    double b = 2;
    long i =999999999;
    testtemp<int>(a,b);//显示地指定类型，从第一个位置开始匹配，返回类型必须指定
    int c[] = {0};
    // print("love",a,b,56,3.14,"meimei",3,"baby",89,"jj");
    // while(--i);
}
void test12();
class memptr
{
    friend void test12();
    void mytest()
    {
        cout<<"diaoyong cheng gong "<<endl;
    }
};

void test12()
{
    memptr obj;
    memptr* ptrobj = nullptr;
    auto myptr = &memptr::mytest;
    (ptrobj->*myptr)() ;
}
inline pair<int,int> posToRC(int p)
{
    int row = p/9;
    int col = p%9;
    return make_pair(row,col);
}
//返回一个位置对应的九宫格位置
inline int posToninePos(int pos)
{
    int r = pos/27;
    int c = pos%9;
    return r*3+c/3;
}
void relatedPos(int p,set<int> &temp)
{
    auto res = posToRC(p);
    //插入行和列
    for(int i=0;i<9;++i)
    {
        temp.insert(res.first*9+i);
        temp.insert(res.second+i*9);
    }
    int num = posToninePos(p);
    int r = num/3;
    int c = num%3;
    int pos = r*27+c*3;
    for(int i = 0;i<3;++i)
    {
        int it = pos+i*9;
        temp.insert(it);
        temp.insert(it+1);
        temp.insert(it+2);
    }
    // temp.erase(p);
}
void test13()
{
    set<int> temp;
    relatedPos(0,temp);
    // print(temp);
    cout<<temp.size()<<endl;
}
class sons
{
public:
sons(int n)
{
    a = n;
    cout<<"gou zao zhixi"<<endl;
}
    sons()
    {
        a = 1;
        cout<<"gou zao zhixi"<<endl;
    }
    ~sons()
    {
        cout<<"xigouzhizx"<<endl;
    }
    sons& operator=(int n)
    {
        this->a = n;
        return *this;
    }
    int a;
};
class newtest
{
public:
    newtest(int val);
    newtest(newtest&&) noexcept;
    newtest(const newtest&);
    int *p;
private:
    static sons s;
    static void init();
};
void newtest::init()
{
    s = 9;
}
sons newtest::s;
// newtest::init();

newtest::newtest(int val)
{
    p = new int(val);
}
newtest::newtest(const newtest& t)
{
    this->p = new int(*t.p);
    cout<<"拷贝构造调用"<<endl;
}
newtest::newtest(newtest&& t) noexcept 
{
    this->p = new int(std::move(*t.p));
    t.p = nullptr;
    cout<<"diao yong ok"<<endl;
}
void test14()
{
    newtest t(newtest(3));
    newtest s(std::move(t));
}

template<typename T>
void prints(T &&val)
{
    cout<<typeid(val).hash_code()<<" ";
}
template<typename T,typename ...Args>
void prints(T &&val,Args &&... para)
{
    prints(std::forward<T>(val));
    prints(std::forward<Args>(para)...);
    // cout<<endl; 
}

void test15()
{
    prints(1,56,"jikjk",76);
    cout<<(typeid("kkk") == typeid("hhh"))<<endl;;
}
#include<memory>
class datatest
{
public:
    datatest()=default;
    datatest(int,int,int);
    datatest(const datatest&);
    datatest(datatest&&);
    void init();
    int a = 0;
    int b = 0;
    int c = 0;
    static int ori,mov;
};
// datatest& opertator=(const datatest &l,const datatest& t)
// {
//     l.a = t.a;
//     l.b = t.b;
//     l.c = t.c;
//     return l;
// }
void datatest::init()
{
    this->a = 0;
    this->b = 0;
    this->c = 0;
}
int datatest::ori = 0;
int datatest::mov = 0;
datatest::datatest(int v1,int v2,int v3):a(v1),b(v2),c(v3)
{
}
datatest::datatest(const datatest& t)
{
    this->a = t.a;
    this->b = t.b;
    this->c = t.c;
    ++ori;
}
datatest::datatest(datatest&& t)
{
    this->a = t.a;
    this->b = t.b;
    this->c = t.c;
    ++mov;
}

void test16()
{
    int j = 100000000;
    int i = j;
    // datatest k[i]; 
    // while(--i)
    // {
    //     // datatest t(1,2,3);
    //     k[i].init();
    // }
    allocator<datatest> alloc;
    auto p = alloc.allocate(j);
    while(j--)
    {
        datatest t(1,2,3);
        // alloc.construct(p++,t);
        alloc.construct(p++,std::move(t));
    }
    cout<<"construct func called times:"<<datatest::ori<<endl;
    cout<<"move_coustruct called times:"<<datatest::mov<<endl;
}


void test17(int app[][10])
{
    stack<pair<int,int>> sta,tea;

    for(int i=0;i<10;i++)
    {
        sta.push(make_pair(i,i-1));
    }
    for(int i=0;i<10;i++)
    {
        cout<<sta.top().first<<sta.size()<<" ";
        sta.pop();
    }
    typedef struct java
    {
        stack<int> val;
        stack<pair<int,int>> pos;
    }Java;
    Java jj;
    jj.val.push(7);
    vector<int> vec;
    tea = sta;
}
void test18(function<int(int,int)> myfunc)
{
    cout<<myfunc(1,1)<<endl;
}
void test19()
{
    auto la = [](auto a,auto b){return a+b;};
    test18(la);
}
void test20()
{
    set<int> a = {1,2,3,4,5};
    set<int> b = {2,4};
    set<int> c;
    set_symmetric_difference(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()));
    cout<<(*a.rbegin() == 5)<<endl;    
}
void test21()
{
    const char s[4] = "abc";
    cout<<(s[3]=='\0')<<endl;
}
#include<regex>
void test22()
{
    const char *s = "java";
    int a = 10;
    a += '0';
    cout<<a<<endl;
}
int main()
{
    clock_t tStart = clock();
    int a[10][10];
    test22();
    printf("Time taken: %.5fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}