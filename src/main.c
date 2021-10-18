#include <stdio.h>
#include <stdlib.h>

#include "includes/contact.h"

int main(int argc, char *argv) {
  printf("========================\n");
  printf("    AGENDA TELEFONICA   \n");
  printf("========================\n");

  while (1) {
    int choice;

    printf("-\n");
    printf("--- MENU PRINCIPAL\n");
    printf("0. Sair\n");
    printf("1. Adicionar\n");
    printf("2. Listar\n");
    printf("3. Pesquisar\n");
    printf("4. Atualizar\n");
    printf("5. Deletar\n");
    printf("\n");

    printf("Digite o que deseja executar> ");
    scanf("%d", &choice);

    if (choice == 0)
      break;
    else if (choice == 1)
      contact_createContactInDatabase();
    else if (choice == 2)
      contact_listContactsFromDatabase();
    else if (choice == 3)
      contact_getContactByCode();
    else if (choice == 4)
      contact_updateContactByCode();
    else if (choice == 5)
      contact_deleteContactByCode();
  }
  return EXIT_SUCCESS;
}