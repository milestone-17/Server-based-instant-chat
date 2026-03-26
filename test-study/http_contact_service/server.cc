#include<iostream>
#include<httplib.h>
#include "../http_contact_client/ContactServer.h"
#include "add_contact_response.pb.h"
#include"../http_contact_client/add_contact_request.pb.h"
#include"ContactException.h"
#include"ContactServer.h"
using namespace std;
int main(){
    std::cout<<"----------服务启动--------------"<<std::endl;
    ContactServer contactserver;
    httplib::Server server;
    server.Post("/contacts/add",[contactserver](const httplib:: Request&req, httplib::Response&resp){
        add_contact_resp::AddContactRep response;
        add_contact_req::AddContactReq request;
       try{
        //反序列化
        string req_str;
        if(!request.ParseFromString(req.body)){
            throw ContactException("Parse AddContactRequest Error");
        }
        //新增联系人
        contactserver.add(request,&response);
        //序列化response
        string resp_str;
        if(!response.SerializeToString(&resp_str)){
            throw ContactException("Parse AddContactResponse Error");
        }
        resp.body=resp_str;
        resp.set_header("Content-Type", "application/protobuf");
        resp.status=200;
    } catch (ContactException &e) {
    cerr << "---> /contacts/add 发现异常!!!" << endl
         << "---> 异常信息: " << e.what() << endl;
         resp.status = 500;
    base_response::BaseResponse* baseResponse = response.mutable_base_resp();
    baseResponse->set_success(false);
    baseResponse->set_errmsg(e.what());
    std::string response_str;
    if (response.SerializeToString(&response_str)) {
        resp.body = response_str;
        resp.set_header("Content-Type", "application/protobuf");
    }
}

});
    server.Get("/test-get", [](const httplib::Request&req, httplib::Response&resp){
        cout<<"收到get请求"<<endl;
        resp.status=200;
    });
    //监听
    server.listen("0.0.0.0", 8080);
}
