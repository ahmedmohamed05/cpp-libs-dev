#ifndef DATE
#define DATE
#include "mstring.h"
#include <ctime>
#include <iostream>
#include <string>

// Default format is DD/MM/YYYY/HH:MM:SS
class TimeDate {
private:
  short _year, _month, _day, _hour, _minute, _second;
  std::string _separator;

public:
  // ************************************************************
  // *********************** Constructors ***********************
  // ************************************************************
  TimeDate() { *this = getTodayTimeDate(); }

  TimeDate(const std::string &date, std::string separator = "/") {
    setTimeDate(date, separator);
    if (!isValidTimeDate(_day, _month, _year, _hour, _minute, _second)) {
      *this = getTodayTimeDate();
    }
  }

  TimeDate(short day, short month, short year, short hour, short minute,
           short second, std::string separator = "/") {
    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = second;
    if (separator.empty())
      separator = "/";
    _separator = separator;
  }

  // TimeDate(const TimeDate *tm) { *this = *tm; }

  // ***********************************************************
  // *********************** Second Methods ********************
  // ***********************************************************

  // Returns false if newSecond is invalid
  bool setSecond(short newSecond) {
    if (!isValidSecond(newSecond))
      return false;

    _second = newSecond;
    return true;
  }

  short getSecond() const { return _second; }

  // Checks if the given second is 0 <= second <= 59
  static bool isValidSecond(short second) {
    return (0 <= second && second <= 59);
  }

  // ***********************************************************
  // *********************** Minute Methods ********************
  // ***********************************************************

  // Returns false if newSecond is invalid
  bool setMinute(short newMinute) {
    if (!isValidMinute(newMinute))
      return false;

    _minute = newMinute;
    return true;
  }

  short getMinute() const { return _minute; }

  static bool isValidMinute(short minute) {
    return (1 <= minute && minute <= 59);
  }

  // ***********************************************************
  // *********************** Minute Methods ********************
  // ***********************************************************

  // Returns false if newHour is invalid
  bool setHour(short newHour) {
    if (!isValidHour(newHour))
      return false;

    _hour = newHour;
    return true;
  }

  short getHour() const { return _hour; }

  static bool isValidHour(short Hour) { return (0 <= Hour && Hour <= 23); }

  // ***********************************************************
  // *********************** Day Methods ***********************
  // ***********************************************************

  // returns false if newDay is invalid
  bool setDay(short newDay, short month, short year) {
    if (!isValidDay(newDay, month, year))
      return false;

    _day = newDay;
    return true;
  }

  // This setter use's the current month and year to set the day
  bool setDay(short newDay) {
    if (!isValidDay(newDay, _month, _year))
      return false;

    _day = newDay;
    return true;
  }

  short getDay() const { return _day; }

  static bool isValidDay(short dayOrder, short month, short year) {
    int monthDays = getMonthDays(month, year);
    return (1 <= dayOrder && dayOrder <= monthDays);
  }

  static bool isLastDayInMonth(const TimeDate &date) {
    return date.getMonthDays() == date.getDay();
  }

  bool isLastDayInMonth() const { return isLastDayInMonth(*this); }

  // *************************************************************
  // *********************** Month Methods ***********************
  // *************************************************************

  // Returns false if newMonth is invalid
  bool setMonth(short newMonth) {
    if (!isValidMonth(newMonth))
      return false;

    _month = _month;
    return true;
  }
  short getMonth() const { return _month; }

  // Returns December if month not found
  static std::string findMonthFullName(short monthOrder) {
    if (monthOrder < 1 || monthOrder > 12)
      return "Dec";

    std::string *arr = getMonthsFullNames();
    std::string monthName = arr[monthOrder];
    delete[] arr;
    return monthName;
  }

  // Returns December if month not found
  std::string findMonthFullName() const { return findMonthFullName(_month); }

  // Returns Dec if month not found
  static std::string findMonthShortName(short monthOrder) {
    if (monthOrder < 1 || monthOrder > 12)
      return "Dec";

    std::string *arr = getMonthsShortNames();
    std::string monthName = arr[monthOrder];
    delete[] arr;
    return monthName;
  }

  // Returns Dec if month not found
  std::string findMonthShortName() const { return findMonthShortName(_month); }

  // Dont forget to DELETE THE ARRAY
  static std::string *getMonthsShortNames() {
    std::string *arr =
        new std::string[12]("Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul",
                            "Aug", "Sep", "Oct", "Nov", "Dec");

    return arr;
  }

  // Dont forget to DELETE THE ARRAY
  static std::string *getMonthsFullNames() {
    std::string *arr = new std::string[12](
        "January", "February", "March", "April", "May", "June", "July",
        "August", "September", "October", "November", "December");

    return arr;
  }

  static bool isValidMonth(short month) { return (month >= 1 && month <= 12); }

  static bool isValidMonth(std::string monthName) {
    std::string *fullNamesArr = getMonthsFullNames();
    std::string *shortNamesArr = getMonthsShortNames();
    for (int i = 0; i < 12; i++) {
      if (monthName == fullNamesArr[i] || monthName == shortNamesArr[i]) {
        delete[] fullNamesArr;
        delete[] shortNamesArr;
        return true;
      }
    }
    delete[] fullNamesArr;
    delete[] shortNamesArr;
    return false;
  }

  // returns -1 if it's invalid month
  static short getMonthDays(short month, short year) {
    if (!isValidMonth(month)) {
      return -1;
    }

    short numberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (month == 2) ? (isLeapYear(year) ? 29 : 28)
                        : numberOfDays[month - 1];
  }

