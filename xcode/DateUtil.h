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
namespace DateUtil {
    int getYearspan(boost::gregorian::date, boost::gregorian::date);
    int getMonthspan(boost::gregorian::greg_year);
    int getDayspan(boost::gregorian::greg_year, boost::gregorian::greg_month);
    long daysThisYear();
}


#endif /* defined(__Tuneline__DateHandler__) */
