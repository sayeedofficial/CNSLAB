#include <bits/stdc++.h>
using namespace std;

string encrypt( string pt,string key)
{
	string ct="";
	
	//calculate row and column
	int row = ceil((float)pt.length()/key.length());
	int col = key.length();
	
	//construct matrix
	char mat[row][col];
	int k=0;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			if(pt[k])
				mat[i][j]=pt[k++];
			else
				mat[i][j]='#';	
	
	cout<<"Encryption matrix"<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<mat[i][j]<<"\t";
		cout<<endl;
	}
	
	for(int i=0;i<col;i++)
		for(int j=0;j<row;j++)
			ct += mat[j][key.find(i+'1')];
	
	return ct;
}

string decrypt( string ct, string key)
{
	string pt="";
	
	//get row and column
	int row = ceil((float)ct.length()/key.length());
	int col = key.length();
	
	//construct matrix
	char mat[row][col];
	int k=0;
	for(int i=0;i<col;i++)
		for(int j=0;j<row;j++)
			mat[j][key.find(i+'1')]=ct[k++];
	
	cout<<"Decryption matrix"<<endl;
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
			cout<<mat[i][j]<<"\t";
		cout<<endl;
	}
	
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			if(mat[i][j]!='#')
				pt += mat[i][j];
	
	return pt;
}

int main()
{
	cout<<"TRANSPOSITION CIPHER TECHNIQUE\n\n";
	
	//get plain text
	string plain_text;
	cout<<"Enter the plaintext: ";
	cin>>plain_text;
	
	//get key
	string key;
	cout<<"\nEnter the key: ";
	cin>>key;
	
	cout<<"\nENCRYPTION\n"<<endl;
	string cipher_text = encrypt(plain_text,key);
	cout<<"\nCipher Text is "<<cipher_text<<endl;
	
	cout<<"\nDECRYPTION\n"<<endl;
	string decrypt_text = decrypt(cipher_text,key);
	cout<<"\nDecrypted text is "<<decrypt_text<<endl;
	
	return 0;
}


