#include <iostream>
#include <string>
#include <fstream>

#ifndef __LOGGING__
#define __LOGGING__

using namespace std;

class Logging{
	public:
		enum LOG_LEVEL{DEBUG=0,INFO,WARN,ERROR,CRITICAL};

	public:
		static Logging& getLogInstance(){
			static Logging log;

			return log;
		}

		void initLog(string logName,LOG_LEVEL logLevel=INFO, string timeFmt="%Y-%m-%d %H:%M:%S");
		void debug(string msg);
		void info(string msg);
		void warn(string msg);
		void error(string msg);
		void critical(string msg);

	private:
		string getSysTime();

	protected:
		Logging(){};
		~Logging(){ 
			if(_fout) _fout.close();
			//cout<<"destructor..."<<endl;
		}
		Logging(const Logging&);
		Logging & operator = (const Logging&);

	private:
		string _logName;
		LOG_LEVEL _logLevel;
		string _timeFmt;
		ofstream _fout;

};

#endif

