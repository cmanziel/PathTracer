#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class Interval
{
public:
	double min;
	double max;

	Interval();
	Interval(double min, double max);

	double Size() const;
	bool ContainsClosed(double val) const;
	bool ContainsOpened(double val) const;

	static const Interval empty, universe;
};

#endif