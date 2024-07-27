#include "date.hpp"

Date::Order Date::order = Date::Order::MonthDayYear;
char Date::separator = '/';

static const vector<string> weekdays = { "Sunday", "Monday", "Tuesday", "Wednesday",
		"Thursday", "Friday", "Saturday" };

static const vector<string> months = { "January", "February", "March", "April",
	"May", "June", "July", "August", "September", "October", "November", "December" };

Date::Date() {

	date = { 0, 0, 0, 1, 0, 70, 0, 0, -1 };
	mktime(&date);

}

Date::Date(int day, int month, int year) {

	tm tempDate = { 0, 0, 0, day, month - 1, year - 1900, 0, 0, -1 };
	dateValidation(tempDate);
	date = { 0, 0, 0, day, month - 1, year - 1900, 0, 0, -1 };
	mktime(&date);

}

int Date::day() const {
	return date.tm_mday;
}

void Date::day(int day) {

	tm tempDate = date;
	tempDate.tm_mday = day;
	dateValidation(tempDate);
	date.tm_mday = day;

}

int Date::month() const {
	return date.tm_mon + 1;
}

void Date::month(int month) {

	tm tempDate = date;
	tempDate.tm_mon = month - 1;
	dateValidation(tempDate);
	date.tm_mon = month - 1;

}

int Date::year() const {
	return date.tm_year + 1900;
}

void Date::year(int year) {

	tm tempDate = date;
	tempDate.tm_year = year - 1900;
	dateValidation(tempDate);
	date.tm_year = year - 1900;

}

string Date::dayName() const {
	return weekdays[date.tm_wday];
}

string Date::monthName() const {
	return months[date.tm_mon];
}

void Date::advance(int days) {

	date.tm_mday += days;
	mktime(&date);

}

void Date::print(ostream& out) const {
		
	if (order == Order::DayMonthYear) {
		out << date.tm_mday << separator << date.tm_mon + 1 << separator << date.tm_year + 1900;
	}
	else if (order == Order::MonthDayYear) {
		out << date.tm_mon + 1 << separator << date.tm_mday << separator << date.tm_year + 1900;
	}
	else if (order == Order::YearMonthDay) {
		out << date.tm_year + 1900 << separator << date.tm_mon + 1 << separator << date.tm_mday;
	}

}

Date Date::now() {

	Date d;
	time_t seconds = time(nullptr);
	d.date = *localtime(&seconds);
	return d;

}

void Date::dateValidation(tm tempDate) {

	tm timeCopy = tempDate;
	mktime(&timeCopy);

	if (tempDate.tm_mday != timeCopy.tm_mday || tempDate.tm_mon != timeCopy.tm_mon ||
		tempDate.tm_year != timeCopy.tm_year) {

		Invalid invalidDate = { tempDate.tm_mday, tempDate.tm_mon + 1, tempDate.tm_year + 1900};
		throw invalidDate;

	}

}
