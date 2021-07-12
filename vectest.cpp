#include<vector>
#include<string>
#include<iostream>
using namespace std;
void test(char *s)
{
	string str(s);
	cout<<str<<endl;
}

int main(int argc,char **argv)
{
	test();			
	if(argc<2)
	{
		cerr<<"less arg"<<endl;
		return -1;
	}
	test(argv[1]);
	return 0;
}
