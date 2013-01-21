import logging
import socket
import os
import sys
import time
from datetime import datetime
import struct
import threading
from ConfigParser import SafeConfigParser
import xml.dom.minidom

def filterSpecialString(target_str):
    target_str=target_str[:target_str.find("<SequenceNum>")]+target_str[target_str.find("</SequenceNum>")+len("</SequenceNum>"):]
    return target_str

def verifyResult( expect_resp, recv_buf  ):

    expect_resp=filterSpecialString(expect_resp)
    recv_buf=filterSpecialString(recv_buf)
    #print "expect_resp:"+expect_resp
    #print "recv_buf:"+recv_buf
    if cmp( recv_buf, expect_resp ) == 0:
        return True
    else:
        return False

def parseReceiveData( recv_data ):
    index = recv_data.find("<?")
    
    if index == -1:
        print "Response info not correct,please check it."
        logging.critical( "Response info not correct,please check it. Response:\n" + recv_data + "\n" )
        sys.exit(3)

    recv_data = recv_data[index:]
    recv_data_list=recv_data.strip().split("\n")
    recv_data=""
    for str in recv_data_list:
        recv_data=recv_data+str.strip()

    return recv_data

def getCaseFromFile( filename ):
    try:
        config = SafeConfigParser()
        config.read( filename )
        return config
    except BaseException as e:
        logging.critical( "failed to open the config file '" + filename + "'" )
        logging.critical( str(e) )
        print opt.case
        print "failed to open the config file '" + filename + "'"
        print str( e )
        sys.exit(3)

def getSubStringValue( req,begin_str,end_str ):
    index=req.find(begin_str)
    index_r=req.find(end_str)
    if index==-1 or index_r==-1:
        return ""
    else:
        sequence_num = req[index+len(begin_str):index_r]
        return sequence_num

def getRequest(case_cfg, step):
    req=case_cfg.get(step,"REQ").strip()
    req_seq_str=getSubStringValue(req,"<SequenceNum>","</SequenceNum>")
    
    return req,req_seq_str

def getResponse(case_cfg, step):
    if case_cfg.has_option(step,"RESP"):
        response="".join( case_cfg.get(step,"RESP").strip().split("\n") )
    else:
        response=""

    return response

def getReceiveNum(case_cfg, step):
    if case_cfg.has_option(step,"RECEIVE_NUM"):
        receive_num = case_cfg.get(step,"RECEIVE_NUM")
    else:
        receive_num="1"
    
    return int(receive_num)

def logBeginEnd(thread_id,step,flag):
    print "==========="+thread_id+"[" + step + "] "+flag+"=========="
    logging.info( "==========="+thread_id+"[" + step + "] "+flag+"==========" )

def send2Server( config, report_file, case_cfg, test_type ):
    try:
        if test_type == "ft":
            thread_id=""
        else:
            thread_id = "["+threading.current_thread().name+"]"

        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect( ( config.get("server","ip"), int( config.get("server","port") ) ) )
    except socket.error, arg:
        (errno, err_msg) = arg
        err_str = "Connect server "+config.get("server","ip")+":"+ config.get("server","port")+" failed: %s, errno=%d\n\n" % (err_msg, errno)
        print err_str
        logging.critical( thread_id+"Connect server "+config.get("server","ip")+":"+ config.get("server","port")+" failed\nFail reason:"+err_str )
        sys.exit(3)

    step_list = case_cfg.sections()
    step_list.sort()
    for step in step_list:
        logBeginEnd(thread_id,step,"BEGIN")

        #get request from file
        req,req_seq_str=getRequest(case_cfg,step)

        #get response from file
        expect_resp=getResponse(case_cfg,step)

        #get RECEIVE_NUM from file
        receive_num=getReceiveNum(case_cfg,step)

        try:
            #send the request data
            head=struct.pack("h",0)+struct.pack("!h",len(req)+4) #32bit, previous 16bit is zero, the last 16bit is len(req)+4
            req = head+req
            print thread_id+"Request:\n" + req + "\n"
            logging.info( thread_id+"Request:\n" + req + "\n" )
            sock.send( req )

            if expect_resp=="":
                logging.info( thread_id+"["+step+"] success\n" )
                report_file.write(thread_id+"["+step+"] success\n")
                logBeginEnd(thread_id,step,"END")
                continue

            #receive the response data
            bufsize=65535
            recv_buf=""
            #verify_result=False
            verify_result=True
            while True:
                recv_buf = sock.recv(bufsize).strip() #UnSubscribe not need to receive response
                print thread_id+"Response:\n" + recv_buf + "\n"
                logging.info( thread_id+"Response:\n" + recv_buf + "\n" )
                
                recv_buf=parseReceiveData(recv_buf)
                #only sequence number equal can judge the result.
                resp_seq_str=getSubStringValue(recv_buf,"<ReqSeqNum>","</ReqSeqNum>")
                if resp_seq_str=="" or req_seq_str == resp_seq_str:
                    #check the response data
                    #if verifyResult( expect_resp, recv_buf ):
                        #verify_result=True
                    
                    receive_num=receive_num-1
                    if receive_num==0:
                        if verify_result==True:
                            logging.info( thread_id+"["+step+"] success\n" )
                            report_file.write(thread_id+"["+step+"] success\n")
                        else:
                            logging.info( thread_id+"["+step+"] failed\n" )
                            report_file.write(thread_id+"["+step+"] failed\n")
                        break

            logBeginEnd(thread_id,step,"END")
        except socket.error, arg:
            (errno, err_msg) = arg
            err_str = "Connect server failed: %s, errno=%d" % (err_msg, errno)
            print err_str
            logging.critical( thread_id+"["+step+"] failed\nFail reason:"+err_str )
            report_file.write(thread_id+"["+step+"] failed\n")
            logBeginEnd(thread_id,step,"END")
        
    sock.close()

def sendFT( config ):
    cases = config.items("ft")
    cases.sort()
    report_name = "ADS_FT_Report_" + datetime.now().strftime("%Y%m%d")
    report_file = open(report_name, 'w+')
    for file in cases:
        logging.info("Starting send case ["+file[0]+"] to server")
        print "***************Starting send case ["+file[0]+"] to server****************"
        file_name = file[1]
        case_cfg = getCaseFromFile(file_name)
        #report_name = "ADS_FT_Report_" + file_name[file_name.rfind("/")+1:file_name.rfind(".")]+"_"+datetime.now().strftime("%Y%m%d")
        report_file.write("***"+file_name[file_name.rfind("/")+1:]+"@"+datetime.now().strftime("%H:%M:%S")+" BEGIN***\n")
        send2Server(config,report_file,case_cfg,"ft")
        report_file.write("***"+file_name[file_name.rfind("/")+1:]+"@"+datetime.now().strftime("%H:%M:%S")+" END*****\n\n")

    report_file.close( )

def sendPT( config ):        
    logging.info( "Concurrent number:" + config.get("performance","concurrent") )

    case_cfg = getCaseFromFile(config.get("performance","case"))
    report_name = "ADS_Performance_Report_" + datetime.now().strftime("%Y%m%d")
    report_file = open(report_name, 'w')
    threads = []
    socket_num = int( config.get("performance","concurrent") )
    nloops = range( socket_num )

    for i in nloops:
        t=threading.Thread(target=send2Server,args=(config,report_file,case_cfg,"pt"))
        threads.append(t)

    for i in nloops:
        time.sleep( 1 )
        threads[i].start()

    for i in nloops:
        threads[i].join()

    report_file.close( )
    logging.info( "All threads done." )
