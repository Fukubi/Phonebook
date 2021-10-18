#ifndef CONTACT_H
#define CONTACT_H

typedef struct contact {
  int id;
  char name[255];
  char number[20];
  char email[255];
} contact;

void contact_listContactsFromDatabase(void);
void contact_createContactInDatabase(void);
void contact_getContactByCode(void);
void contact_updateContactByCode(void);
void contact_deleteContactByCode(void);

#endif