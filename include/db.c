#include <stdio.h>

#include "error.h"
#include "config.h"
#include "db.h"

int db_connect() {
	char CONNINFO[256];
	sprintf(CONNINFO, "dbname=%s user=%s password=%s", DBNAME, DBUSER, DBPASS);
	conn = PQconnectdb(CONNINFO);

	if (PQstatus(conn) != CONNECTION_OK) {
		fprintf(stderr, "Connection to database failed: %s", PQerrorMessage(conn));
		db_close();
		return FITZ_ERROR;
	}

	return FITZ_SUCCESS;
}

map * db_query(const char * query, int * rows, int * error) {
	int fields;
	map * results;

	PGresult *res = PQexec(conn, query);

	if (PQresultStatus(res) == PGRES_TUPLES_OK) {
		*rows  = PQntuples(res);
		fields = PQnfields(res);

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
	} else if (PQresultStatus(res) == PGRES_COMMAND_OK) {
		*rows = 0;
		*error = FITZ_SUCCESS;
		return NULL;
	} else {
		fprintf(stderr, "Command failed: %s. %s\n", PQresStatus(PQresultStatus(res)), PQerrorMessage(conn));
		PQclear(res);

		*error = FITZ_ERROR;
		return NULL;
	}
}

char * db_escape(const char * text) {
	char * out = malloc(strlen(text)*2 + 1);
	int error;
	size_t bytes;

	bytes = PQescapeStringConn(conn, out, text, strlen(text), &error);
	if (error != 0) {
		fprintf(stderr, "Problem escaping string! Bytes written: %d\n", (int)bytes);
		return NULL;
	}

	return out;
}

int db_close() {
	PQfinish(conn);

	return FITZ_SUCCESS;
}
