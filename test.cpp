#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <vector>
using namespace std;

int main(){

    string s1="123";
	string s2=s1+"456";//one new address to store s2

	cout<<"s1 addr:"<<&s1<<" value:"<<s1<<endl;
	cout<<"s2 addr:"<<&s2<<" value:"<<s2<<endl;

	s1=s1+"789";
	cout<<"s1 addr:"<<&s1<<" value:"<<s1<<endl;//address has no change

  return 0;
}
