#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>

#ifndef __CONFIG__
#define __CONFIG__
using namespace std;

class Config{
	public:
		Config(const string fileName);

		void trim(string & str);

		void initConfig();

		int getCount();

		void toString();

		string get(const string item, const string key);

	private:
		void read2Mem(ifstream& fin, vector< vector<string> > & vt );
		void parseData( vector< vector<string> > & vt );

	private:
		const string _fileName;
		map< string,map<string,string> > _items;

};


#endif


