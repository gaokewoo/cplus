#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Config{
	public:
		Config(const string fileName);

		void trim(string & str);

		void initConfig();

		int getItems();

		string get(const string item, const string key);

	private:
		const string _fileName;

};

Config::Config(const string filename):_fileName(filename){ } 

void Config::trim(string & str) {
	str.erase(0,str.find_first_not_of("\r\t\n "));
	str.erase(str.find_last_not_of("\r\t\n ")+1);
}

void Config::initConfig(){
	 ifstream fin;
	 fin.open(_fileName.c_str(),ios_base::in);

	 if(!fin){
		 cerr<<"open file error."<<endl;
		 fin.close();
		 exit(3);
	 }

	while(!fin.eof() ){
		string tmp;
		fin>>tmp;
		trim(tmp);
		!tmp.empty() && cout<<"config info:"<<tmp<<endl;
	}


	fin.close();

}

int Config::getItems(){

	return 0;
}

string Config::get(const string item, const string key){

	return "";
}
int main(){
	Config a("/home/acer/cplus/config.ini");

	a.initConfig();

	return 0;
}
