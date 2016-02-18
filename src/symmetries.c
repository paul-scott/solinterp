#include "symmetries.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

/* Convert table into a grided form, taking into account symmetries
 *
 * table is a kx3 table of points in list form where k = table->nr
 * n number of points on circle for ecliptic longitude
 * m number of points on circle for hour angle
 */

void grid_transform(Table *table, size_t n, size_t m, const char *sym)
{
	Table tab; // working table for grided data
	size_t nr = n + 2; // extra rows for hour angles and -180, 180 redundancy
	size_t nc = m + 2; // extra cols for eclip longs and -180, 180 redundancy
	double el_step = 360./n; // ecliptic longitude grid step
	double ha_step = 360./m; // hour angle grid step

	int east_only = !strcmp(sym, "E");

	table_init(&tab, nr, nc);

	// Setting values for grid axes
	tab.v[0][0] = 0.; // top left point not used
	for (size_t i=1; i<nr; i++)
		tab.v[i][0] = -180.0 + (i-1)*el_step;
	for (size_t j=1; j<nc; j++)
		tab.v[0][j] = -180.0 +(j-1)*ha_step;

	for (size_t r=0; r<table->nr; r++) {
		double el = table->v[r][0];
		double ha = table->v[r][1];
		double val = table->v[r][2];
		size_t i = (size_t) roundf((180. + el)/el_step) % n;
		size_t j = (size_t) roundf((180. + ha)/ha_step) % m;
		printf("%lu, %lu\n", i, j);

		// direct
		tab.v[i+1][j+1] = val; // direct

		// spring-autumn
		size_t i_sa = (3*n/2 - i) % n;
		tab.v[i_sa+1][j+1] = val;

		// day-night
		size_t i_dn = (n - i) % n;
		size_t j_dn = (3*m/2 - j) % m;
		tab.v[i_dn+1][j_dn+1] = -val;

		// spring-autumn and day-night
		size_t i_sadn = (n - i_sa) % n;
		tab.v[i_sadn+1][j_dn+1] = -val;

		if (east_only) {
			size_t j_ew = (m - j) % m;
			tab.v[i+1][j_ew+1] = val;
			tab.v[i_sa+1][j_ew+1] = val;
			size_t j_ewdn = (3*m/2 - j_ew) % m;
			tab.v[i_dn+1][j_ewdn+1] = -val;
			tab.v[i_sadn+1][j_ewdn+1] = -val;
		}
	}
	// Copying -180 to 180
	for (size_t i=1; i<nr; i++)
		tab.v[i][nc-1] = tab.v[i][1];
	for (size_t j=1; j<nc; j++)
		tab.v[nr-1][j] = tab.v[1][j];

	table_free(table);
	*table = tab;
}