  short getMonthDays() const { return getMonthDays(_month, _year); }

  static bool isLastMonth(short month) { return month == 12; }

  static bool isLastMonth(const TimeDate &date) {
    return isLastMonth(date.getMonth());
  }

  bool isLastMonth() const { return isLastMonth(_month); }

  // ************************************************************
  // *********************** Year methods ***********************
  // ************************************************************

  // Returns false if newYear is invalid
  bool setYear(short newYear) {
    if (!isValidYear(newYear))
      return false;

    _year = newYear;
    return true;
  }

  short getYear() const { return _year; }

  static bool isLeapYear(short year) {
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
  }

  bool isLeapYear() const { return isLeapYear(_year); }

  static bool isValidYear(short year) { return year > 0; }

  static void increaseByOneYear(TimeDate &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + 1);
  }

  void increaseByOneYear() { increaseByOneYear(*this); }

  static void decreaseByOneYear(TimeDate &date) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() - 1);
  }

  void decreaseByOneYear() { decreaseByOneYear(*this); }

  static void increaseByXYears(TimeDate &date, const int &years) {
    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }
    date.setYear(date.getYear() + years);
  }
  void increaseByXYears(const int &years) { increaseByXYears(*this, years); }

  static void decreaseByXYears(TimeDate &date, int yearsToRemove) {
    if (yearsToRemove >= date.getYear())
      return;

    if (date.getDay() == 29 && date.getMonth() == 2 && date.isLeapYear()) {
      date.setDay(28);
    }

    date.setYear(date.getYear() - yearsToRemove);
  }
  void decreaseByXYears(const int &yearsToRemove) {
    decreaseByXYears(*this, yearsToRemove);
  }

  static short getYearDays(short year) { return isLeapYear(year) ? 366 : 365; }
  short getYearDays() { return getYearDays(this->getYear()); }

  static short getYearHours(short year) { return getYearDays(year) * 24; }
  short getYearHours() { return getYearHours(this->getYear()); }

  static unsigned getYearMinutes(short year) { return getYearHours(year) * 60; }
  unsigned getYearMinutes() { return getYearMinutes(this->getYear()); }

  static unsigned getYearSeconds(short year) {
    return getYearMinutes(year) * 60;
  }
  unsigned getYearSeconds() { return getYearSeconds(this->getYear()); }

  static bool isEndOfYear(const TimeDate &date) {
    return date.isLastMonth() && date.isLastDayInMonth();
  }

  bool isEndOfYear() const { return isEndOfYear(*this); }

  // ************************************************************
  // *********************** Separator Methods ******************
  // ************************************************************

  // Returns false if newSeparator is empty
  bool setSeparator(std::string newSeparator) {
    if (!newSeparator.empty())
      return false;

    _separator = newSeparator;
    return true;
  }

  std::string getSeparator() const { return _separator; }

  // ************************************************************
  // *********************** Full Date Methods ******************
  // ************************************************************

  // If the given date is invalid, the data won't change
  bool setTimeDate(short day, short month, short year, short hour, short minute,
                   short second, std::string separator = "/") {
    if (!isValidTimeDate(day, month, year, hour, minute, second)) {
      return false;
    }

    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = second;
    _separator = separator;
    return true;
  }

  // Format as following, saying your separator is '/' => DD/MM/YYYY/HH/MM/SS
  // Returns false if newDate is invalid or something went wrong
  bool setTimeDate(std::string newDate, std::string separator = "/") {
    TimeDate *newTimeDate =
        TimeDate::convertStringToTimeDate(newDate, separator);
    if (newTimeDate == nullptr)
      return false;

    *this = *newTimeDate;
    delete newTimeDate;
    return true;
  }

  // Get today's date
  static TimeDate getTodayTimeDate(std::string separator = "/") {
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);

    return TimeDate(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900,
                    now->tm_hour, now->tm_min, now->tm_sec, separator);
  }

  std::string getStr() {
    std::string str;
    str += std::to_string(_day) + _separator;
    str += std::to_string(_month) + _separator;
    str += std::to_string(_year) + _separator;
    str += std::to_string(_hour) + _separator;
    str += std::to_string(_minute) + _separator;
    str += std::to_string(_second);
    return str;
  }

  static bool isValidTimeDate(short day, short month, short year, short hour,
                              short minute, short second) {

    return (isValidYear(year) && isValidMonth(month) &&
            isValidDay(day, month, year) && isValidHour(hour) &&
            isValidMinute(minute) && isValidSecond(second));
  }

  // PASS the correct separator, returns nullptr if something went wrong
  static TimeDate *convertStringToTimeDate(const std::string &date,
                                           const std::string separator) {
    std::vector<std::string> vDate = Mstring::split(date, separator);
    if (vDate.empty())
      return nullptr;

    short day = std::stoi(vDate.at(0));
    short month = std::stoi(vDate.at(1));
    short year = std::stoi(vDate.at(2));
    short hour = std::stoi(vDate.at(3));
    short minute = std::stoi(vDate.at(4));
    short second = std::stoi(vDate.at(5));

    if (!isValidTimeDate(day, month, year, hour, minute, second))
      return nullptr;

    return new TimeDate(day, month, year, hour, minute, second, separator);
  }
};

std::ostream &operator<<(std::ostream &os, const TimeDate &date) {
  std::string separator = date.getSeparator();
  os << date.getYear() << separator;
  os << date.getMonth() << separator;
  os << date.getDay() << ":";
  os << date.getHour() << separator;
  os << date.getMinute() << separator;
  os << date.getSecond();
  return os;
}

#endif