// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include <sstream>
#include "DcAgent.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include <concurrency/ThreadManager.h>
#include <concurrency/PosixThreadFactory.h>

#include <server/TThreadPoolServer.h>
#include <server/TThreadedServer.h>


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;

using boost::shared_ptr;

using namespace  ::dc;

class DcAgentHandler : virtual public DcAgentIf {
 public:
  DcAgentHandler() {
    // Your initialization goes here
  }

  void run(std::string& _return, const std::string& command) {
    // Your implementation goes here
      std::ostringstream oss;
      FILE * pp = popen(command.c_str(),"r");
      if(pp){
          char buf[4096];
          while(fgets(buf,sizeof(buf),pp)){
              oss << buf;
          }
          pclose(pp);
      }
      else{
          oss << "Error: No such command : " << command;
      }
      _return = oss.str();
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<DcAgentHandler> handler(new DcAgentHandler());
  shared_ptr<TProcessor> processor(new DcAgentProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

   shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(15);
   shared_ptr<PosixThreadFactory> threadFactory 
	       = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());

   threadManager->threadFactory(threadFactory);
  threadManager->start(); 
  TThreadPoolServer server(processor,serverTransport,transportFactory,protocolFactory,threadManager);

  server.serve();
  return 0;
}

