#include "tables.h"
#include <stdio.h>
#include <assert.h>

int test1()
{
	Table table;
	size_t nr = 3;
	size_t nc = 4;

	table_init(&table, nr, nc);
	assert(table.nr == nr);
	assert(table.nc == nc);
	for (size_t i=0; i<nr; i++) {
		for (size_t j=0; j<nc; j++) {
			table.v[i][j] = 4;
		}
	}
	assert(table.v[0][0] == 4.0);
	assert(table.v[2][3] == 4.0);
	table_free(&table);
	return 0;
}

int test2()
{
	Table table;

	table_init_csv(&table, "resources/table_test_file1.csv", ",");
	assert(table.nr == 9);
	assert(table.nc == 9);
	assert(table.v[0][0] == 11.);
	assert(table.v[5][3] == 64.);
	assert(table.v[8][8] == 99.);
	//table_print(&table);
	table_free(&table);
	return 0;
}

int test3()
{
	Table table;

	table_init_csv(&table, "resources/table_test_file2.csv", ",");
	assert(table.nr == 12);
	assert(table.nc == 1);
	assert(table.v[0][0] == 1.);
	assert(table.v[5][0] == 6.);
	assert(table.v[11][0] == 12.);
	table_free(&table);
	return 0;
}

int main(int argc, char *argv[])
{
	int res = 0;
	res += test1();
	res += test2();
	res += test3();

	printf("test_tables: %d tests failed of %d\n", res, 3);
	return res;
}
