#ifndef DATE_H
#define DATE_H

#include "Executive.h"
#include "Record.h"
#include "boost\date_time.hpp"

class Date{
  public:
    Date();
    Date(std::string inputDate);
    ~Date();
    std::list<std::string> getTimeSlots();
    std::string getDate(bool ifIO);
  private:
    std::list<std::string>* timeSlots;
    boost::gregorian::date date;
    std::string dateFormatFixer(std::string date);
};
#endif
