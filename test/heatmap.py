#! /bin/env python

from __future__ import division

import argparse
import matplotlib.pyplot as plt

def plot_heatmap(data):
	x = data[0][1:]
	y = [row[0] for row in data[1:]]
	z = [row[1:] for row in data[1:]]
	fig = plt.figure()
	sp = fig.add_subplot(1, 1, 1)
	sp.set_xticks(range(len(x)))
	sp.set_xticklabels([str(v) for v in x])
	sp.set_yticks(range(len(y)))
	sp.set_yticklabels([str(v) for v in y])
	sp.set_xlabel('Hour angle (degrees)')
	sp.set_ylabel('Ecliptic longitude (degrees)')
	sp.imshow(z, interpolation='nearest')
	plt.show()

def csv_reader(fn):
	f = open(fn)
	dat = []
	for line in f.readlines():
		if len(line) == 0 or line[0] == '#':
			continue
		l = [float(x) for x in line.split(',')]
		dat.append(l)
	return dat

if __name__ == '__main__':
	parser = argparse.ArgumentParser()
	parser.add_argument('file',
			help='csv file with gridded data')
	args = parser.parse_args()

	data = csv_reader(args.file)
	plot_heatmap(data)
