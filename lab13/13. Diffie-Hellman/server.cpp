# include <bits/stdc++.h>
# include <arpa/inet.h> 
using namespace std;

int createServer(int port)  // TCP connection
{
	//create server socket and address
	int sersock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(port), INADDR_ANY};
    
    bind(sersock, (struct sockaddr *) &addr, sizeof(addr));
    cout << "\nServer Online. Waiting for client...." << endl;
    
    listen(sersock, 5);
    int sock = accept(sersock, NULL, NULL);
    cout << "Connection Established." << endl;
    return sock;
}

int randInRange(int low, int high) // excluding high and low
{
    return (rand()%(high-(low+1))) + (low+1) ;
}

long powermod(long a, long b, long  q)
{
	long res=1;
	for(long i=0; i<b; i++)
		res=(res*a)%q;
	return res;
}

int main()
{
	//get port 
    int port; 
    cout << "\nEnter port : "; 
    cin >> port;
    
    //create server socket
    int sock = createServer(port);
	
	//get prime number and its primitive root
	long q, alpha;
	cout<<"\nEnter a prime number, q : "; 
	cin >> q;
	cout<<"Enter primitive root of q, alpha : "; 
	cin >> alpha;
	
	//get client's public key 
	long Yc; 
	recv(sock, &Yc, sizeof(Yc), 0);
	cout<< "\nClient's public key,  Yc = " << Yc <<endl;
	
	//create server's private key
	srand(time(NULL));
	long Xs = randInRange(1, q); 
	cout<< "\nServer's private key, Xs = " << Xs <<endl;
	
	// server's public key
	long Ys = powermod(alpha, Xs, q); 
	
	// send server's public key
	send(sock, &Ys, sizeof(Ys), 0);	 
	cout<< "Server's public key,  Ys = " << Ys <<endl;
	
	//create secret key
	long k = powermod(Yc,Xs,q);	
	cout<<"\nSecret Key, k = "<<k<<endl;

	//get message
	long msg;
	cout<<"\nEnter a message(number) to send : "; 
	cin>>msg;
	
	// encryption
	long cipher = msg ^ k; 
	send(sock, &cipher, sizeof(cipher), 0);
	cout << "Encrypted msg sent to client: " << cipher << endl << endl;
}

/* 
some values for q and alpha
q=11, alpha=2
q=71, alpha=7
*/

/*
Enter port : 4444

Server Online. Waiting for client....
Connection Established.

Enter a prime number, q : 11
Enter primitive root of q, alpha : 2

Client's public key,  Yc = 5

Server's private key, Xs = 10
Server's public key,  Ys = 1

Secret Key, k = 1

Enter a message(number) to send : 453
Encrypted msg sent to client: 452
*/
