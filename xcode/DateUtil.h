//
//  DateUtil.h
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-17.
//
//

#ifndef __Tuneline__DateHandler__
#define __Tuneline__DateHandler__

#include "cinder/Cinder.h"
#include "boost/date_time/gregorian/gregorian.hpp"

#include <iostream>
#include <string>

class DateUtil {
public:
    DateUtil();
    boost::gregorian::date getDate();
    void setDate(std::string localDate);
    void setDate(boost::gregorian::greg_year,
                     boost::gregorian::greg_month,
                     boost::gregorian::greg_day);
    
    unsigned int yearsSince(std::string);

    unsigned int daysSince(std::string);

    
private:
    boost::gregorian::date mDate;
    unsigned int mDay;
    unsigned int mMonth;
    unsigned int mYear;
    
};


#endif /* defined(__Tuneline__DateHandler__) */
