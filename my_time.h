

#ifndef __MY_TIME_H__
#define __MY_TIME_H__

#ifdef __cplusplus
extern "C"
{
#endif
 
#include <stdint.h>
 
#define	IsLeapYear(yr)	(!((yr) % 400) || (((yr) % 100) && !((yr) % 4)))
// number of seconds since 0 hrs, 0 minutes, 0 seconds, on the
// 1st of January 2000 UTC
typedef uint32_t utc_time;
 
// To be used with
struct utc_time_t
{
  uint8_t seconds;  // 0-59
  uint8_t minutes;  // 0-59
  uint8_t hour;     // 0-23
  uint8_t day;      // 0-30
  uint8_t month;    // 0-11
  uint16_t year;    // 2000+
} ;
 
/*********************************************************************
 * GLOBAL VARIABLES
 */
 
/*********************************************************************
 * FUNCTIONS
 */
 
  extern void convert_utc_time(uint16_t base_year, struct utc_time_t *tm, utc_time sec_time );
 
  /*
   * Converts UTCTimeStruct to UTCTime (seconds since 00:00:00 01/01/2000)
   *
   * tm - pointer to UTC time struct
   */
  extern utc_time convert_utc_secs(uint16_t base_year, const struct utc_time_t *tm );
 extern void utc_to_local_time(struct utc_time_t *tm);
 
#ifdef __cplusplus
}
#endif
 
#endif 