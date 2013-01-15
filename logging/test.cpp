#include "Logging.h"

int main(){
	Logging & log = Logging::getLogInstance();

	cout<<"-------test debug----------"<<endl;
	log.initLog("./log.txt",Logging::DEBUG);
	log.debug("test debug");
	log.info("test debug");
	log.warn("test debug");
	log.error("test debug");
	log.critical("test debug");

	cout<<"-------test error----------"<<endl;
	log.initLog("./log.txt",Logging::ERROR);
	log.debug("test debug");
	log.info("test debug");
	log.warn("test debug");
	log.error("test debug");
	log.critical("test debug");

	cout<<"before return"<<endl;
	return 0;
}
