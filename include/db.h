#ifndef FITZFACE_COM_DATABASE
#define FITZFACE_COM_DATABASE

#include "map.h"
#include <libpq-fe.h>

PGconn * conn;

int db_connect();
int db_query(const char * query, map * results);

#endif
