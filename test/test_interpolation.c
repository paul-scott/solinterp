#include "interpolation.h"
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
	double v = catrom_interp(&table, 0, 0, 360./n, 360./m);
	assert(v == 3.);
	v = catrom_interp(&table, 36, 0, 360./n, 360./m);
	assert(v == 4.);

	table_free(&table);
}

void test2()
{
	Table table;
	Table table2;
	size_t i;
	size_t j;

	assert(!table_init_csv(&table, "resources/AliceSprings_N10M24_ext.csv", ","));

	size_t n = 10;
	size_t m = 24;
	assert(!grid_transform(&table, n, m, "E"));
	size_t nn = n*6;
	size_t mm = m*6;

	assert(!table_init(&table2, nn + 1, mm + 1));

	table2.v[0][0] = 0.;
	for (i=1; i<table2.nr; i++)
		table2.v[i][0] = -180.0 + (i-1)*360./nn;
	for (j=1; j<table2.nc; j++)
		table2.v[0][j] = -180.0 + (j-1)*360./mm;

	for (i=0; i<nn; i++)
		for (j=0; j<mm; j++)
			table2.v[i+1][j+1] = catrom_interp(&table,
					table2.v[i+1][0], table2.v[0][j+1], 360./n, 360./m);

	//table_print(&table2);

	table_free(&table);
	table_free(&table2);
}

void test3()
{
	Table table;
	Table table2;

	assert(!table_init_csv(&table, "resources/alice_springs_sample.csv", ","));
	assert(!table_init_csv(&table2, "resources/alice_springs_interp.csv", ","));

	const double FLOAT_THRESHOLD = 1e-9;

	size_t n = 10;
	size_t m = 24;
	assert(!grid_transform(&table, n, m, "E"));

	for (size_t i=0; i<table2.nr; i++) {
		double x = table2.v[i][0];
		double y = table2.v[i][1];
		double p = table2.v[i][2];
		double p_i = catrom_interp(&table, x, y, 360./n, 360./m);
		//printf("%f %f %f %f\n", x, y, p, p_i);
		assert(p_i <= p + FLOAT_THRESHOLD && p_i >= p - FLOAT_THRESHOLD);
	}

	table_free(&table);
	table_free(&table2);
}

void test4()
{
	Table table;
	Table table2;
	size_t i;

	assert(!table_init_csv(&table, "resources/newcastle_sample.csv", ","));
	assert(!table_init_csv(&table2, "resources/newcastle_interp.csv", ","));

	const double FLOAT_THRESHOLD = 1e-5;

	size_t n = 10;
	size_t m = 24;
	assert(!grid_transform(&table, n, m, "EW"));

	for (i=0; i<table2.nr; i++) {
		double x = table2.v[i][0];
		double y = table2.v[i][1];
		double p = table2.v[i][2];
		double p_i = catrom_interp(&table, x, y, 360./n, 360./m);
		//printf("%f %f %f %f\n", x, y, p, p_i);
		assert(p_i <= p + FLOAT_THRESHOLD && p_i >= p - FLOAT_THRESHOLD);
	}

	table_free(&table);
	table_free(&table2);
}

int main(int argc, char *argv[])
{
	test1();
	test2();
	test3();
	test4();

	return 0;
}
