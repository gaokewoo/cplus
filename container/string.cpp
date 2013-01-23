#include <iostream>

using namespace std;

int main(){
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

	s.append("67");

	return 0;

}
