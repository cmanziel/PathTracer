#include "Interval.h"

Interval::Interval()
	: min(), max()
{
};

Interval::Interval(double min, double max)
	: min(min), max(max)
{
};

double Interval::Size() const
{
	return max - min;
}

bool Interval::ContainsClosed(double val) const
{
	return val >= min && val <= max;
}

bool Interval::ContainsOpened(double val) const
{
	return val > min && val < max;
}

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);