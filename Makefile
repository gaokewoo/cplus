MACROS=$(flag)
VERSION=$(version) 

PROTOCOL_SRC=protocol/CMDProtocol.cpp  \
	     protocol/EADProtocol.cpp  \
	     protocol/MessageCenter.cpp  \
	     protocol/Protocol.cpp  \
	     protocol/ProtocolSet.cpp  \
	     protocol/RRLProtocol.cpp

SESSION_SRC=session/ADSAuthority.cpp  \
	    session/ADSSession.cpp  \
	    session/ADSState.cpp  \
	    session/TimerManager.cpp

SYSTEM_SRC=system/adssim.cpp      \
	   system/CBaseSocket.cpp      \
	   system/CEADPFrame.cpp    \
	   system/CIOMessageQueue.cpp  \
	   system/CTCPListen.cpp \
	   system/CBaseFrame.cpp  \
	   system/CConsoleService.cpp  \
	   system/CEpollModule.cpp  \
	   system/CTCPConnect.cpp      \
	   system/XmlParser.cpp

TINYXML_SRC=tinyxml/tinystr.cpp  \
	    tinyxml/tinyxml.cpp  \
	    tinyxml/tinyxmlerror.cpp \
	    tinyxml/tinyxmlparser.cpp  


#OBJS=$(addsuffix .o, $(basename $(PROTOCOL_SRC))) \
    $(addsuffix .o, $(basename $(SESSION_SRC))) \
    $(addsuffix .o, $(basename $(SYSTEM_SRC))) \
    $(addsuffix .o, $(basename $(TINYXML_SRC))) 

OBJS=$(PROTOCOL_SRC:.cpp=.o) $(SESSION_SRC:.cpp=.o) $(SYSTEM_SRC:.cpp=.o) $(TINYXML_SRC:.cpp=.o) 

CUR_DIR=$(shell pwd)
INCLUDE_DIR= -I. -I$(CUR_DIR)/system/ -I$(CUR_DIR)/protocol/ -I$(CUR_DIR)/session/ -I$(CUR_DIR)/tinyxml/


CC=g++
TARGET=adssim
CFLAGS=-Wall -g

$(TARGET):$(OBJS)
	$(CC) -o $(TARGET) $(OBJS)  -lpthread 

%.o:%.cpp
	 $(CC) $(CFLAGS) $(INCLUDE_DIR) -c  $< -o $@

clean:
	rm -f -r $(OBJS) $(TARGET)
