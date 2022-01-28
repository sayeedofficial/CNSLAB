#include <bits/stdc++.h>
using namespace std;

string encrypt(string pt,int key[][3],int order)
{
	string cipher="";
	
	//append fillers
	int fillers = (pt.length() % order);
	while (fillers<order && fillers!=0)
	{
		pt += 'z';
		fillers++;
	}
	cout<<"Plaintext for encryption: "<<pt<<endl;
	
	//construction of plaintext matrix
	int row = pt.length()/order;
	int col = order;
	int pt_matrix[row][col];
	int k=0;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			pt_matrix[i][j] = pt[k++] - 'a';
	
	int ct_matrix[row][col];//cipher text matrix
	
	//matrix multiplication
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			ct_matrix[i][j] = 0;
			for(int k=0;k<order;k++)
			{
				ct_matrix[i][j] += pt_matrix[i][k] * key[k][j];
				ct_matrix[i][j] %= 26;
			}
			cipher += (char)('a' + ct_matrix[i][j]);
		}
	}
	return cipher;
}

int get_determinant(int key[][3],int order)
{
	int det;
	if(order == 2)
		det = key[0][0]*key[1][1] - key[1][0]*key[0][1];
	else
	{
		det = key[0][0]*(key[1][1]*key[2][2] - key[2][1]*key[1][2]) - key[0][1]*(key[1][0]*key[2][2] - key[2][0]*key[1][2]) + key[0][2]*(key[1][0]*key[2][1]-key[2][0]*key[1][1]);
	}
	det%=26;
	if(det<0)
		return det+26;
	return det;
}

int gcdext(int a,int b)
{
	int q,r,t,t1=0,t2=1;
	while(b!=0)
	{
		q = a/b;
		r = a % b;
		t = t1-q*t2;
		
		a=b;
		b=r;
		t1=t2;
		t2=t; 
	}
	if(t1<0)
		t1+=26;
	return t1;
}

int getminor(int key[][3],int order,int i,int j)
{
	if(order==2)
	{
		i = i==0? 1:0;// 00->11 | 01->10 | 10->01 | 11->00
		j = j==0? 1:0;
		return key[i][j];
	}
	if(order==3)
	{
		if(i==0 && j==0)
			return key[1][1]*key[2][2] - key[2][1]*key[1][2];
		if(i==0 && j==1)
			return key[1][0]*key[2][2] - key[2][0]*key[1][2];
		if(i==0 && j==2)
			return key[1][0]*key[2][1] - key[2][0]*key[1][1];
		if(i==1 && j==0)
			return key[0][1]*key[2][2] - key[2][1]*key[0][2];
		if(i==1 && j==1)
			return key[0][0]*key[2][2] - key[2][0]*key[0][2];
		if(i==1 && j==2)
			return key[0][0]*key[2][1] - key[0][1]*key[2][0];
		if(i==2 && j==0)
			return key[0][1]*key[1][2] - key[1][1]*key[0][2];
		if(i==2 && j==1)
			return key[0][0]*key[1][2] - key[1][0]*key[0][2];
		if(i==2 && j==2)
			return key[0][0]*key[1][1] - key[1][0]*key[0][1];
	}
	return 0;
}

string decrypt(string ct,int key[][3],int order)
{
	string msg = "";
		
	//get the determiinant of key matrix
	int determinant = get_determinant(key,order);
	
	//get multiplicative inverseof determinant using extended euclidean
	int mulinverse = gcdext(26,determinant);
	
	//getting adjoint of key matrix
	int adj[3][3];
	for(int i=0;i<order;i++)
	{
		for(int j=0;j<order;j++)
		{
			int sign;
			if((i+j)%2)
				sign = -1;
			else
				sign = +1;
			adj[j][i] = sign*getminor(key,order,i,j);//call minor function
		}
	}
	
	//calculate inverse of key matrix
	int inverse[3][3];
	for(int i=0;i<order;i++)
	{
		for(int j=0;j<order;j++)
		{
			inverse[i][j] = (mulinverse*adj[i][j])%26;
			if(inverse[i][j]<0)
				inverse[i][j]+=26;
		}
	}
		
	//construct cipher matrix
	int row = ct.length()/order;
	int col = order;
	int ct_matrix[row][col];
	int k=0;
	for(int i=0;i<row;i++)
		for(int j=0;j<col;j++)
			ct_matrix[i][j] = ct[k++] - 'a';
			
	//calculate plain text matrix
	int pt_matrix[row][col];
	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			pt_matrix[i][j] = 0;
			for(int k=0;k<order;k++)
			{
				pt_matrix[i][j] += ct_matrix[i][k] * inverse[k][j];
				pt_matrix[i][j] %= 26;
			}
			msg += (char)('a' + pt_matrix[i][j]);
		}
	}
	return msg;
}

int main()
{
	cout<<"HILL CIPHER"<<endl;
	
	//get order of key
	int order;
	cout<<"Enter the order of key matrix : ";
	cin>>order;
	
	//get the key matrix
	int key[3][3];
	cout<<"Enter the key matrix :"<<endl;
	for(int i=0;i<order;i++)
		for(int j=0;j<order;j++)
			cin>>key[i][j];
			
	//get plaintext
	string plaintext;
	cout<<"Enter the plaintext : ";
	cin>>plaintext;
	
	cout<<"\nENCRYPTION"<<endl;
	string ciphertext = encrypt(plaintext,key,order);
	cout<<"Ciphertext is : "<<ciphertext<<endl;
	
	cout<<"\nDECRYPTION"<<endl;;
	string decrypted = decrypt(ciphertext,key,order);
	cout<<"Decrypted text is : "<<decrypted<<endl;
	
	return 0;	
}
