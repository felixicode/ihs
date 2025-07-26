#ifndef RTC_H_
#define RTC_H_

//#define RTC_SET
#ifdef RTC_SET
void rtc_set_date_time(u8 n, u8 y, u8 r, u8 s, u8 f, u8 m);
void rtc_set_week_day(u8 n);
#endif

void rtc_read(char *arr, char len);
#endif