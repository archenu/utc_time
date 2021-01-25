#include "my_time.h"
 
#define	YearLength(yr)	(IsLeapYear(yr) ? 366 : 365)
 
/*********************************************************************
 * CONSTANTS
 */
 
// (MAXCALCTICKS * 5) + (max remainder) must be <= (uint16 max),
// so: (13105 * 5) + 7 <= 65535
#define MAXCALCTICKS  ((uint16)(13105))
 
#define	BEGYEAR	        2000     // UTC started at 00:00:00 January 1, 2000
 
#define	DAY             86400UL  // 24 hours * 60 minutes * 60 seconds
 
 
/*********************************************************************
 * EXTERNAL VARIABLES
 */
 
 
static uint8_t monthLength( uint8_t lpyr, uint8_t mon )
{
  uint8_t days = 31;
 
  if ( mon == 1 ) // feb
  {
    days = ( 28 + lpyr );
  }
  else
  {
    if ( mon > 6 ) // aug-dec
    {
      mon--;
    }
 
    if ( mon & 1 )
    {
      days = 30;
    }
  }
 
  return ( days );
}
 
 
void convert_utc_time(uint16_t base_year, struct utc_time_t *tm, utc_time sec_time )
{
  // calculate the time less than a day - hours, minutes, seconds
  {
    uint32_t day = sec_time % DAY;
    tm->seconds = day % 60UL;
    tm->minutes = (day % 3600UL) / 60UL;
    tm->hour = day / 3600UL;
  }
  // Fill in the calendar - day, month, year
  {
    uint16_t numDays = sec_time / DAY;
    tm->year = base_year;
    while ( numDays >= YearLength( tm->year ) )
    {
      numDays -= YearLength( tm->year );
      tm->year++;
    }
 
    tm->month = 0;
    while ( numDays >= monthLength( IsLeapYear( tm->year ), tm->month ) )
    {
      numDays -= monthLength( IsLeapYear( tm->year ), tm->month );
      tm->month++;
    }
 
    tm->day = numDays;
  }
  
  tm->day += 1;
  tm->month += 1;
}
 
 
 
 
utc_time convert_utc_secs(uint16_t base_year,  const struct utc_time_t *tm )
{
  uint32_t seconds;

  /* Seconds for the partial day */
  seconds = (((tm->hour * 60UL) + tm->minutes) * 60UL) + tm->seconds;
 
  /* Account for previous complete days */
  {
    /* Start with complete days in current month */
    uint16_t days = tm->day-1;
 
    /* Next, complete months in current year */
    {
      int8_t month = tm->month-1;
      while ( --month >= 0 )
      {
        days += monthLength( IsLeapYear( tm->year ), month );
      }
    }
 
    /* Next, complete years before current year */
    {
      uint16_t year = tm->year;
      while ( --year >= base_year )
      {
        days += YearLength( year );
      }
    }
 
    /* Add total seconds before partial day */
    seconds += (days * DAY);
  }
 
  return ( seconds );
}

/**
 * @brief 将utc时间转换为本地时间，先转为秒再加上8小时对应的秒数
 * 
 * @param tm utc时间，既是输入也是输出
 */
void utc_to_local_time(struct utc_time_t *tm)
{
    
    utc_time  seconds = convert_utc_secs(1970, tm);
    seconds += 8*3600;
    convert_utc_time(1970, tm, seconds);
};