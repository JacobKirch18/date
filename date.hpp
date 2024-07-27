#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <ostream>
#include <vector>

using std::ostream;
using std::string;
using std::vector;

class Date {

public:

	struct Invalid {

		int day;
		int month;
		int year;

	};

	enum class Order {

		MonthDayYear,
		DayMonthYear,
		YearMonthDay

	};

	static Order order;

	static char separator;

	Date();
	Date(int, int, int);

	int day() const;
	void day(int);

	int month() const;
	void month(int);

	int year() const;
	void year(int);

	string dayName() const;
	string monthName() const;

	void advance(int days = 1);

	void print(ostream&) const;

	static Date now();

private:

	tm date;

	void dateValidation(tm);

};
