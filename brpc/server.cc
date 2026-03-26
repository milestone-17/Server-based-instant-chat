#include"mian.pb.h"
#include<butil/logging.h>
#include<brpc/server.h>
#include <cmath>
//1服务器继承EchoService
class EchoServicempl:public::example::EchoService{
    public:
    EchoServicempl(){}
    ~EchoServicempl(){}
    void Echo(google::protobuf::RpcController* controller,
              const ::example::EchoRequest* request,
              ::example::EchoResponse* response,
              ::google::protobuf::Closure* done){
        brpc::ClosureGuard cguard(done);
        std::cout<<"收到一个请求:"<<request->request()<<std::endl;
        //回复请求
        std::string str=request->request()+":处理完成";
        response->set_response(str);
        // done->Run(); 如果上面没有智能管理,需要
                       }
};

int main(int argc,char*argv[]){
    //关闭brpc的日志输出
    logging::LoggingSettings setting;
    setting.logging_dest=logging::LoggingDestination::LOG_TO_NONE;
    logging::InitLogging(setting);
    //2.创建rpc服务器类,搭建服务器 
    EchoServicempl echo;
    brpc::Server server;
    //3.向服务器添加rpc服务器
    int ret=server.AddService(&echo,brpc::ServiceOwnership::SERVER_DOESNT_OWN_SERVICE);
    if(ret==-1){
        std::cout<<"添加rpc服务器失败"<<std::endl;
        return -1;
    }
    //4.启动服务器
    brpc::ServerOptions opt;
    opt.idle_timeout_sec=-1;
    opt.num_threads=1;//io处理线程数
    ret=server.Start(9527,&opt);
    if(ret==-1){
        std::cout<<"启动服务器失败"<<std::endl;
        return -1;
    }
    //休眠直到 ctrl+c 按下，或者 stop 和 join 服务器
    server.RunUntilAskedToQuit();
    return 0;

}
