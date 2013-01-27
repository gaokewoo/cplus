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

	string s3(s,2); //attention:this function is different with the previous function
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

	s.insert(0,"abc",2);
	EXPECT_EQ(s,"abfffaaeaeedbc");//test s.insert(pos,cp,len)

	s.insert(0,"hijklmn",2,3);//test s.insert(pos,s2,pos2,len)
	EXPECT_EQ(s,"jklabfffaaeaeedbc");

	s.erase(0,2);//test s.erase(pos,len);
	EXPECT_EQ(s,"labfffaaeaeedbc");
}

TEST_F(string_test,substr){
	string s2;
	s2=s.substr(0,2); //test s.substr(pos,n)
	EXPECT_EQ(s2,"ab");

	s2=s.substr(2); //test s.substr(pos)
	EXPECT_EQ(s2,"c");

	s2=s.substr(); //test s.substr()
	EXPECT_EQ(s2,"abc");
}

