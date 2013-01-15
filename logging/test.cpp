#include "Logging.h"

int main(){
	Logging & log = Logging::getLogInstance();

	log.initLog("./log.txt",Logging::DEBUG);

	cout<<"-------test debug----------"<<endl;
	log.debug("test debug");
	log.info("test debug");
	log.warn("test debug");
	log.error("test debug");
	log.critical("test debug");

	cout<<"-------test error----------"<<endl;
	log.setLogLevel(Logging::ERROR);
	log.debug("test debug");
	log.info("test debug");
	log.warn("test debug");
	log.error("test debug");
	log.critical("test debug");

	cout<<"before return"<<endl;
	return 0;
}
