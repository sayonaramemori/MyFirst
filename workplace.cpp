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
#include<map>
#include<list>
#include<cmath>
#include<ctime>
using namespace std;

template<typename T>
double calcu(T && val)
{
    return val;
}
template<typename T,typename ... Arg>
double calcu(T&& v1,Arg&& ... rest)
{
    return v1*calcu(std::forward<Arg>(rest)...);
}
template<typename ... Arg>
double liancheng(Arg&& ... arg)
{
    double res = calcu(std::forward<Arg>(arg)...);
    // cout<<"连乘结果为："<<res<<endl;
    return res;
}

void test()
{
    double num=1;
    double start = 1;
    double res = 0;
    cout<<"pleae enter some number"<<endl;
    while(true)
    {
        cin >> num;
        if(!cin)break;
        res = liancheng(start,num);
        start = num = res;
    }
    cout<<"result is:"<<res<<endl;
}



class shuitou
{
public:
    shuitou() = default;
    void Q_d_myu_num(double Q,double d,double myu,int num)
    {
        this->Q_=Q;
        this->d_=d;
        this->myu_=myu;
        this->num_=num;
    }
    void Spe_d_myu_num(double spe,double d,double myu,int num)
    {
        this->d_=d;
        this->myu_=myu;
        this->num_=num;
        this->spe_=spe;
    }
    double getA()
    {
        return M_PI* d_*d_ /4;
    }
    double getSpeed()
    {
        if(spe_==0)
        {
            auto sqa = getA();
            return Q_/sqa;
        }
        else
        return spe_;
    }
    double getlambda()
    {
        if(this->lambda == 0)
        return 64/getRe();
        else
        return this->lambda;
    }
    void setRE(double re)
    {
        this->re = re;
        double s = re*myu_*pow(0.1,num_)/d_;
        this->spe_ = s;
    }
    double getRe()
    {
        if(re!=0)return this->re;
        auto spe = getSpeed();
        return spe*d_*pow(10,num_)/myu_;
    }
    double getQ()
    {
        if(this->Q_ ==0)
        return re*myu_*pow(0.1,num_)*getA()/d_;
        else
        return this->Q_;
    }
    void setQ(double val)
    {
        this->Q_ = val;
    }
    double getHf(double lon)
    {
        auto spe = getSpeed();
        return getlambda()*(lon/d_)*pow(spe,2)/(2*9.8);
    }
    void setlambda(double sanjiao)
    {
        // this->lambda = 0.3164/pow(getRe(),0.25);
        // this->lambda = 1.0/(pow(2*log10l(3.7*d_/sanjiao),2));
        this->lambda = sanjiao;
    }
private:
    double Q_=0;
    double lambda = 0; 
    double d_=0;
    double myu_=0;
    double re = 0;
    int num_=0;
    double spe_=0;
};

class twoline
{
public:
    twoline(double start,double tail,double re,int times)
    {
        this->s = start;
        this->re = re;
        this->e = tail;
        this->accur = times;
    }
    bool compare(double val)
    {
        //set line function
        if(val == 0)throw runtime_error("zero is not permited!");
        auto val_1 = 0.2;
        auto val_2 = pow(10,val);
        // auto val_2 = -2*log10l(0.000244/(3.7*0.3048)+2.51/(re*val));
        // auto val_2 = 1/pow(2*log10l(3.7*100),2);
        return val_1>val_2;
    }
    double dowork()
    {
        this->status = compare(this->e);
        if(status == compare(this->s))abort();
        while(--accur)
        {
            // cout<<"test ok";
            mid = (s+e)/2;
            if(status == compare(mid))
            {
                e = mid;
            }
            else
            {
                s = mid;
            }
        }
        cout<<"mid:"<<this->mid<<endl;
        //process the result of lambda
        return mid;
    }
    bool status = 1;
    int accur = 7;
    double s = 0;
    double e = 0;
    double mid = 0;
    double re = 0;
};
void dotest()
{    
    twoline tl(0.00001,1,190415,1000);
    auto res = tl.dowork();

    double Q = 0;
    double lon = 4;
    double d = 15.0/1000;
    double myu = 1.306;
    double spe = 0.25;
    int num = 6;
    double cucao = 0.6/1000;
    shuitou tes;
    tes.Q_d_myu_num(Q,d,myu,num);
    // tes.Spe_d_myu_num(spe,d,myu,num);
    // tes.setlambda(0.045);
    // tes.setQ()
    tes.setRE(2000);
    cout<<"Q:"<<tes.getQ()<<endl;
    // cout<<"Δ/d:"<<cucao/d<<endl;
    cout<<"speed:"<<tes.getSpeed()<<"m/s"<<endl;
    cout<<"Re:"<<tes.getRe()<<endl;
    cout<<"lambda:"<<tes.getlambda()<<endl;
    cout<<"hf:"<<tes.getHf(lon)<<endl;
    // cout<<"hj:"<<(1.8*pow(tes.getSpeed(),2)/19.6)<<endl;
    // cout<<(0.131+0.163*pow(0.5,3.5))<<endl;

// cout<<1/pow(2*log10l(3.7*cucao/d),2);

}

    double densityofwater = 995.3;
    double myu = 0.784;
    int num = 6;
