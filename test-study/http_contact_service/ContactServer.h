#include "add_contact_response.pb.h"
#include "add_contact_response.pb.h"
#include"../http_contact_client/add_contact_request.pb.h"
#include"../http_contact_client/add_contact_request.pb.h"
#include"ContactsMapper.h"
#include"../http_contact_client/add_contact_request.pb.h"

#include<iostream>
#include<httplib.h>
class ContactServer{
    private:
   ContactsMapper contactsMapper; //持久化存储通讯录⽅法定义
   public:
   void add(add_contact_req::AddContactReq& request,add_contact_resp::AddContactRep* response) const;
//  void del(del_contact_req::DelContactRequest& request,
//  del_contact_resp::DelContactResponse* response) const;
//  void findOne(find_one_contact_req::FindOneContactRequest request, 
//  find_one_contact_resp::FindOneContactResponse* response) 
// const;
// //  void findAll(find_all_contacts_resp::FindAllContactsResponse* rsp) const;
// private:
//  void printAddContactRequest(add_contact_req::AddContactRequest& request) 
// const;
//  void buildPeopleInfo(contacts::PeopleInfo* people, 
// add_contact_req::AddContactRequest& request) const;
//  void buildFindOneContactResponse(const contacts::PeopleInfo& people, 
 
// find_one_contact_resp::FindOneContactResponse* response) const;
//  void buildFindAllContactsResponse(contacts::Contacts& contacts, 
 
// find_all_contacts_resp::FindAllContactsResponse* rsp) const;
// };

};