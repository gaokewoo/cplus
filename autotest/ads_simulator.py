#!/usr/bin/env python
import sys, __builtin__, subprocess, os
from os.path import dirname, abspath
from optparse import OptionParser
from datetime import datetime
from ConfigParser import SafeConfigParser
import logging
import sender

def defaultLogName():
    t = datetime.now()
    name = t.strftime("%Y%m%d")
    return __builtin__.HOME+"/ADS_autotest_" + name + ".log"

def parseArgs():
    p = OptionParser()
    p.add_option( "--cfg", action="store", type="string", dest="cfg",
        help="the absolute path and file name of config file" )
    p.add_option( "--log", action="store", type="string", dest="log",
        help="the absolute path and filename of log, default is ./ADS_autotest_<yymmddHMS>.log" )
    p.add_option( "--type", action="store", type="string", dest="type",
        help="the absolute path and filename of test type" )

    p.set_defaults( log=defaultLogName() )
    p.set_defaults( type="ft" )

    opt, args = p.parse_args()

    if len( sys.argv ) == 1 \
        or opt.cfg == None:
        subprocess.call( [ sys.argv[0], '-h' ], stdout=sys.stdout )
        sys.exit(1)

    return (opt, args)

def initConfig( cfgFilename ):
    try:
        config = SafeConfigParser()
        config.read( cfgFilename )
        return config
    except BaseException as e:
        logging.critical( "failed to open the config file '" + cfgFilename + "'" )
        logging.critical( str(e) )
        print cfgFilename
        print "failed to open the config file '" + cfgFilename + "'"
        print str(e )
        sys.exit(3)


def initSysPath():
    HOME = dirname ( abspath( sys.argv[0] ) )
    __builtin__.HOME = HOME
    sys.path.append( HOME )

if __name__ == '__main__':

    initSysPath()

    opt,args = parseArgs()

    logging.basicConfig(filename=opt.log,level=logging.INFO, format="[%(asctime)s %(levelname)s] %(message)s", datefmt='%Y-%m-%d %H:%M:%S')
    #print opt.cfg
    logging.info("Read config info from file:"+opt.cfg)

    config = initConfig( opt.cfg )

    logging.info( "Target machine IP:"+config.get("server","ip") )
    logging.info( "Target machine PORT:"+config.get("server","port") )
    logging.info( "Test type:"+opt.type )
    
    if( opt.type == "ft" ):
        sender.sendFT(config)
    elif ( opt.type == "performance" ):
        sender.sendPT(config)
    else:
        logging.critical( "Not supported test type" )
        sys.exit(3)


