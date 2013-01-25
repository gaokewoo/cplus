#include <iostream>
#include "gtest/gtest.h"

using namespace std;

class string_test:public testing::Test{
	protected:

		virtual void SetUp(){
			cout<<"----initialize string s----"<<endl;
			s="abc";
		}

		//virtual void TearDown(){}

		string s;

};

TEST_F(string_test,insert) {
	EXPECT_EQ("abc",s);
	EXPECT_EQ("ababc",s.insert(0,"aa"));

}
TEST_F(string_test,insert2) {
	EXPECT_EQ("aaabc",s.insert(0,"aa"));

}
