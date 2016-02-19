#include "interpolation.h"
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
	double v = catrom_interp(&table, 0, 0, 360./n, 360./m);
	assert(v == 3.);
	v = catrom_interp(&table, 36, 0, 360./n, 360./m);
	assert(v == 4.);

	table_free(&table);
	return 0;
}

int test2()
{
	Table table;
	Table table2;

	table_init_csv(&table, "resources/AliceSprings_N10M24_ext.csv", ",");

	size_t n = 10;
	size_t m = 24;
	grid_transform(&table, n, m, "E");
	size_t nn = n*6;
	size_t mm = m*6;

	table_init(&table2, nn + 1, mm + 1);

	table2.v[0][0] = 0.;
	for (size_t i=1; i<table2.nr; i++)
		table2.v[i][0] = -180.0 + (i-1)*360./nn;
	for (size_t j=1; j<table2.nc; j++)
		table2.v[0][j] = -180.0 + (j-1)*360./mm;

	for (size_t i=0; i<nn; i++)
		for (size_t j=0; j<mm; j++)
			table2.v[i+1][j+1] = catrom_interp(&table,
					table2.v[i+1][0], table2.v[0][j+1], 360./n, 360./m);

	table_print(&table2);

	table_free(&table);
	table_free(&table2);
	return 0;
}

int main(int argc, char *argv[])
{
	int res = 0;
	res += test1();
	res += test2();

	printf("#test_interpolation: %d tests failed of %d\n", res, 2);
	return res;
}
