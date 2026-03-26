#include"contacts.pb.h"
class ContactsMapper {
public:
 void selectContacts(contacts::Contacts* contacts) const;
 void insertContacts(contacts::Contacts& contacts) const;
};