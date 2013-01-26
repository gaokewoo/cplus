#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class string_test:public testing::Test{
	protected:

		virtual void SetUp(){
			s="abc";
		}

		//virtual void TearDown(){}

		string s;

};

TEST_F(string_test,assign) {
	string s2("abc",2);
	EXPECT_EQ(s2,"ab");

	string s3(s,2);
	EXPECT_EQ(s3,"c");

	string s4(s,2,2);
	EXPECT_EQ(s4,"c");

}

TEST_F(string_test,insert) {
	string::iterator it=s.begin();
	it++;

	it=s.insert(it,'d');//the second element only support char type
						//test s.insert(p,t)
	EXPECT_EQ(s,"adbc");

	s.insert(it,2,'e');//test s.insert(p,n,t),return void
	EXPECT_EQ(s,"aeedbc");

	string::iterator p=s.begin();
	string::iterator b=it+1;
	string::iterator e=it+2;
	s.insert(p,b,e);
	EXPECT_EQ(s,"eaeedbc");//test s.insert(p,b,e)

	//ASSERT_EQ("ababc",s.insert(0,"aa"));
	//EXPECT_EQ("ababc",s.insert(0,"aa"))<<"wugk test"<<endl;
	s.insert(0,"aa");
	EXPECT_EQ(s,"aaeaeedbc");//test s.insert(pos,cp)

	s.insert(0,3,'f');
	EXPECT_EQ(s,"fffaaeaeedbc");//test s.insert(pos,n,c)

}
