#include<bits/stdc++.h>
using namespace std;

//48 bit expansion table consisting of 1 to 32
int E[]={ 32, 1, 2, 3, 4, 5,
		   4, 5, 6, 7, 8, 9,
		   8, 9,10,11,12,13,
		  12,13,14,15,16,17,
          16,17,18,19,20,21,
		  20,21,22,23,24,25,
		  24,25,26,27,28,29,
		  28,29,30,31,32, 1 };

string expansionPermute(string input)
{
	string res="";
	for(int i=0;i<48;i++)
		res += input[E[i]-1];
	return res;
}

string XOR(string input1,string input2)
{
	string res="";
	for(int i=0;i<input1.length();i++)
		res += (input1[i]==input2[i])? "0" : "1";//if same then zero else one
    return res;
}

int main()
{
	//get round number [optional]
	/*int	i;
	cout<<"\nEnter Round number(i):";
	cin>>i;*/
	
	//input (i-1)th round output
	unsigned long long hexInput;
    cout<<"Enter 64-bit(i-1)th round output in hex:";
	cin>>hex>>hexInput;
	
	//convert to binary
	string input = bitset<64>(hexInput).to_string();
    cout<<"\n64-bitBinaryInput="<<input<<endl;
    
    // optional if key is taken as input from user
    //get ith round key(48 bit) [can be input from user]
    /*string Ki;
	ifstream fin;
	fin.open("keygen.txt");
	for(int j=1;j<=i;j++)
		fin>>Ki;	
	if(Ki.length()==0)
	{
		cout<<"\nkeygen.txt not found!!!\n"<<endl;
		exit(1);
	}*/
	unsigned long long hexkey;
	cout<<"\nEnter 48 bit key in hexadecimal format : ";
	cin>>hex>>hexkey;
	string Ki = bitset<48>(hexkey).to_string();
	cout<<"keyforithround(Ki)="<<Ki<<endl;

	//extract right 32 bits
	string Ri_1 = input.substr(32,32);//32 bit Right half of inputR[i-1]
	cout<<"\nRight half of 64-bit input , Ri_1= "<<Ri_1<<endl;

	//expand right 32 bits
	string R48 = expansionPermute(Ri_1);
	cout<<"Ri_1 after expansion permutation = "<<R48<<endl;
	
	//XOR with 48 bit key
    string sBoxInput = XOR(R48,Ki);
	cout<<"\nInput to s-box: "<<sBoxInput<<endl<<endl;
	
    return 0;
}
