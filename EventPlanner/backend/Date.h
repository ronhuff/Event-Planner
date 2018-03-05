#ifndef DATE_H
#define DATE_H

#include "Executive.h"

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
