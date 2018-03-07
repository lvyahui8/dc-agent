CC	    =g++
LIB_INC     =-L/usr/local/lib
CXXFLAGS	    =-I/usr/include/thrift
SHARE_OBJ   =dc_agent_constants.o dc_agent_types.o 

all : server client

server: DcAgent.o DcServer.o $(SHARE_OBJ)
	    g++ $(LIB_INC) $(INC) $^ -o dc_server -lthrift
	    @echo dc_server created.

client: DcAgent.o DcClient.o $(SHARE_OBJ)
	    g++ $(LIB_INC) $(INC) $^ -o dc_client -lthrift
	    @echo dc_client created.

#default:server client

clean :
	    -rm *.o dc_client dc_server
	    @echo cleanup done;
