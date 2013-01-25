#include <iostream>
#include "gtest/gtest.h"

using namespace std;

TEST(test,strrchr){
	//cout<<"test str:"<<"/a/b/c"<<endl;
	string str="/a/b/c";
	string result=strrchr(str.c_str(),'/');

	EXPECT_EQ(result,"/c");	
}

TEST(test,strchr){
	//cout<<"test str:"<<"/a/b/c"<<endl;
	string str="/a/b/c";
	string result=strchr(str.c_str(),'/');

	EXPECT_EQ(result,"/a/b/c");	
}

TEST(test,gethostname){
	char hostname[128];
	gethostname(hostname,128);
	EXPECT_EQ(string(hostname),"EVB499BAE5651C");	
}

