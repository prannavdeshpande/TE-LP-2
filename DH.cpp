#include<iostream>
#include<windows.h>
using namespace std;

long long int modExp(long long int base, long long int exp, long long int mod){
  base = base %mod;
  long long int result = 1;
  while(exp>0){
    if(exp%2==1){
      result = (result*base)%mod;
    }
    base = (base*base)%mod;
    exp = exp/2;
  }
  return result;
}

int main(){
  long long int n,g;
  cout<<"Enter the value of n (large prime number) : ";
  cin>>n;
  cout<<"Enter the value of g (primitive root of n) : ";
  cin>>g;

  long long int Xa, Xb; // Private keys of A and B
  cout<<"Alice selecting random number as private key..."<<endl;  cout<<endl;
  Sleep(3000);  
  Xa = rand()%(n-2) + 2;
  cout<<"Alice selected "<<Xa<<" as private key. "<<endl;  cout<<endl;

  cout<<"Bob selecting random number as private key..."<<endl;  cout<<endl;
  Sleep(3000);  
  Xb = rand()%(n-2) + 2;
  cout<<"Bob selected "<<Xb<<" as private key. "<<endl;  cout<<endl;

  Sleep(3000);
  cout<<"Both Alice and Bob are calculating and sending their public key..."<<endl;  cout<<endl;  Sleep(3000);
  long long int pubA, pubB;
  pubA = modExp(g,Xa,n);
  pubB = modExp(g,Xb,n);

  cout<<"Alice generated her public key as : "<<pubA<<" and send to Bob"<<endl;
  cout<<endl;  Sleep(3000);
  cout<<"Bob generated his public key as : "<<pubB<<" and send to Alice"<<endl;
  cout<<endl;
  Sleep(3000);
  cout<<"Public key is sent."<<endl;  cout<<endl;
  cout<<endl<<"Alice and Bob calculating the keys..."<<endl;  cout<<endl;
  Sleep(3000);
  long long int KA,KB;
  KA = modExp(pubB,Xa,n);
  KB = modExp(pubA,Xb,n);
  Sleep(3000);
  cout<<"Alice got a shared key : "<<KA<<endl;  cout<<endl;
  cout<<"Bob got a shared key : "<<KB<<endl;  cout<<endl;

  Sleep(3000);

  if(KA==KB){
    cout<<"Hence both have received the same shared key."<<endl;  cout<<endl;
  }




}