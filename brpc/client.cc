#include"mian.pb.h"
#include<brpc/channel.h>
#include <brpc/controller.h>
#include <chrono>
#include <google/protobuf/stubs/callback.h>
#include <memory>
#include <thread>

void callback(brpc::Controller*cntl,example::EchoResponse* response){
    std::unique_ptr<brpc::Controller>cntl_guard(cntl);
    std::unique_ptr<example::EchoResponse>response_guard(response);
    if(cntl->Failed()){
    std::cout<<"发起请求failed,错误信息:"<< cntl->ErrorText() << std::endl;
    return ;
}
std::cout<<"收到响应"<<response->response()<<std::endl;

}

int main(int argc,char*argv[]){
    brpc::Channel channel;
    brpc::ChannelOptions channeloptions;
    channeloptions.connect_timeout_ms=-1;
    channeloptions.timeout_ms=-1;
    channeloptions.max_retry=3;
    channeloptions.protocol="baidu_std";

    int ret=channel.Init("127.0.0.1:9527",&channeloptions);
    if(ret==-1){
        std::cout<<"channel初始化失败\n";
    }

   example::EchoService_Stub stud(&channel);

example::EchoRequest request;
example::EchoResponse* response=new example::EchoResponse();
request.set_request("你好");

brpc::Controller* ctrl=new brpc::Controller();
auto closure=google::protobuf::NewCallback(callback,ctrl,response);
stud.Echo(ctrl,&request, response,closure);

std::cout<<"异步调用\n";
std::this_thread::sleep_for(std::chrono::seconds(5));
    return 0;
}
