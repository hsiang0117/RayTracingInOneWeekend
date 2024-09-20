#ifndef INTERVAL_HPP
#define INTERVAL_HPP

class interval {
public:
	double min, max;
	interval() : min(-infinity), max(infinity) {}
	interval(double min, double max) :min(min), max(max){}

	double size() const {
		return max - min;
	}

	bool contains(double x)const {
		return min <= x && x <= max;
	}

	bool surronds(double x)const {
		return min < x && x < max;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);

#endif // !INTERVAL_HPP
