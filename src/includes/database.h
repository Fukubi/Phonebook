#ifndef DATABASE_H
#define DATABASE_H

#include "contact.h"

void database_listFromDatabase(void);
void database_createInDatabase(contact contactToCreate);
contact database_getById(int id);
void database_updateById(contact contactToUpdate);
void database_deleteById(int id);

#endif