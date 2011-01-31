#ifndef FITZFACE_COM_DATABASE
#define FITZFACE_COM_DATABASE

#include <libpq-fe.h>

#include "map.h"

PGconn * conn;

int    db_connect();
map *  db_query(const char * query, int * rows, int * error);
char * db_escape(const char * text);
int    db_close();

#endif
