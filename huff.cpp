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
  if(ob->left==NULL && ob->right==NULL)
    {
      optcode[ob->sim]=code;
      if(code.size() > maxcode.size())
	   {
	   maxcode=code;
	   }
    }
}
list <Node>::iterator Huff::PopMin(list <Node> & three)
{
  list <Node>::iterator It1=three.begin();
  list <Node>::iterator It2=three.begin();
      It1=three.begin();
      It2=three.begin();
      while(It2!=three.end())
	{
	  if(*It1 > *It2)It1=It2;
	  It2++;
	}
   return It1;
}

int Huff::BuildThree()
{	
  list <Node>::iterator It1;
  Node *left, *right;
  list <Node> three;
  for(int i=0;i<256;i++)
    {
      Node ob(frequency[i],i);
      three.push_back(ob);
    }
  while(three.size()!=1)
    {
      It1=PopMin(three);
      left = new Node(*It1);
      three.erase(It1);
      It1=PopMin(three);
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
      fout.write((char*)&frequency[i], sizeof(uint32_t));
    }
  byte = length = 0;
  fin >> cc;
  while(!fin.eof())
    {//cout<<cc<<endl;
      code=optcode[cc];
      for(int i=0; i<code.size(); ++i)
	{
	  if(code[i]==true) byte|=(0x80 >> length);
	  //if(code[i]==false)byte&(~(0x80 >> length));
	  if(length == 7)
	    {
	      fout << byte;
	      byte = length = 0;
	    }
	  else 
	    {++length;}
	}
      fin >> cc;
    }
  if(length!=0)
	{
	int size=0;
	while(length!=8)
		{
		if(maxcode[size]==true) byte|=(0x80 >> length);
		++size;
		++length;
		}
	fout << byte;
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
      fin.read((char*)&frequency[i], sizeof(uint32_t));
      frequency[i]=ntohl(frequency[i]);
    }
  BuildThree();
  fin >> c;
  temp=parent;
  while(!fin.eof())
    {
      for( int bit = 0; bit < 8; ++bit) {		
	if((c & (0x80 >> bit))!=0) {
	  temp=(temp->right);
	} else {
	  temp=(temp->left);
	}
	if(temp->left==NULL && temp->right==NULL)
	  {
	    fout << temp->sim;
	    temp=parent;
	  }
      }
      fin >> c;
      /*
	if((c & (0x80 >> length))!=0)temp=(temp->right);
	else
	{
	temp=(temp->left);
	}
	if(length==7)
	{
	length=0;
	fin >> c;
	}
	else {length++;}
	if((temp->left)==NULL)
	{
	fout << temp->sim;
	temp=parent;
	}*/
    }
  fin.close();
  fout.close();
  (*parent).DeleteNode();
  delete parent;
  return 0;
}
