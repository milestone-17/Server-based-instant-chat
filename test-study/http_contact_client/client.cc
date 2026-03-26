#include<iostream>
#include<httplib.h>
#include"add_contact_request.pb.h"
using namespace std;
#include"ContactServer.h"
#define CONTACTS_HOST "192.168.75.131" //不可带有分号
#define CONTACTS_PORT 8080


    // httplib::Client client(CONTACTS_HOST,CONTACTS_PORT);
    // auto resp1=client.Post("/test-post");
    // if(resp1->status==200){
    //     cout<<"消息post成功"<<endl;
    // }
    // auto resp2=client.Get("/test-get");
    //  if(resp2->status==200){
    //     cout<<"消息get成功"<<endl;
    // }
//     return 0;
// // }
// #include<iostream>
// #include<httplib.h>
// #include"base_response.pb.h"
// #include"add_contact_request.pb.h"

// using namespace std;
// int main(){
//     std::cout<<"----------服务启动--------------"<<std::endl;
//     httplib::Server server;
//     server.Post("/test-post",[](const httplib:: Request&req, httplib::Response&resp){
//         cout<<"收到post请求!"<<endl;
//         resp.status=200;
//     });
//     server.Get("/test-get", [](const httplib::Request&req, httplib::Response&resp){
//         cout<<"收到get请求"<<endl;
//         resp.status=200;
//     });
//     //监听
//     server.listen("0.0.0.0", 8080);
// }
void menu() {
 std::cout << "-----------------------------------------------------" << 
std::endl
 << "--------------- 请选择对通讯录的操作 ----------------" << 
std::endl
 << "------------------ 1、新增联系⼈ --------------------" << 
std::endl 
 << "------------------ 2、删除联系⼈ --------------------" << 
std::endl
 << "------------------ 3、查看联系⼈列表 ----------------" << 
std::endl 
 << "------------------ 4、查看联系⼈详细信息 ------------" << 
std::endl
 << "------------------ 0、退出 --------------------------" << 
std::endl
 << "-----------------------------------------------------" << 
std::endl;
}
int main(){
    enum OPTION{ADD=1,DEL,FIND_ALL,FIND_ONE};
    ContactServer contactserver;
    while(true){
        menu();
        int option;
        cin>>option;
        switch (option) {
            case ADD:
                contactserver.addContact();
                break;
            case DEL:
                contactserver.delContact();
                break;
            case FIND_ALL:
                contactserver.findContacts();
                break;
            case FIND_ONE:
                contactserver.findContact();
                break;
        }
    }
}