CC	    =g++
LIB_INC     =-L/usr/local/lib -L/usr/lib64
CXXFLAGS    =-static -I/usr/include/thrift
SHARE_OBJ   =dc_agent_constants.o dc_agent_types.o 

all : server client

server: DcAgent.o DcServer.o $(SHARE_OBJ)
	    ar cr libserver.a $^
	    g++ $(CXXFLAGS) $(LIB_INC) $(INC) libserver.a -o dc_server
	    @echo dc_server created.

client: DcAgent.o DcClient.o $(SHARE_OBJ)
	    ar cr libclient.a $^
	    g++ $(LIB_INC) $(INC) libclient.a -o dc_client
	    @echo dc_client created.

#default:server client

clean :
	    -rm *.o *.a dc_client dc_server
	    @echo cleanup done;
