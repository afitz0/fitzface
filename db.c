#include <stdio.h>
#include "errorCodes.h"
#include "config.h"
#include "db.h"

int db_connect() {
	char CONNINFO[256];
	sprintf(CONNINFO, "dbname=%s user=%s password=%s", DBNAME, DBUSER, DBPASS);
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

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		printf("Command failed: %s\n", PQresStatus(PQresultStatus(res)));
		PQclear(res);
		return FITZ_ERROR;
	}

	rows   = PQntuples(res);
	fields = PQnfields(res);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < fields; j++) {
			map_insert(results, PQfname(res, j), PQgetvalue(res, i, j));
		}
	}

	return FITZ_SUCCESS;
}
