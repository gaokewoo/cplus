#include <iostream>

using namespace std;

void test_str_assign(){

	string s("12345");
	cout<<"s:"<<s<<endl;

	string s2("12345",2);
	cout<<"s2:"<<s2<<endl;

	string s3(s,2);
	cout<<"s3:"<<s3<<endl;

	string s4(s,2,2);
	cout<<"s4:"<<s4<<endl;

	cout<<"\n-----test iterator begin-------"<<endl;
	string::iterator it = s.begin();
	while(it != s.end()){
		cout<<*it<<endl;

		it++;
	}
	cout<<"-----test iterator end------\n"<<endl;

}

void test_str_insert(){
	cout<<"\n----"<<__func__<<" begin----"<<endl;

	string s;
	s.insert(0,3,'c');
	cout<<"test s.insert(pos,n,c):"<<s<<endl;

	string s2="aaaa";
	s.insert(0,s2);
	cout<<"test s.insert(pos,s2):"<<s<<endl;
	cout<<"----"<<__func__<<" end----\n"<<endl;
}

int main(){

	test_str_assign();
	test_str_insert();

//	s.append("67");

	return 0;

}
