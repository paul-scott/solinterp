#include "tables.h"
#include <stdio.h>
#include <string.h>

void vector_init(Vector *vec)
{
	vec->len = 0;
	vec->cap = VECTOR_INIT_CAP;
	vec->v = malloc(VECTOR_INIT_CAP*sizeof(double));
}

void vector_free(Vector *vec)
{
	free(vec->v);
}

void vector_add(Vector *vec, double val)
{
	if (vec->len == vec->cap) {
		double *newv = realloc(vec->v, 2*vec->cap*sizeof(double));
		vec->v = newv;
		vec->cap *= 2;
	}
	vec->v[vec->len] = val;
	vec->len++;
}

void vector_set(Vector *vec, size_t i, double val)
{
	vec->v[i] = val;
}

double vector_get(const Vector *vec, size_t i)
{
	return vec->v[i];
}

void vectorv_init(VectorV *vec)
{
	vec->len = 0;
	vec->cap = VECTOR_INIT_CAP;
	vec->v = malloc(VECTOR_INIT_CAP*sizeof(Vector));
}

void vectorv_free(VectorV *vec)
{
	for (size_t i=0; i<vec->len; i++)
		vector_free(&(vec->v[i]));
	free(vec->v);
}

void vectorv_add(VectorV *vec, Vector *val)
{
	if (vec->len == vec->cap) {
		Vector *newv = realloc(vec->v, 2*vec->cap*sizeof(Vector));
		vec->v = newv;
		vec->cap *= 2;
	}
	vec->v[vec->len] = *val;
	vec->len++;
}

void vectorv_set(VectorV *vec, size_t i, Vector *val)
{
	vec->v[i] = *val;
}

Vector *vectorv_get(const VectorV *vec, size_t i)
{
	return &(vec->v[i]);
}

void table_init(Table *table, size_t nr, size_t nc)
{
	table->nr = nr;
	table->nc = nc;

	table->v = malloc(nr*sizeof(double *));
	if (!table->v)
		return;

	for (size_t i=0; i<nr; i++)
		table->v[i] = malloc(nc*sizeof(double));
}

void table_free(Table *table)
{
	for (size_t i=0; i<table->nr; i++)
		free(table->v[i]);
	free(table->v);
}

void table_init_csv(Table *table, const char *fn, const char *delim)
{
	// Any line that starts with a # or is blank is ignored
	const size_t BUFFLEN = 2048;
	char line[BUFFLEN];

	VectorV rows;
	vectorv_init(&rows);

	FILE *file;

 	file = fopen(fn, "r");
	if (!file)
		return;

	while (fgets(line, BUFFLEN, file)) {
		if (line[0] == '#') {
		} else if (strlen(line) <= 1) {
		} else {
			Vector row;
			vector_init(&row);
			char *tok = strtok(line, delim);
			while (tok) {
				double val = atof(tok);
				vector_add(&row, val);
				tok = strtok(NULL, delim);
			}
			vectorv_add(&rows, &row); // rows takes ownership of memory
		}
	}

	fclose(file);

	size_t nr = rows.len;
	size_t nc = 0;
	int square = 1;

	if (nr > 0)
		nc = vectorv_get(&rows, 0)->len;
	for (size_t i=0; i<nr; i++)
		square = square && (vectorv_get(&rows, i)->len == nc);

	if (square) {
		table->nr = nr;
		table->nc = nc;
		table->v = malloc(nr*sizeof(double *));
		for (size_t i=0; i<nr; i++) {
			table->v[i] = malloc(nc*sizeof(double));
			for (size_t j=0; j<nc; j++)
				table->v[i][j] = vector_get(vectorv_get(&rows, i), j);
		}
	} else {
		table->nr = 0;
		table->nc = 0;
	}

	vectorv_free(&rows);
}
