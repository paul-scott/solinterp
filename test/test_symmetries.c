#include "symmetries.h"
#include <stdio.h>
#include <assert.h>

void test1()
{
	Table table;

	assert(!table_init_csv(&table, "resources/sym_test_file1.csv", ","));

	size_t n = 10;
	size_t m = 24;
	assert(!grid_transform(&table, n, m, "E"));

	table_print(&table);
	table_free(&table);
}

int main(int argc, char *argv[])
{
	test1();
	return 0;
}
