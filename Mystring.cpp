#include<iostream>
#include<string>
#include<vector>
#include<functional>
#include<algorithm>
#include<numeric>
using namespace std;

class MyString
{
public:
    MyString(){}
    MyString(const char* s)
    {
        size_t = getsize(s);
        init(s);
    }
    MyString(MyString &s)
    {
        this->size_t = s.size_t;
        this->p = new char[s.size_t+1];
        for(int i=1;i<=size_t;++i)
        {
            p[i] = s[i];
        }
    }
    MyString(MyString &&s)
    {
        
    }
    ~MyString()
    {
        if(p != nullptr)
        {
            // cout<<"successful to delete num array;"<<endl;
            delete []p;
        }
    }
    int sizeVal()
    {
        return size_t;
    }
    int find(const MyString &s)
    {
        int s_length = s.size_t;
        int this_length = size_t;
        if(s_length>this_length)return 0;
        int j = 0;
        int i = 1;
        while(i<=this_length&&j<=s_length)
        {
            if(j==0||p[i]==s.p[j])
            {
                ++i;
                ++j;
            }
            else
            {
                i = i-j+2;
                j=1;
            }
        }
        // cout<<j<<"   "<<s_length<<endl;
        if(j>s_length)return i-j+1;
        else return 0;
    }
    int kmp_find(const MyString &s)
    {       
        int next[s.size_t+1];
        get_nextval(s,next); 
        int s_length = s.size_t;
        int this_length = size_t;
        if(s_length>this_length)return 0;
        int j = 0;
        int i = 1;
        while(i<=this_length&&j<=s_length)
        {
            if(j==0||p[i]==s[j])
            {
                ++i;
                ++j;
            }
            else
            {
                j=next[j];
            }
        }
        // cout<<j<<"   "<<s_length<<endl;
        if(j>s_length)return i-j+1;
        else return 0;
        return 1;
    }
    int replace(const MyString &beReplaced,const MyString &newVal)
    {

        int pos = kmp_find(beReplaced);
        if(!pos)return 0;
        int oldSize = beReplaced.size_t;
        int newSize = newVal.size_t;
        if(newSize>oldSize)
        {
            int i=1;
            char *newp = new char[size_t+newSize-oldSize+1];
            for(;i<pos;++i)
            {
                newp[i] = p[i];
            }
            for(int j=1;j<=newSize;++j)
            {
                newp[i+j-1] = newVal.p[j];
            }
            for(int j=0;pos+oldSize+j<=size_t;++j)
            {
                newp[i+newSize+j]=p[pos+oldSize+j];
            }
            delete [] p;
            p = newp;
            size_t = size_t-oldSize+newSize;
        }
        return 1;
    }
    void print()
    {
        for(int i=1;i<=size_t;i++)cout<<p[i];
        cout<<endl;
    }
private:
    char& operator[](int n) const
    {
        return this->p[n];
    }
    char& operator[](int n) 
    {
        return this->p[n];
    }
    void get_next(const MyString& s,int next[])
    {
        int i = 1;
        next[1] = 0;
        int j = 0;
        while(i<=s.size_t)
        {
            if(j==0||s[i]==s[j])
            {
                ++i;
                ++j;
                next[i] = j;
            }
            else
            j = next[j];
        }
    }
    void get_nextval(const MyString &s,int nextval[])
    {
        int i = 1;
        nextval[1] = 0;
        int j = 0;
        while(i<=s.size_t)
        {
            if(j==0||s[i]==s[j])
            {
                ++i;
                ++j;
                if(s[j]!=s[i])nextval[i]=j;
                else nextval[i] = nextval[j];
            }
            else j = nextval[j];
        }
        
    }
    void init(const char* s)
    {
        p = new char[size_t+1];
        for(int i=1;i<=size_t;++i)
        {
            p[i] = s[i-1];
        }
    }    
    int getsize(const char* s)
    {
        int size = 0;
        while(s[size++] != '\0');
        return size-1;
    }
    int size_t = 0;
    int max_size = 0;
    char* p = nullptr;
};

void test()
{
    MyString str("python is general lauguage");
    str.print();
    str.replace("general","scripting");
    str.print();
}

int main()
{
    test();
    return 0;
}