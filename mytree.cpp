#include<iostream>

using namespace std;

template<typename T>
class mytree
{
public:
    typedef struct datap
    {
        T datas;
        datap* lchild;
        datap* rchild;
    }dataptr;
    mytree() = default;
    void append(const T&);
    void Inorder();
private:
    dataptr *root = nullptr;
};

template<typename T>
void mytree<T>::append(const T& val)
{
    dataptr* temp = new dataptr;
    temp->datas = val;
}