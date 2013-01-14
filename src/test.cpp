#include "Config.h"

//for test

int main(){
	Config a("../config.ini");

	a.initConfig();
	cout<<"The number of config items:"<<a.getItems()<<endl;

	cout<<"Get config:"<<a.get("config1","item1")<<endl;

	cout<<"---------toString------------"<<endl;
	a.toString();
	

	return 0;
}
