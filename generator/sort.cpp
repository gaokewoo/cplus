#include <iostream>
#include <fstream>

using namespace std;

int main(){
	ifstream fin("50.txt");
	string tmp;

	//getline(fin,tmp,',');
	//getline(fin,tmp);
	//fin>>tmp;
	while(fin>>tmp){
		cout<<tmp<<endl;
	}
	if(!fin.eof()){
		cerr<<"file operation error."<<endl;
	}

	//cout<<"tmp:"<<tmp<<endl;
	fin.close();

	return 0;

}
