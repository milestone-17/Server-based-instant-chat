#include "ContactServer.h"
#include "../http_contact_service/add_contact_response.pb.h"
#include "ContactException.h"
#include "add_contact_request.pb.h"
#include <httplib.h>
#include <iostream>
#include <string>
#define CONTACTS_HOST "192.168.75.131" // 不可带有分号
#define CONTACTS_PORT 8080
using namespace std;
void ContactServer::addContact() {
  httplib::Client client(CONTACTS_HOST, CONTACTS_PORT);
  // 构建request请求
  add_contact_req::AddContactReq req;
  buildAddContactRequest(&req);
  // 序列化
  string req_str;
  if (!req.SerializeToString(&req_str)) {
    throw ContactException("addContact序列化失败");
  }
  // 发送请求
  auto rep = client.Post("/contacts/add", req_str, "application/protobuf");
  if (!rep) {
    string errmsg;
    errmsg.append("/contacts/add链接错误,错误信息为: ")
        .append(httplib::to_string(rep.error()));
    throw ContactException(errmsg);
  }
  // 反序列化
  add_contact_resp::AddContactRep resp;
  bool parse = resp.ParseFromString(rep->body);
  if (rep->status != 200 && !parse) { //parse->false
    std::string err_desc;
    err_desc.append("post '/contacts/add/' 失败：")
        .append(std::to_string(rep->status))
        .append("(")
        .append(rep->reason)
        .append(")");
    throw ContactException(err_desc);
  } else if (rep->status != 200) {
    string err_desc;
    err_desc.append("post '/contacts/add/' 失败:")
    .append(std::to_string(rep->status))
    .append("(")
    .append(rep->reason)
    .append(")");
    throw ContactException(err_desc);
  } else if (!resp.base_resp().success()) {
    //出力数据异常
    string err_desc;
    err_desc.append("post '/contacts/add/' 结果异常:")
    .append("异常原因")
    .append(resp.base_resp().errmsg());
    throw ContactException(err_desc);
  }
  cout<<"----->新增联系人成功,联系人ID为:"<<resp.uid();
}
void ContactServer::delContact() {}
void ContactServer::findContacts() {}
void ContactServer::findContact() {}
void buildAddContactRequest(add_contact_req::AddContactReq *req) {
  cout << "--------开始添加个人信息---------" << endl;
  cout << "输入名字:";
  string name;
  getline(cin, name);
  cin.ignore(256, '\n');
  cout << endl;
  cout << "输入年龄:";
  int age;
  cin >> age;
  cout << endl;
  for (int i = 1;; ++i) {

    cout << "输入电话号码" << i << "(按回车键输入完成):";
    string number;
    getline(cin, number);
    if (number.empty()) {
      cout << " 所有电话号码输入完成" << endl;
    }
    auto phone = req->add_phone_number();
    phone->set_number(number);
    cout << "设置电话号码类型(1--固定电话,2--移动电话) :";
    int type;
    cin >> type;
    switch (type) {
    case 1:
      phone->set_type(::add_contact_req::AddContactReq_Phone_PhoneType ::
                          AddContactReq_Phone_PhoneType_MP);
      break;
    case 2:
      phone->set_type(::add_contact_req::AddContactReq_Phone_PhoneType ::
                          AddContactReq_Phone_PhoneType_TEL);
      break;
    default:
      cout << "输入错误,使用默认值" << endl;
      break;
    }
  }
  cout << "添加备注";
  for (int i = 1;; ++i) {
    cout << "备注信息" << i << endl;
    string key;
    cout << "输入备注信息名称(回车键完成)  :";
    getline(cin, key);
    if (key.empty()) {
      cout << "未输入信息,备注完成";
      break;
    }
    cout << endl;
    string value;
    cout << "输入备注信息内容(回车键完成) :";
    getline(cin, value);
    req->mutable_remark()->insert(key, value);
  }
  cout << "添加联系人信息完成" << endl;
}
void printFindOneContactResponse(find_contact_req::FindContactRep &resp) {}
//   void printFindAllContactsResponse(
//       find_all_contacts_resp::FindAllContactsResponse &resp);