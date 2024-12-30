#include "./include/timedate.h"
#include <iostream>

int main() {
  TimeDate birthday("4/8/2005/0/0/0");
  std::cout << birthday << '\n';
  std::cout << TimeDate::calculateAgeInDays(birthday) << '\n';

  return 0;
}