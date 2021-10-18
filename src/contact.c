#include "includes/contact.h"
#include "includes/database.h"

#include <stdio.h>
#include <string.h>

static void readString(char buffer[], int stringMaxSize) {
  setbuf(stdin, NULL);
  fgets(buffer, 255, stdin);

  buffer[strcspn(buffer, "\n")] = 0;
}

void contact_listContactsFromDatabase(void) { database_listFromDatabase(); }

void contact_createContactInDatabase(void) {
  char buffer[255];
  contact contactToCreate;

  printf("Digite o nome: ");
  readString(buffer, 255);
  strcpy(contactToCreate.name, buffer);

  printf("Digite o numero: ");
  readString(buffer, 20);
  strcpy(contactToCreate.number, buffer);

  printf("Digite o email: ");
  readString(buffer, 255);
  strcpy(contactToCreate.email, buffer);

  database_createInDatabase(contactToCreate);
}

void contact_getContactByCode(void) {
  contact contactFound;

  printf("Digite o codigo do contato: ");
  scanf("%d", &contactFound.id);

  contactFound = database_getById(contactFound.id);

  printf("%d | %s | %s | %s\n", contactFound.id, contactFound.name,
         contactFound.number, contactFound.email);
}

void contact_updateContactByCode(void) {
  contact contactFound;
  char buffer[255];

  printf("Digite o codigo do contato: ");
  scanf("%d", &contactFound.id);

  contactFound = database_getById(contactFound.id);

  printf("Nome atual: %s\n", contactFound.name);
  printf("Novo nome (Deixe vazio para não alterar): ");
  readString(buffer, 255);

  if (strcmp(buffer, "") != 0)
    strcpy(contactFound.name, buffer);

  printf("Numero atual: %s\n", contactFound.number);
  printf("Novo numero (Deixe vazio para não alterar): ");
  readString(buffer, 20);

  if (strcmp(buffer, "") != 0)
    strcpy(contactFound.number, buffer);

  printf("Email atual: %s\n", contactFound.email);
  printf("Novo email (Deixe vazio para não alterar): ");
  readString(buffer, 255);

  if (strcmp(buffer, "") != 0)
    strcpy(contactFound.email, buffer);

  database_updateById(contactFound);
}

void contact_deleteContactByCode(void) {
  contact contactFound;
  char choice;

  printf("Digite o codigo do contato: ");
  scanf("%d", &contactFound.id);

  contactFound = database_getById(contactFound.id);

  setbuf(stdin, NULL);
  while (choice != 'y' && choice != 'n') {
    printf("\n%d | %s | %s | %s\n", contactFound.id, contactFound.name,
           contactFound.number, contactFound.email);

    printf("Deseja realmente deletar esse contato [Sim(y)/Nao(n)]: ");
    scanf("%c", &choice);
  }

  if (choice == 'y')
    database_deleteById(contactFound.id);
}