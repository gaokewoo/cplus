#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept>

using namespace std;

class A{
	public:
		A(){cout<<"Constructor A"<<endl;}
		A(A &){cout<<"Copy constructor A"<<endl;}
		A(const A &){cout<<"Copy constructor A"<<endl;} //注意，对于容器，形参必须要有const关键字，否则编译会报错

};

//test initialization
void test1(){

	A aa;
	cout<<"------test vector-------"<<endl;
	vector<A> svec(3,aa);  //容器中存放的是元素的copy


	cout<<"------test list-------"<<endl;
	list<A> ilist(3); //首先创建一个A的对象，之后创建3个副本

	//Output:
	//Constructor A
	//------test vector-------
	//Copy constructor A
	//Copy constructor A
	//Copy constructor A
	//------test list-------
	//Constructor A
	//Copy constructor A
	//Copy constructor A
	//Copy constructor A


}

//test initialization
void test2(){
	cout<<"-------test2()---------"<<endl;
	vector<int> ivec(5); //在vector中创建5个int元素，并初始化为0
	cout<<ivec.capacity()<<endl; //10
	cout<<ivec.size()<<endl; //10
    cout<<ivec.empty()<<endl;//0

	vector<int>::iterator it = ivec.begin();

	while(it != ivec.end()){
		cout<<__func__<<" value:"<<*it<<endl;
		it++;
	}

//	Output:
//	5
//	5
//	0
//	vector's value:0
//	vector's value:0
//	vector's value:0
//	vector's value:0
//	vector's value:0

}

void print_value(vector<int> & ivec){
	vector<int>::iterator it = ivec.begin(); 
	while(it != ivec.end()){
		cout<<__func__<<" value:"<<*it<<endl;

		it++;
	}
}

void test3_iterator(vector<int> & ivec){

	vector<int>::iterator it = ivec.begin(); ///use iterator,output:1,2,3,4,5
	while(it != ivec.end()){
		cout<<__func__<<" value:"<<*it<<endl;

		it++;
	}
}

void test3_const_iterator(vector<int> & ivec){

	vector<int>::const_iterator it = ivec.begin(); //use const_iterator, output:1,2,3,4,5
	while(it != ivec.end()){
		cout<<__func__<<" value:"<<*it<<endl;

		it++;
	}
}

void test3_reverse_iterator(vector<int> & ivec){

	vector<int>::reverse_iterator it = ivec.rbegin(); //use reverse_iterator, need use rbegin and rend, output:5,4,3,2,1
	while(it != ivec.rend()){
		cout<<__func__<<" value:"<<*it<<endl;

		it++;
	}
}


void test3_const_reverse_iterator(vector<int> & ivec){

	vector<int>::const_reverse_iterator it = ivec.rbegin(); //use const_reverse_iterator, need use rbegin and rend, output:5,4,3,2,1
	vector<int>::const_reverse_iterator it_end = ivec.rend();//it_end must define in this place ,or will raise compilation error
	while(it != it_end){
		cout<<__func__<<" value:"<<*it<<endl;

		it++;
	}
}

void test3_other(vector<int> & ivec){

	vector<int>::iterator it = ivec.begin(); //test insert,output:1,2,3,4,5
	cout<<__func__<<" test back:"<< ivec.back()<<endl;
	cout<<__func__<<" test front:"<< ivec.front()<<endl;
	try{
		cout<<__func__<<" test at:"<< ivec.at(5)<<endl;
	}
	catch(out_of_range e){
		cout<<"An error raised, since you visit an illegal address:"<<e.what()<<endl;

	}
	while(it != ivec.end()){
		cout<<__func__<<" value:"<<*it<<endl;
		//ivec.insert(it,3,2);//this function will raise core
		//it = ivec.insert(it,7); //will lead to endless loop

		it++;
	}

	cout<<"\n----------test insert begin-----------"<<endl;
	vector<int>::iterator it2 = ivec.begin(); //test insert,output:1,2,3,4,5
	ivec.insert(it2,0);
	while(it2 != ivec.end()){
		cout<<__func__<<" value:"<<*it2<<endl;
		it2++;
	}
	cout<<"----------test insert end-----------\n"<<endl;

	ivec.erase(--it);
	print_value(ivec); //output:1,2,3,4
	cout<<__func__<<" test capacity:"<<ivec.capacity()<<endl; //output:8
	cout<<__func__<<" test size:"<<ivec.size()<<endl; //output:4
	cout<<__func__<<" test max_size:"<<ivec.max_size()<<endl; //output:1073741823

	ivec.resize(3);
	cout<<__func__<<" test capacity:"<<ivec.capacity()<<endl; //output:8
	cout<<__func__<<" test size:"<<ivec.size()<<endl; //output:3
	print_value(ivec); //output:1,2,3
	ivec.resize(7,10);
	cout<<__func__<<" test capacity:"<<ivec.capacity()<<endl; //output:8
	cout<<__func__<<" test size:"<<ivec.size()<<endl; //output:7
	print_value(ivec); //output:1,2,3,10,10,10,10
	
}


//test iterator
void test3(){
	cout<<"\n--------test3()-----------"<<endl;

	vector<int> ivec;
	ivec.push_back(1);
	ivec.push_back(2);
	ivec.push_back(3);
	ivec.push_back(4);
	ivec.push_back(5);
	
	test3_iterator(ivec);
	test3_const_iterator(ivec);
	test3_reverse_iterator(ivec);
	test3_const_reverse_iterator(ivec);
	test3_other(ivec);
}
int main(){
    test1();

	test2();

	test3();

}
