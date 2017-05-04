#include "huff.h"

using namespace std;

Huff::Huff()
{
for(int i=0;i<256;i++)
{frequency[i]=0;}
length=0;
}
void Huff::CodeForPacker(Node *ob)
{
if(ob->left!=NULL)
	{
	code.push_back(false);
	CodeForPacker(ob->left);
	code.pop_back();
	}
if(ob->right!=NULL)
	{
	code.push_back(true);
	CodeForPacker(ob->right);
	code.pop_back();
	}
if(ob->sim)
	{
	optcode[ob->sim]=code;
	}
}
int Huff::BuildThree()
{	
list <Node>::iterator It1;
list <Node>::iterator It2;
Node *left, *right;
list <Node> three;
for(int i=0;i<256;i++)
	{
	Node ob(frequency[i],i);
	three.push_back(ob);
	}
while(three.size()!=1)
	{
	It1=three.begin();
	It2=three.begin();
	while(It2!=three.end())
		{
		if(*It1 > *It2)It1=It2;
		It2++;
		}
	left = new Node(*It1);
	three.erase(It1);
	It1=three.begin();
	It2=three.begin();
	while(It2!=three.end())
		{
		if(*It1 > *It2)It1=It2;
		It2++;
		}
	right = new Node(*It1);
	three.erase(It1);
	parent=new Node (left, right);
	three.push_front(*parent);	
	}	
}
int Huff::packer(const char * ifile,const char * ofile)
{
unsigned char cc;
unsigned char byte;
ifstream fin  (ifile);
if (!fin) 
	{
	return 1;
	}
fin.unsetf (std::ios::skipws);
ofstream fout (ofile);
fin>>cc;
while(!fin.eof())
	{
	frequency[cc]++;
	fin>>cc;
	}
fin.close();
fin.open(ifile);
fin.unsetf (std::ios::skipws);
BuildThree();
CodeForPacker(parent);
(*parent).DeleteNode();
fout << 'H' << 'U' << 'F' << 'F';
for(int i=0;i<256;i++)
	{
	frequency[i]=htonl(frequency[i]);
	fout << frequency[i];
	}
byte = 0;
length = 0;
fin >> cc;
while(!fin.eof())
	{cout<<cc<<endl;
	code=optcode[cc];
	for(int i=0;i<code.size();i++)
		{
		if(code[i]==true)byte|(0x80 >> length);
		if(code[i]==true)byte&(~(0x80 >> length));
		if(length==7)
			{
			length=0;
			fout << byte;
			byte = 0;
			}
		else 
			{length++;}
		}
	fin >> cc;
	}
fin.close();
fout.close();
delete parent;
return 0;		
}
int Huff::unpacker(const char * ifile,const char * ofile)
{
unsigned char c;
ifstream fin  (ifile);
if (!fin) 
	{
	return 1;
	}
fin.unsetf (std::ios::skipws);
ofstream fout (ofile);
fin >> c;
if(c!='H')return 1;
fin >> c;
if(c!='U')return 1;
fin >> c;
if(c!='F')return 1;
fin >> c;
if(c!='F')return 1;
for(int i=0;i<256;i++)
	{
	fin >> frequency[i];
	frequency[i]=ntohl(frequency[i]);
	}
BuildThree();
fin >> c;
temp=parent;
while(!fin.eof())
	{
	if((c & (0x80 >> length))!=0)temp=(temp->right);
	else
		{
		temp=(temp->left);
		}
	length++;
	if(length==8)
		{
		length=0;
		fin >> c;
		}
	if((temp->sim)!=0)
		{
		fout << temp->sim;
		temp=parent;
		}
	}
fin.close();
fout.close();
(*parent).DeleteNode();
delete parent;
return 0;
}
