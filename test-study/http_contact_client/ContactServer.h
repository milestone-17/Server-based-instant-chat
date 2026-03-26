#include "add_contact_request.pb.h"
#include "del_contact_request.pb.h"
#include "find_contactone_request.pb.h"
class ContactServer {
public:
  void addContact();
  void delContact();
  void findContacts();
  void findContact();

private:
  void buildAddContactRequest(add_contact_req::AddContactReq *req);
  void printFindOneContactResponse(find_contact_req::FindContactRep &resp);
//   void printFindAllContactsResponse(
//       find_all_contacts_resp::FindAllContactsResponse &resp);
};