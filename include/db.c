#include <stdio.h>

#include "errorCodes.h"
#include "config.h"
#include "db.h"

int db_connect() {
	char CONNINFO[256];
	sprintf(CONNINFO, "dbname=%s user=%s password=%s", DBNAME, DBUSER, DBPASS);
	conn = PQconnectdb(CONNINFO);

	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
		PQfinish(conn);
		return FITZ_ERROR;
	}

	return FITZ_SUCCESS;
}

map * db_query(const char * query, int * rows, int * error) {
	int fields;
	map * results;

	PGresult *res = PQexec(conn, query);

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		fprintf(stderr, "Command failed: %s\n", PQresStatus(PQresultStatus(res)));
		PQclear(res);

		*error = FITZ_ERROR;
		return NULL;
	}

	*rows  = PQntuples(res);
	fields = PQnfields(res);

	printf("Allocation results with %d rows.\n", *rows);
	results = malloc((*rows) * sizeof(map));

	for (int i = 0; i < *rows; i++) {
		results[i] = map_init(fields);
		for (int j = 0; j < fields; j++) {
			if (map_insert(&results[i], PQfname(res, j), PQgetvalue(res, i, j)) != FITZ_SUCCESS)
				fprintf(stderr, "Error inserting row %d, field %s.\n", i, PQfname(res, j));
		}
	}

	*error = FITZ_SUCCESS;
	return results;
}
