#include <iostream>
#include <pthread.h>
#include <stdio.h>
//#include<sys/types.h>
//#include<unistd.h>
using namespace std;
pthread_t ntid;

void printids(const char *s){
pid_t pid;
  pthread_t tid;

  pid = getpid();
  tid = pthread_self();
  printf("%s pid %u tid %u (0x%x)\n",s,(unsigned int)pid,(unsigned int)tid,(unsigned 
int)tid);
}

void *thr_fn(void *arg){
  printids("new thread:");
  return ((void *)0);
}

enum ab {a=1,b=2,c=3,d,e,f};

class A{
	public:
		void f(const int& a){cout<<"const int a"<<endl;}
		void f(int &a){cout<<"int a"<<endl;}
};

typedef void (A::*PF)(const int &a);
int main(){

  PF pl=&A::f;

  A a;
  //cout<<&(a.*pl)<<endl;

  return 0;
}
