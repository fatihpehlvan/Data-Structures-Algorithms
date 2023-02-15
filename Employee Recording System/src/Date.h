#ifndef AS2_2_DATE_H
#define AS2_2_DATE_H

#include <iostream>

class Date {
private:
    int day;
    int month;
    int year;
public:
    Date(const std::string& date);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    bool operator <(const Date* d) const;

    bool operator =(const Date* d) const;

    bool operator >(const Date* d) const;
};

#endif //AS2_2_DATE_H
