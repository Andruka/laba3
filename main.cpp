#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>
#include <arpa/inet.h>
using namespace std;
int main()
{
int type;
char * ifile;
char * ofile;
Huff ob;
cout<<"Выберите действие:"<<endl;
cout<<"1-упаковать файл"<<endl;
cout<<"2-распаковать файл"<<endl;
cin>>type;
cout<<"Введите имя файла на вход"<<endl;
cin>>ifile;
cout<<"Введите имя файла на выход"<<endl;
cin>>ofile;
if(type==1)
	{
	ob.packer(ifile,ofile);
	cout<<"Упаковка завершена"<<endl;
	}
}
