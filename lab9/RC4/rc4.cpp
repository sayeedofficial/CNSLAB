#include <bits/stdc++.h>
using namespace std;

int main()
{
	//getting plaintext
	string plaintext;
	cout<<"Enter message : ";
	cin>>plaintext;
	int n = plaintext.length();
	
	//converting to ASCII
	int pt[256];
	cout<<"Plain text : ";
	for(int i=0;i<n;i++)
	{
		pt[i] = (int)plaintext[i];
		cout<<pt[i]<<" ";
	}
	
	//getting key
	string key;
	cout<<"Enter key : ";
	cin>>key;
	
	//initialization
	int S[256],T[256];
	for(int i=0;i<256;i++)
	{
		S[i] = i;
		T[i] = (int)key[i%key.length()];//converting to ascii 
	}
	
	//initial permutation
	int j=0;
    for(int i=0; i<256; i++)
    {
        j = (j + S[i] + T[i]) % 256;
        swap(S[i], S[j]);
    }
    
    //keystream generation
    int keyStream[256];
    cout << "\nKey Stream : ";
    j=0;
    for(int i=0; i<n; i++) //generate keystream of same length as plaintext
    {
        j = (j + S[i]) % 256;
        swap(S[i], S[j]);
        int t = (S[i] + S[j]) % 256;
        keyStream[i] = S[t];
        cout << keyStream[i] << " ";
    }
    
    //Encryption
    int ct[256];
    cout<<"\n\nENCRYPTION"<<endl;
    cout << "Cipher Text \t: ";
    for(int i=0; i<n; i++)
    {
        ct[i] = pt[i] ^ keyStream[i]; // xor
        cout << ct[i] << " ";
    }
	
	//decryption
	cout<<"\n\nDECRYPTION"<<endl;
	int dt[256];
	string dtString ="";
	cout << "Decrypted text \t: " ;
    for(int i=0; i<n; i++)
    {
        dt[i] = ct[i] ^ keyStream[i];
        cout << dt[i] << " ";
        dtString += (char)dt[i]; // change ASCII value to char
    }
    cout << "\nDecrypted text \t: " << dtString << endl;
	
	return 0;
}
