#include <bits/stdc++.h>
using namespace std;

char uniqtext[26];

string readplaintext()
{
	ifstream fin;//input file stream(just like cin for files)
	string ptext;
	fin.open("Plaintext.txt");
	fin>>ptext;
	fin.close();
	return ptext;
}

void writeciphertext(string ctext)
{
	ofstream fout;
	fout.open("Ciphertext.txt");
	fout<<ctext;
	fout.close();
}

void permute(char a[],int l,int r,vector<string>& keyspace)//keyspace pass by reference
{
	if(l==r)//base case
		keyspace.push_back(a);
	else
	{
		for(int i=l;i<=r;i++)
		{
			swap(a[l],a[i]);
			permute(a,l+1,r,keyspace);
			swap(a[l],a[i]);
		}
	}
}

vector<string> genkeyspace(string plaintext)
{
	vector<string> keyspace;
	
	set<char> uniqset;
	for(int i=0;i<plaintext.length();i++)
		uniqset.insert(plaintext[i]);
	
	int count=0;
	for(set<char>::iterator it=uniqset.begin() ; it!=uniqset.end() ; it++)
		uniqtext[count++]=(*it);
	
	permute(uniqtext,0,strlen(uniqtext)-1,keyspace);
	
	return keyspace;
}

string encrypt(string PT,string unique,string key)
{
	string CT="";
	for(int i=0;i<PT.length();i++)
	{
		int idx = unique.find(PT[i]);
		CT+=key[idx];
	}
	return CT;
}

void showfrequency(string PT,string CT)
{
	//hashmaps
	map<char,int> mplain;
	map<char,int> mcipher;
	
	for(int i=0;i<PT.length();i++)
	{
		mplain[PT[i]]++;
		mcipher[CT[i]]++;
	}
	
	cout<<"FREQUENCY"<<"\tPLAINTEXT"<<"\tCIPHERTEXT"<<endl;
	for(int i=0;i<PT.length();i++)
	{
		float freq= (float)mplain[PT[i]]/PT.length();
		cout<<freq<<"\t\t"<<PT[i]<<"\t\t"<<CT[i]<<endl;
	}
}

int main()
{
	//getting plaintext
	string plaintext = readplaintext(); 
	cout<<"Plaintext is "<<plaintext<<endl;
	
	//generating keyspace
	vector<string> keyspace = genkeyspace(plaintext);
	
	//get a random key from keyspace 
	srand(time(NULL));
	string key = keyspace[rand()%keyspace.size()];
	cout<<"Key is "<<key<<endl;
	
	//encryption
	string CT=encrypt(plaintext,uniqtext,key);
	cout<<"Cipher text is "<<CT<<endl;
	
	//write cipher text to file
	writeciphertext(CT);
	
	showfrequency(plaintext,CT);
	return 0;
}
