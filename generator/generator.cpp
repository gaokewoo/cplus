//this programe use to generate 50,500,5000,50000,500000 random data to different files

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void generator(ofstream & f,const long number){
	srand(time(0));

	for(int i=0; i<number; i++){
		long j=rand()%number+1;
		f<<j<<",";
	}
	
}

int main(){
	cout<<"------Generate 50 data------"<<endl;
	ofstream fout50("50.txt",ios_base::app);
	generator(fout50,50);
	fout50.close();

	cout<<"------Generate 500 data------"<<endl;
	ofstream fout5B("5B.txt",ios_base::app);
	generator(fout5B,500);
	fout5B.close();


	cout<<"------Generate 5000 data------"<<endl;
	ofstream fout5Q("5Q.txt",ios_base::app);
	generator(fout5Q,5000);
	fout5Q.close();

	cout<<"------Generate 50000 data------"<<endl;
	ofstream fout5W("5W.txt",ios_base::app);
	generator(fout5W,50000);
	fout5W.close();
	
	cout<<"------Generate 500000 data------"<<endl;
	ofstream fout5SW("5SW.txt",ios_base::app);
	generator(fout5SW,500000);
	fout5SW.close();

	return 0;
}
