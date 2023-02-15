#include "Date.h"
Date::Date(const std::string& date) {
    std::string word;
    int i = 0;
    for (auto x : date)
    {
        if (x == '-')
        {
            if(i == 0)
                Date::day = std::stoi(word);
            else if(i == 1)
                Date::month = std::stoi(word);
            word = "";
            i++;

        }
        else {
            word = word + x;
        }
    }
    Date::year = std::stoi(word);
}
int Date::getDay() const {
    return day;
}

int Date::getMonth() const {
    return month;
}

int Date::getYear() const {
    return year;
}
// opeartor < compare its date with other date and returns true if its date is older.
bool Date::operator<(const Date *d) const {
    if(year < d->year)return true;

    else if (year == d->year && month < d->month) return true;

    else if (year == d->year && month == d->month && day < d->day) return true;

    return false;
}

// opeartor > compare its date with other date and returns true if its date is newer.
bool Date::operator>(const Date *d) const {
    if(year > d->year)return true;

    else if (year == d->year && month > d->month) return true;

    else if (year == d->year && month == d->month && day > d->day) return true;

    return false;
}
//opeartor = compare its date with other date and returns true if dates are equal.
bool Date::operator=(const Date *d) const {
    if(year == d->year && month == d->month && day == d->day) return true;

    return false;
}