void handle()
{
    vector<double> lostP = {2.53,5.54,10.47,21.28,24.5,26.37};
    vector<double> Quene = {1.22,1.76,2.7,4,4.29,4.65};

    double lon = 1;
    double d = 15.0/1000;
    int i =0 ;
    cout<<"沿程损失："<<endl;
    cout<<"参数：ρ="<<densityofwater<<"kg/m^3   "<<"ν:"<<myu<<"*10^-6"<<endl;
    for_each(Quene.begin(),Quene.end(),[&](auto &a)
    {
        shuitou tes;
        tes.Q_d_myu_num(a/3600,d,myu,num);
        auto re = tes.getRe();
        auto cacu_lam = 2000*lostP[i++]*d/(pow(tes.getSpeed(),2)*lon*densityofwater);
        
        printf("Re:%.1f\t",re);
        // cout<<"lambda:"<<tes.getlambda()<<endl;
        cout<<"λ:"<<cacu_lam<<endl; 
        // cout<<"caculte_lambda:"<<cacu_lam<<endl;
    });
    
}

void tinylost()
{
    vector<double> p1 = {1.6,3.82,6.27,6.93,8.48};
    vector<double> p2 = {2.95,5.71,8.52,9.46,11.35};
    vector<double> Quene= {0.93,1.43,1.89,2.01,2.81};
    double d = 25.0/1000;
    cout<<"局部损失："<<endl;
    cout<<"参数：ρ="<<densityofwater<<"kg/m^3   "<<"ν:"<<myu<<"*10^-6"<<endl;
    for(int i=0;i<p1.size();i++)
    {
        double d1 = 25.0/1000;
        double d2 = 15.0/1000;
        shuitou tea1,tea2;
        tea2.Q_d_myu_num(Quene[i]/3600,d2,myu,num);
        tea1.Q_d_myu_num(Quene[i]/3600,d1,myu,num);
        // cout<<"Re:"<<tea.getRe()<<endl;
        // cout<<"lambda:"<<tes.getlambda()<<endl;  
        auto hf = 2*p1[i]-p2[i];
        auto res1 = 2000*hf/(densityofwater*pow(tea1.getSpeed(),2));
        auto res2 = 2000*hf/(densityofwater*pow(tea2.getSpeed(),2));

        auto A1A2 = tea1.getA()/tea2.getA();
        auto A2A1 = 1.0/A1A2;
        // cout<<"ζ1:"<<res1<<endl;   
        // cout<<"book ζ1:"<<pow(1-A1A2,2)<<endl;
        // cout<<"ζ2:"<<res2<<endl;
        
        printf("ζ:%.3f\n",res2);
        // cout<<"book ζ2:"<<pow(1-A2A1,2)<<endl;  
    }
}

void wenQL()
{
    vector<double> innerp = {0.84,1.57,3.69,7.94,16.81,23.78};
    vector<double> Quene = {0.81,1.18,1.81,2.67,3.99,4.88};


    double d = 20.0/1000;
    double sum = 0;
    cout<<"文丘里流量系数："<<endl;
    cout<<"参数：ρ="<<densityofwater<<"kg/m^3   "<<"ν:"<<myu<<"*10^-6"<<endl;
    for(int i=0;i<Quene.size();i++)
    {
        shuitou tea;
        tea.Q_d_myu_num(Quene[i]/3600,d,myu,num);
        auto spe = tea.getSpeed();
        auto Square = tea.getA();
        double para = pow(2*innerp[i]*1000/densityofwater,0.5);
        auto res = Quene[i]/(Square*3600*para);
        cout<<"μ:"<<res<<endl;
        sum+=res;
    }
    cout<<"μ平均值為："<<sum/Quene.size()<<endl;
}

int main()
{   
    // twoline tea(-1,0.1,0,1000);
    // tea.dowork();

    handle();
    tinylost();
    wenQL();
    // dotest();
    
    return 0;
}