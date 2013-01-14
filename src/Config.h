#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>

#ifndef __CONFIG__
#define __CONFIG__
using namespace std;

class Config{
	public:
		Config(const string fileName);

		void trim(string & str);

		void initConfig();

		int getItems();

		void toString();

		string get(const string item, const string key);

	private:
		const string _fileName;
		map< string,map<string,string> > _items;

};


#endif


