#include "symmetries.h"
#include <stdio.h>
#include <assert.h>

int test1()
{
	Table table;

	table_init_csv(&table, "resources/sym_test_file1.csv", ",");

	size_t n = 10;
	size_t m = 24;
	grid_transform(&table, n, m, "E");

	table_print(&table);

	table_free(&table);
	return 0;
}

int main(int argc, char *argv[])
{
	int res = 0;
	res += test1();

	printf("#test_symmetries: %d tests failed of %d\n", res, 1);
	return res;
}
