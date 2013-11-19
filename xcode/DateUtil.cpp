//
//  DateUtil.cpp
//  Tuneline
//
//  Created by Daniel Vasquez on 2013-11-17.
//
//
// Credit:
// Pukku at stackoverflow.com

#include "DateUtil.h"
#include "cinder/Cinder.h"


#include <string>

using namespace std;
using namespace ci;
using namespace boost::gregorian;



DateUtil::DateUtil(){
    date today = day_clock::local_day();
    date::ymd_type ymd = today.year_month_day();
    setDate(ymd.year, ymd.month, ymd.day);
    cout << "\ndate created: " << to_simple_string(today) << endl;
}

date DateUtil::getDate()
{
    return mDate;
}

void DateUtil::setDate(string localDate)
{
    try {
        date aDate(from_simple_string(localDate));
        mDate = aDate;
        mYear = mDate.year();
        mMonth = mDate.month();
        mDay = mDate.day();
        
    } catch (...) {
        cout << "\nBad date entered: " << localDate << endl;
        cout << "Date must be in format yyyy-mm-dd" << endl;
    }
    
}

void DateUtil::setDate(greg_year gYear, greg_month gMon, greg_day gDay)
{
    try {
        date aDate(gYear, gMon, gDay);
        mDate = aDate;
        mYear = mDate.year();
        mMonth = mDate.month();
        mDay = mDate.day();
        
    } catch (...) {
        cout << "Date must be passed in as (boost::gregorian::greg_year, boost::gregorian::greg_month, boost::gregorian::greg_day)" << endl;
    }
    
}


unsigned int DateUtil::yearsSince(string aDate)
{
    try {
        //Implementation by Pukku
        date date1 = from_simple_string(aDate);
        if (date1 > mDate)
            std::swap(date1, mDate); // guarantee that d2 >= d1
        
        partial_date pd1(date1.day(), date1.month());
        partial_date pd2(mDate.day(), mDate.month());
        
        int fullYearsInBetween = mDate.year() - date1.year();
        if (date1 > mDate)
            fullYearsInBetween -= 1;
        
        return fullYearsInBetween;
        
    }
    catch(...)
    {
        cout << "\nBad date entered: " << aDate << endl;
        cout << "Date must be in format yyyy-mm-dd" << endl;
        return 0;
    }

}



unsigned int DateUtil::daysSince(string bdate)
{
    try {
        date birthday(from_simple_string(bdate));
        days days_alive = mDate - birthday;
        days one_day(1);
        if (days_alive == one_day) {
            std::cout << "Born yesterday, very funny" << std::endl;
            return 0;
        }
        else if (days_alive < days(0)) {
            std::cout << "Not born yet, hmm: " << days_alive.days()
            << " days" <<std::endl;
            return 0;
        }
        else {
            std::cout << "Days alive: " << days_alive.days() << std::endl;
            //cout << "oneyr = " << oneyr << endl;
            return (unsigned int)days_alive.days();
            
            
        }
        
    }
    catch(...) {
        cout << "\nBad date entered: " << bdate << endl;
        cout << "Date must be in format yyyy-mm-dd" << endl;
        return 0;
    }

}



