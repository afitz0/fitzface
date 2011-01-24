#ifndef FITZFACE_COM_DATABASE
#define FITZFACE_COM_DATABASE

#include <libpq-fe.h>
#include "errorCodes.h"
#include "map.h"

const char * CONNINFO = "dbname=fitzface user=fitzface password=XXX";
PGconn * conn;

int db_connect() {
	conn = PQconnectdb(CONNINFO);

	if (PQstatus(conn) != CONNECTION_OK) {
		printf("Connection to database failed: %s", PQerrorMessage(conn));
		PQfinish(conn);
		return FITZ_ERROR;
	}

	return FITZ_SUCCESS;
}

int db_query(const char * query, map * results) {
	int fields, rows;
	PGresult *res = PQexec(conn, query);

	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		printf("Command failed: %s", PQerrorMessage(conn));
		PQclear(res);
		return FITZ_ERROR;
	}

	rows   = PQntuples(res);
	fields = PQnfields(res);

	if (results != NULL) {
		fprintf(stderr, "WARNING: given results set will be overwritten.\n");
	}

	results = (map*)malloc(sizeof(map)*rows);

	for (int i = 0; i < rows; i++) {
		results[i] = map_init(fields);
		for (int j = 0; j < fields; j++) {
			map_insert(&results[i], PQfname(res, j), PQgetvalue(res, i, j));
		}
	}
}

#endif
