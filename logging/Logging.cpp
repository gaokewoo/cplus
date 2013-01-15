#include "Logging.h"

void Logging::initLog(string logName, LOG_LEVEL logLevel, string timeFmt){
	_logName = logName;
	_logLevel = logLevel;
	_timeFmt = timeFmt;

	_fout.open(_logName.c_str(),ios_base::app);
	if(!_fout){
		cerr<<"Log file "<<_logName<<" open error";
		exit(1);
	}
}

string Logging::getSysTime(){

	time_t t = time(0);
	char tmp[64];
	strftime( tmp, sizeof(tmp), _timeFmt.c_str() ,localtime(&t) );
	//cout<<tmp<<endl;

	return tmp;
}


void Logging::debug(string msg){
	cout<<"logLevel:"<<_logLevel<<endl;
	if(_logLevel <= DEBUG)
		_fout<<"["<<getSysTime()<<"][DEBUG]"<<msg<<endl;
}


void Logging::info(string msg){
	if(_logLevel <= INFO)
		_fout<<"["<<getSysTime()<<"][INFO]"<<msg<<endl;
}

void Logging::warn(string msg){
	if(_logLevel <= WARN)
		_fout<<"["<<getSysTime()<<"][WARN]"<<msg<<endl;
}

void Logging::error(string msg){
	if(_logLevel <= ERROR)
		_fout<<"["<<getSysTime()<<"][ERROR]"<<msg<<endl;
}

void Logging::critical(string msg){
	if(_logLevel <= CRITICAL)
		_fout<<"["<<getSysTime()<<"][CRITICAL]"<<msg<<endl;
}

