#include "./include/timedate.h"
#include <iostream>

int main() {
  TimeDate tm("3/12/2020/1/30/00");

  TimeDate tm2(tm);

  TimeDate tm3;
  tm3 = tm;

  std::cout << tm2 << '\n';

  return 0;
}