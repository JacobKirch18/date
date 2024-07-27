#include<gtest/gtest.h>
#include <sstream>
#include "date.hpp"

TEST(DefaultCtor, HasCorrectValue) {

	Date d;
	EXPECT_EQ(d.day(), 1);
	EXPECT_EQ(d.month(), 1);
	EXPECT_EQ(d.year(), 1970);

}

TEST(ValueCtor, HasCorrectValue) {

	Date d = { 23, 12, 2003 };
	EXPECT_EQ(d.day(), 23);
	EXPECT_EQ(d.month(), 12);
	EXPECT_EQ(d.year(), 2003);

}

TEST(Invalid, throwsInvalidDate) {

	try {
		Date d = { 29, 2, 2001 };
	}
	catch (Date::Invalid e) {
		EXPECT_EQ(e.day, 29);
		EXPECT_EQ(e.month, 2);
		EXPECT_EQ(e.year, 2001);
	}

}

TEST(Order, HasCorrectValue) {

	EXPECT_EQ(Date::order, Date::Order::MonthDayYear);

}

TEST(Order, valueUpdates) {

	Date::order = Date::Order::DayMonthYear;
	EXPECT_EQ(Date::order, Date::Order::DayMonthYear);
	Date::order = Date::Order::YearMonthDay;
	EXPECT_EQ(Date::order, Date::Order::YearMonthDay);
	Date::order = Date::Order::MonthDayYear;

}

TEST(Setters, updateDateValue) {

	Date d1;
	d1.day(23);
	d1.month(12);
	d1.year(2003);
	EXPECT_EQ(d1.day(), 23);
	EXPECT_EQ(d1.month(), 12);
	EXPECT_EQ(d1.year(), 2003);

	Date d2 = { 15, 2, 2024 };
	d2.day(23);
	d2.month(12);
	d2.year(2003);
	EXPECT_EQ(d2.day(), 23);
	EXPECT_EQ(d2.month(), 12);
	EXPECT_EQ(d2.year(), 2003);

}

TEST(Props, returnCorrectValue) {

	Date d1 = { 15, 2, 2024 };
	EXPECT_EQ(d1.dayName(), "Thursday");
	EXPECT_EQ(d1.monthName(), "February");

	Date d2 = { 11, 8, 2010 };
	EXPECT_EQ(d2.dayName(), "Wednesday");
	EXPECT_EQ(d2.monthName(), "August");
}

TEST(Advance, incrementsDateCorrectly) {

	Date d1;
	d1.advance(1);
	EXPECT_EQ(d1.day(), 2);
	EXPECT_EQ(d1.month(), 1);
	EXPECT_EQ(d1.year(), 1970);

	Date d2;
	d2.advance(100);
	EXPECT_EQ(d2.day(), 11);
	EXPECT_EQ(d2.month(), 4);
	EXPECT_EQ(d2.year(), 1970);

}

TEST(Print, outputsCorrectValue) {

	Date d;
	std::ostringstream out;
	d.print(out);
	EXPECT_EQ(out.str(), "1/1/1970");

}

TEST(Now, returnsCurrentTime) {

	Date d1 = Date::now();
	time_t seconds = time(nullptr);
	tm date = *localtime(&seconds);
	Date d2 = { date.tm_mday, date.tm_mon + 1, date.tm_year + 1900 };

	EXPECT_EQ(d1.day(), d2.day());
	EXPECT_EQ(d1.month(), d2.month());
	EXPECT_EQ(d1.year(), d2.year());

}