#include "includes/database.h"
#include "includes/contact.h"

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sqlite3 *openDatabase(void) {
  sqlite3 *db;

  if (sqlite3_open("Database.db", &db) != SQLITE_OK) {
    fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));

    exit(EXIT_FAILURE);
  }

  return db;
}

static void closeDatabase(sqlite3 *db) { sqlite3_close(db); }

static void prepareDatabase(sqlite3 *db) {
  sqlite3_stmt *stmt;
  sqlite3_prepare_v2(
      db,
      "CREATE TABLE IF NOT EXISTS contacts (id INTEGER PRIMARY KEY, name TEXT "
      "NOT NULL, number TEXT NOT NULL, email TEXT);",
      -1, &stmt, NULL);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Erro enquanto preparava o banco de dados: %s\n",
            sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    closeDatabase(db);
    exit(EXIT_FAILURE);
  }

  sqlite3_finalize(stmt);
}

void database_listFromDatabase(void) {
  sqlite3 *db;
  sqlite3_stmt *stmt;
  db = openDatabase();
  prepareDatabase(db);

  sqlite3_prepare_v2(db, "SELECT * FROM contacts;", -1, &stmt, NULL);

  while (sqlite3_step(stmt) != SQLITE_DONE) {
    contact listedContact;

    listedContact.id = sqlite3_column_int(stmt, 0);
    strcpy(listedContact.name, sqlite3_column_text(stmt, 1));
    strcpy(listedContact.number, sqlite3_column_text(stmt, 2));
    strcpy(listedContact.email, sqlite3_column_text(stmt, 3));

    printf("%d | %s | %s | %s\n", listedContact.id, listedContact.name,
           listedContact.number, listedContact.email);
  }

  sqlite3_finalize(stmt);
  closeDatabase(db);
}

void database_createInDatabase(contact contactToCreate) {
  sqlite3 *db;
  sqlite3_stmt *stmt;

  db = openDatabase();
  prepareDatabase(db);

  sqlite3_prepare_v2(
      db, "INSERT INTO contacts (name, number, email) VALUES (?, ?, ?);", -1,
      &stmt, NULL);

  sqlite3_bind_text(stmt, 1, contactToCreate.name, -1, NULL);
  sqlite3_bind_text(stmt, 2, contactToCreate.number, -1, NULL);
  sqlite3_bind_text(stmt, 3, contactToCreate.email, -1, NULL);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Erro ao criar contato no banco de dados: %s\n",
            sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    closeDatabase(db);
    exit(EXIT_FAILURE);
  }

  sqlite3_finalize(stmt);
  closeDatabase(db);
}

contact database_getById(int id) {
  sqlite3 *db;
  sqlite3_stmt *stmt;
  contact contactFound;

  db = openDatabase();
  prepareDatabase(db);

  sqlite3_prepare_v2(db, "SELECT * FROM contacts WHERE id = ?;", -1, &stmt,
                     NULL);

  sqlite3_bind_int(stmt, 1, id);

  sqlite3_step(stmt);

  contactFound.id = sqlite3_column_int(stmt, 0);
  strcpy(contactFound.name, sqlite3_column_text(stmt, 1));
  strcpy(contactFound.number, sqlite3_column_text(stmt, 2));
  strcpy(contactFound.email, sqlite3_column_text(stmt, 3));

  sqlite3_finalize(stmt);
  closeDatabase(db);

  return contactFound;
}

void database_updateById(contact contactToUpdate) {
  sqlite3 *db;
  sqlite3_stmt *stmt;

  db = openDatabase();
  prepareDatabase(db);

  sqlite3_prepare_v2(
      db, "UPDATE contacts SET name = ?, number = ?, email = ? WHERE id = ?;",
      -1, &stmt, NULL);

  sqlite3_bind_text(stmt, 1, contactToUpdate.name, -1, NULL);
  sqlite3_bind_text(stmt, 2, contactToUpdate.number, -1, NULL);
  sqlite3_bind_text(stmt, 3, contactToUpdate.email, -1, NULL);
  sqlite3_bind_int(stmt, 4, contactToUpdate.id);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Erro ao atualizar dados do contato: %s\n",
            sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    closeDatabase(db);
  }

  sqlite3_finalize(stmt);
  closeDatabase(db);
}

void database_deleteById(int id) {
  sqlite3 *db;
  sqlite3_stmt *stmt;

  db = openDatabase();
  prepareDatabase(db);

  sqlite3_prepare_v2(db, "DELETE FROM contacts WHERE id = ?;", -1, &stmt, NULL);

  sqlite3_bind_int(stmt, 1, id);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    fprintf(stderr, "Erro ao deletar contato: %s\n", sqlite3_errmsg(db));

    sqlite3_finalize(stmt);
    closeDatabase(db);
  }

  sqlite3_finalize(stmt);
  closeDatabase(db);
}