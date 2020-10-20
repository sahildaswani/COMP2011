#include <iostream>

using namespace std;


// Task 1
// determine whether a year is a leap year
bool is_leap_year(int year)
{
    if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
        return true;
    }
    else {
        return false;
    }
}

// Task 2 
// return number of days in a month
int get_num_month_days(int year, int month)
{
    if (month == 2){
        return (is_leap_year(year)) ? 29 : 28;
    }
    else if (month <= 7){
        return (month % 2 == 0) ? 30 : 31;
    }
    else {
        return (month % 2 == 0) ? 31 : 30;
    }
}

// Task 3
// return the anchor day of a century
int get_anchor_century(int year)
{
    int x = (year + 200) % 400;

    if (x >= 0 && x < 100){
        return 5;
    } 
    else if (x >= 100 && x < 200) {
        return 3;
    }
    else if (x >= 200 && x < 300){
        return 2;
    }
    else {
        return 0;
    }
}

// Task 4
// return the weekday after offset
int offset_weekday(int weekday, int offset)
{
    int x = weekday + offset;

    return (x >= 0) ? 
        x % 7 : 
        7 - (x*-1) % 7;
}

// Task 5
// return the anchor day of a year (the weekday of doomsdays)
int get_anchor_year(int year, int anchor_century)
{
    int yy = year % 100;

    int a = yy/12;
    int b = yy % 12;
    int c = b/4;

    int offset = (a + b + c + anchor_century) % 7;

    return offset;
}

// Task 6
// return the doomsday in a month
int get_doomsday(int year, int month)
{
    if (month != 2 && month % 2 == 0){
        return month;
    }
    else if (month == 3 || month == 5 || month == 7) {
        return month + 4;
    }
    else if (month == 9 || month == 11) {
        return month -4;
    }
    else if (month == 2) {
        return (is_leap_year(year)) ? 1 : 7;
    }
    else if (month == 1) {
        return (is_leap_year(year)) ? 4 : 3;
    }
    return 0;
}

// Task 7
// return the weekday of a date
int get_weekday(int year, int month, int day)
{
    int doomsday = get_doomsday(year, month);

    int offset = day - doomsday;

    int weekday = get_anchor_year(year, get_anchor_century(year));

    return offset_weekday(weekday, offset);
}

// print the calendar of the month containing the date
void print_calendar(int year, int month, int day)
{
    // print title
    cout << "==========================================================" << endl;
    cout << "Doomsday Calendar, in memorial of John Conway (1937-2020)." << endl;
    cout << "==========================================================" << endl;
    cout << "\t\t\t" <<year << "-" << month << endl;
    cout << "Sun\tMon\tTus\tWed\tThu\tFri\tSat" << endl;
    // print blank spaces
    int weekday = get_weekday(year, month, 1);
    for (int i = 0; i < weekday; i++) {
        cout << "\t";
    }
    // print dates
    int num_month_days = get_num_month_days(year, month);
    for (int date = 1; date <= num_month_days; date++) {
        // print date
        cout << date;
        if (date == day) cout << "*";
        // formating
        if (date < num_month_days) {
            if (weekday == 6) cout << endl;
            else cout << "\t";
        }
        else cout << endl;
        // update weekday
        weekday = offset_weekday(weekday, 1);
    }
    cout << "==========================================================" << endl;
}

int main()
{
    int year, month, day;
    cout << "Please input the date ('year month day'): ";
    cin >> year >> month >> day;
    print_calendar(year, month, day);
    return 0;
}