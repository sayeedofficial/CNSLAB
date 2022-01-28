# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int connectToServer(const char* ip, int port)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port),inet_addr(ip)};
    
    if(connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
    {
        cout << "\nRun server program first." << endl; 
        exit(0);
    }
    else
        cout << "\nClient is connected to Server." << endl; 

    return sock;
}

int randInRange(int low, int high) // excluding high and low
{
    return (rand()%(high-(low+1))) + (low+1) ;
}

long powermod(long a, long b, long  q)
{
	long res=1;
	for(long i=0;i<b;i++)
		res=(res*a)%q;
	return res;
}

int main()
{
	//get ip address and port number
    char ip[50]; 
    cout << "\nEnter server's IP address: "; 
    cin >> ip;
    int port;    
    cout << "Enter port : "; 
    cin >> port;
    
    //create client socket and connect to server
    int sock = connectToServer(ip, port);
    
    //get porime number and its primitive root
	long q, alpha;
	cout<<"\nEnter a prime number, q : "; 
	cin >> q;
	cout<<"Enter primitive root of q, alpha : "; 
	cin >> alpha;
	
	// client's private key (1<Xa<q)
	srand(time(NULL));
	long Xc = randInRange(1, q); 
	cout<< "\nClient's private key, Xc = " << Xc <<endl;
	
	// client's public key
	long Yc = powermod(alpha, Xc, q); 
	
	// send client's public key
	send(sock, &Yc, sizeof(Yc), 0);	
	cout<< "Client's public key,  Yc = " << Yc <<endl;
	
	// recv server's public key
	long Ys; 
	recv(sock, &Ys, sizeof(Ys), 0);	 
	cout<< "\nServer's public key,  Ys = " << Ys <<endl;
	
	//create secret key
	long k = powermod(Ys,Xc,q);	
	cout<<"\nSecret Key, k = "<<k<<endl;

	//get cipher text
	long cipher;	
	recv(sock, &cipher, sizeof(cipher), 0);
	cout<<"\nMessage received from Server  : " << cipher << endl;
	
	// decryption
	long decipher = cipher ^ k;	
	cout << "Decrpyted message : " << decipher << endl << endl;
}

/* 
some values for q and alpha
q=11, alpha=2
q=71, alpha=7
Note: input q and alpha value same as server's 
*/

/*
Enter server's IP address: 127.0.0.1
Enter port : 4444

Client is connected to Server.

Enter a prime number, q : 11
Enter primitive root of q, alpha : 2

Client's private key, Xc = 4
Client's public key,  Yc = 5

Server's public key,  Ys = 1

Secret Key, k = 1

Message received from Server  : 452
Decrpyted message : 453
*/
