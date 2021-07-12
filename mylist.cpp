#include<iostream>



template<typename T>
class fwlinklist
{
public:
    fwlinklist();  
    virtual void reverseList();
    virtual void mergeList(const fwlinklist* lhs, const fwlinklist* rhs);
    virtual bool rdel(int n);
    virtual void append(const T&);
    // virtual bool insertBeforeVal(int val);
    void print();
private:
    typedef struct datap
    {
        T datas;
        datap* next;
    }dataptr; 
    dataptr* header,*tail;
protected:
    virtual void todata(const T&,dataptr*);
    void init();
};

template<typename T>
void fwlinklist<T>::print()
{
    if(header==nullptr)return;
    dataptr *next = header;
    while (next)
    {
        printf("%d%s",next->datas," ");
        next = next->next;
    }   
}
template<typename T>
fwlinklist<T>::fwlinklist()
{
    this->init();
}
template<typename T>
void fwlinklist<T>::init()
{
    this->header = nullptr;
    this->tail = nullptr;
}
template<typename T>
inline void fwlinklist<T>::todata(const T& val,dataptr *dt)
{
    dt->datas = val;
    dt->next = nullptr;
}
template<typename T>
void fwlinklist<T>::append(const T& new_val)
{
    dataptr *temp = new dataptr;
    todata(new_val,temp);
    if(tail==nullptr)
    {
        tail = temp;
    }
    else
    {
        tail->next = temp;
        tail = temp;
    }
    if(header==nullptr)header = temp;
}
template<typename T>
void fwlinklist<T>::mergeList(const fwlinklist* lhs, const fwlinklist* rhs)
{
 
}
template<typename T>
bool fwlinklist<T>::rdel(int n)
{
    return true;
}
template<typename T>
void fwlinklist<T>::reverseList()
{
    if(header==nullptr||header==tail)return;
    dataptr* next = header->next;
    dataptr* cur = header;
    dataptr* temp = cur;
    while(temp)
    {
        temp = next->next;
        next->next = cur;
        cur = next;
        next = temp;
    }
    tail = header;
    tail->next = nullptr;
    header = cur;
}

template<typename T>
class dolinklist : public fwlinklist<T>
{
public:
    
private:
    typedef struct datap
    {
        T datas;
        datap* next;
        datap* pre;
    }dataptr; 
    dataptr *header,*tail;
    bool is_reversed = false;
    void reverseList() override;
    void test()
    {
        header->next = nullptr;
    }

    
};

template<typename T>
void dolinklist<T>::reverseList()
{

}




void test()
{
    fwlinklist<int> t;
    int i = 8;
    while(i--)
    {
        t.append(i);
    }
    t.reverseList();
    t.print();
}

int main()
{
    test();
    return 0;
}