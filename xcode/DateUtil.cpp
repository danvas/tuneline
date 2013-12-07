//
//  DateUtil.cpp
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-17.
//
//
// Credit:


#include "DateUtil.h"
#include "cinder/Cinder.h"

#include <string>

using namespace std;
using namespace ci;
using namespace boost::gregorian;

namespace DateUtil
{

    //  impl by Pukku at stackoverflow.com
    int getYearspan(date date1, date date2)
    {
        try
        {
            partial_date pd1(date1.day(), date1.month());
            partial_date pd2(date2.day(), date2.month());

            int yearspan = date2.year() - date1.year();
            if (pd2 < pd1)
                yearspan -= 1;
            return yearspan;
        }
        catch(...)
        {
            return 0;
        }
        
    }
    
    int getMonthspan(greg_year gYear)
    {
        date gdate = date(gYear, Jan, 1);
        date today = day_clock::local_day();
        bool isCurrentYear = gYear == today.year();
        try {
            if (isCurrentYear)
            {
                int span = today.month() - gdate.month() + 1;
                //printf("\nmonths in year: %d", span);
                return span;
            }
            //printf("\nmonths in year: %d", 12);
            return 12;
            
        } catch (...) {
            printf("caught exception when calling DateUtil::getDayspan()");
            return 0;
        }
    }

    int getDayspan(greg_year gYear, greg_month gMonth)
    {
        date gdate = date(gYear, gMonth, 1);
        date today = day_clock::local_day();
        bool isCurrentMonth = ( gMonth  == today.month() &&
                                gYear   == today.year()     );
        try {
            
            if (isCurrentMonth)
            {
                //printf("\ndays in %s: %d", gMonth.as_short_string(), (int)today.day() );
                return today.day();
            }
            //printf("\ndays in %s: %d", gMonth.as_short_string(), (int)gdate.end_of_month().day() );
            return gdate.end_of_month().day();
            
        } catch (...) {
            printf("caught exception when calling DateUtil::getDayspan()");
            return 0;
        } 
    }
    
    
    
    long daysThisYear()
    {
        date today = day_clock::local_day();
        date_period range( date(today.year(), Jan, 1), today );
        return range.length().days() + 1;
    }
    
    int getLineResolution(date aDate, int level){
        switch (level) {
            case 0:// life
                return 1;
            case 1:// decades
                return (int)ceil( DateUtil::getYearspan( aDate, day_clock::local_day() )/10.0f );
            case 2:// years
                return getYearspan( aDate, day_clock::local_day() );
            case 3:// months
                return getMonthspan( greg_year(2013) );
            case 4:// days
                greg_year someYear = greg_year(2013);
                greg_month someMonth = greg_month(Nov);
                return DateUtil::getDayspan(someYear, someMonth);
        }
    }

    
}




