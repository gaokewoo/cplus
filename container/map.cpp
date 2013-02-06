#include <iostream>
#include <map>
#include "gtest/gtest.h"

using namespace std;
class A{
	public:
		A(){cout<<"Default constructor called."<<endl;}

};

TEST(test_map,pair){
	pair<int,int> a(1,2);


	EXPECT_EQ(a.first,1);
	EXPECT_EQ(a.second,2);

	pair<int,int> p1;
	p1 = make_pair(3,4); //make_pair

	EXPECT_EQ(p1.first,3);
	EXPECT_EQ(p1.second,4);
}


TEST(test_map,call_default_constructor){
	pair<int,A> a;

}


TEST(test_map,initial_map){
	map<string,int> a;
	a["123"]=4;

	map<string,int>::iterator it = a.begin();

	while(it != a.end()){
		EXPECT_EQ(it->first,"123");
		EXPECT_EQ(it->second,4);

		it++;
	}

	pair<string,int> b("abc",5);
	a.insert(b); //test m.insert(e)
	it=a.begin();
	it++;
	EXPECT_EQ(it->first,"abc");
	EXPECT_EQ(it->second,5);

	//map cann't be initialized by following format
	//map<string,int>a("123",4);

}


TEST(test_map,count_and_find){
	pair<string,int> a("abc",4);
	//map<string,int> my_map(a); //cannot initialize by pair object
	map<string,int> my_map;
	my_map.insert(a);

	EXPECT_EQ(my_map.count("abc"),(unsigned int)1);
	map<string,int>::iterator it = my_map.find("abc");
	EXPECT_EQ(it->first,"abc");
	EXPECT_EQ(it->second,4);

}

