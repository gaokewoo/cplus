#include "Config.h"


Config::Config(const string filename):_fileName(filename){ } 

void Config::trim(string & str) {
	str.erase(0,str.find_first_not_of("\r\t\n "));
	str.erase(str.find_last_not_of("\r\t\n ")+1);
}

//ugly implemention, try to improve it
void Config::initConfig(){
	 ifstream fin;
	 fin.open(_fileName.c_str(),ios_base::in);

	 if(!fin){
		 cerr<<"open file error."<<endl;
		 fin.close();
		 exit(3);
	 }

    string item;
	while(!fin.eof() && getline(fin, item) ){
		trim(item);

		//not process for empty or comments out lines
		if( item.empty() ||(item[0] == '#') ){
			continue;
		}

		//The begin with char '[' explain a new item
	    if( item[0] == '[' ) {
			item.erase(0,item.find_first_not_of("["));
			item.erase(item.find_last_not_of("]")+1);
			//cout<<item<<endl;
			
			//handle subitems
			string subitem;
			streampos pos;
			map<string,string> tmp;
			while( !fin.eof() ){
				pos=fin.tellg();
				getline(fin, subitem);
				trim(subitem);

				if( subitem.empty() || (subitem[0] == '#') ){
					continue;
				}
				
				if( subitem[0] == '[' ) {
					fin.seekg(pos);
					break;
				}

				string key = subitem.substr(0,subitem.find("="));
				string value = subitem.substr(subitem.find("=")+1);

				//cout<<"For item ["<<item<<"] key="<<key<<",value="<<value<<endl;

				tmp.insert(map<string,string>::value_type(key,value)); 
			}
			_items[item]=tmp;

		}

	}


	fin.close();

}

int Config::getItems(){
	int count=0;
	map< string, map<string,string> >::const_iterator map_it = _items.begin();

	while(map_it != _items.end()) {
		count++;
		map_it++;
	}
	return count;
}

void Config::toString(){
	map< string, map<string,string> >::const_iterator map_it = _items.begin();

	while(map_it != _items.end()){
		cout<<"item:"<<map_it->first<<endl;

		map<string,string> tmp = _items[map_it->first];
		map<string,string>::const_iterator map_it_sub = tmp.begin();
		while(map_it_sub != tmp.end()){
			cout<<"\t"<<"key:"<<map_it_sub->first<<endl;
			cout<<"\t"<<"value:"<<map_it_sub->second<<endl;

			map_it_sub++;
		}
		map_it++;
	}
}

string Config::get(const string item, const string key){
	map< string, map<string,string> >::const_iterator map_it = _items.begin();
	string value="";

	while(map_it != _items.end()){
		if( map_it->first == item){
			map<string,string> tmp = _items[map_it->first];
			map<string,string>::const_iterator map_it_sub = tmp.begin();
			while(map_it_sub != tmp.end()){
				cout<<"key:"<<map_it_sub->first<<endl;
				cout<<"value:"<<map_it_sub->second<<endl;

				if(map_it_sub->first == key){
					value = map_it_sub->second;
				}
				map_it_sub++;
			}
		}
		map_it++;
	}

	if(value == ""){
		cerr<<"no data found"<<endl;
		exit(1);
	}

	return value;
}
