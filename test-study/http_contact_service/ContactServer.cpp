#include"ContactServer.h"
#include"contacts.pb.h"
#include "add_contact_response.pb.h"
#include "add_contact_response.pb.h"
#include"../http_contact_client/add_contact_request.pb.h"
#include"../http_contact_client/add_contact_request.pb.h"
// #include"ContactsMapper.h"
#include"../http_contact_client/add_contact_request.pb.h"
using namespace std;
void ContactServer::add(add_contact_req::AddContactReq& request,add_contact_resp::AddContactRep* response) const{
    // 打印⽇志
 printAddContactRequest(request); 
 // 先读取已存在的 contacts
 contacts::Contacts contacts;
 contactsMapper.selectContacts(&contacts);
 // 转换为存⼊⽂件的消息对象 
 google::protobuf::Map<std::string, contacts::PeopleInfo>* map_contacts = 
contacts.mutable_contacts();
 contacts::PeopleInfo people;
 buildPeopleInfo(&people, request); 
 map_contacts->insert({people.uid(), people}); 
 // 向磁盘⽂件写⼊新的 contacts
 contactsMapper.insertContacts(contacts);
 response->set_uid(people.uid());
 response->mutable_base_resp()->set_success(true);
 // 打印⽇志
 cout << "---> (ContactsServer::add) Success to write contacts." << endl;
}