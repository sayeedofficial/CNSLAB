#include <bits/stdc++.h>
using namespace std;

typedef struct{
	int row;
	int col;
}position;

char mat[5][5];

void generatematrix(string key)
{
	int flag[26]={0};//to monitor alphabets present in key
	int x=0,y=0;//row and column of matrix
	
	//creating intitial matrix with alphabets present in key
	for(int i=0;i<key.length();i++)
	{
		//considering i and j as i
		if(key[i]=='j')
			key[i]='i';
		//if character is not in matrix
		if(flag[key[i]-'a']==0)
		{
			mat[x][y++]=key[i];
			flag[key[i]-'a']=1;
		}
		//if one row is exhausted move to next row
		if(y==5)
		{
			x++;
			y=0;
		}
	}
	
	//checking for all alphabets
	for(char ch='a';ch<='z';ch++)
	{
		if(ch=='j')
			continue;
		if(flag[ch-'a']==0)
		{
			mat[x][y++]=ch;
			flag[ch-'a']=1;
		}		
		if(y==5)
		{
			x++;
			y=0;
		}
	}
}

string formatmessage(string msg)
{
	//convert all j into i in plaintext
	for(int i=0;i<msg.length();i++)
		if(msg[i]=='j')
			msg[i]='i';
			
	//if duplicates are present in pairs insert x inbetween them
	for(int i=1;i<msg.length();i+=2)
		if(msg[i-1]==msg[i])
			msg.insert(i,"x");
	
	//if plaintext is odd insert x as filler
	if(msg.length()%2!=0)
		msg+='x';
		
	return msg;
}

position getposition(char c)
{
	position p;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			if(c==mat[i][j])
			{
				p={i,j};
				return p;
			}
		}
	}
	return p;
}

string encrypt(string message)
{
	string ctext;
	for(int i=0;i<message.length();i+=2)
	{
		//get positions of two characters in pair
		position p1 = getposition(message[i]);
		position p2 = getposition(message[i+1]);
		int x1=p1.row;
		int y1=p1.col;
		int x2=p2.row;
		int y2=p2.col;
		
		//characters are in same row
		if(x1==x2)
		{
			ctext.append(1,mat[x1][(y1+1)%5]);
			ctext.append(1,mat[x2][(y2+1)%5]);
		}
		//characters are in same column
		else if(y1==y2)
		{
			ctext.append(1,mat[(x1+1)%5][y1]);
			ctext.append(1,mat[(x2+1)%5][y2]);
		}
		//characters forming rectangle
		else
		{
			ctext.append(1,mat[x1][y2]);
			ctext.append(1,mat[x2][y1]);
		}
	}
	return ctext;
}

string decrypt(string message)
{
	string ptext;
	for(int i=0;i<message.length();i+=2)
	{
		//get positions of characters in matrix
		position p1 = getposition(message[i]);
		position p2 = getposition(message[i+1]);
		int x1=p1.row;
		int y1=p1.col;
		int x2=p2.row;
		int y2=p2.col;
		
		if(x1==x2)//same row
		{
			ptext.append(1,mat[x1][--y1<0?4:y1]);
			ptext.append(1,mat[x2][--y2<0?4:y2]);
		}
		else if(y1==y2)//same column
		{
			ptext.append(1,mat[--x1<0?4:x1][y1]);
			ptext.append(1,mat[--x2<0?4:x2][y2]);
		}
		else
		{
			ptext.append(1,mat[x1][y2]);
			ptext.append(1,mat[x2][y1]);
		}
	}
	return ptext;
}

int main()
{
	//get plaintext
	string plaintext;
	cout<<"Enter message:";
	cin>>plaintext;
	
	//get number of keys
	int n;
	cout<<"Enter number of keys:";
	cin>>n;
	
	string key[n];//string array of keys
	for(int i=0;i<n;i++)
	{
		//get key
		cout<<"\nEnter key"<<i+1<<":";
		cin>>key[i];
		
		//generate playfair matrix and print
		generatematrix(key[i]);
		cout<<"\nKey "<<i+1<<" Matrix"<<endl;
		for(int k=0;k<5;k++)
		{
			for(int j=0;j<5;j++)
			{
				cout<<mat[k][j]<<" ";
			}
			cout<<endl;
		}
		
		//formatting message
		cout<<"Actual message: "<<plaintext<<endl;
		string fmsg= formatmessage(plaintext);
		cout<<"Formatted message: "<<fmsg<<endl;
		
		//encryption
		string ciphertext=encrypt(fmsg);
		cout<<"Encrypted message: "<<ciphertext<<endl;
		
		//decryption
		string decryptmessage=decrypt(ciphertext);
		cout<<"Decrypted message: "<<decryptmessage<<endl;
	}
	return 0;
}



