#include <iostream>
#include <vector>

bool isLeapYear(int year)
{
	if(year%400 == 0)
	{
		return true;
	}
	if(year%100 == 0)
	{
		return false;
	}
	if(year%4 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int getYearLength(int year)
{
	return isLeapYear(year) ? 366 : 365;
}
std::vector<int> monthLengthNormal {31,28,31,30,31,30,31,31,30,31,30,31};
std::vector<int> monthLengthLeap {31,29,31,30,31,30,31,31,30,31,30,31};
int getMonthLength(int year,int month)
{
	if(month<1 || month>12)
	{
		throw std::logic_error("invalid month in getMonthLength()");
	}
	if(isLeapYear(year))
	{
		return monthLengthLeap[month-1];
	}
	else
	{
		return monthLengthNormal[month-1];
	}
}
int getLengthBetweenYear(int yearBegin,int yearEnd)
{
	if(yearBegin > yearEnd)
	{
		return - getLengthBetweenYear(yearEnd,yearBegin);
	}
	int result = 0;
	for(int yearNow = yearBegin; yearNow < yearEnd; yearNow ++)
	{
		result += getYearLength(yearNow);
	}
	return result;
}

class Date
{
private:
	int moveToJanuary()   //return length to January
	{
		int result = 0;
		while(month > 1)
		{
			result += getMonthLength(year,month-1);
			month --;
		}
		return result;
	}
	int moveTo1st()   //return length to 1st
	{
		int result = day - 1;
		day = 1;
		return result;
	}
	int year = 0;
	int month = 0;
	int day = 0;

public:
	Date() {}
	Date(int year,int month,int day)
	{
		this->year = year;
		this->month = month;
		this->day = day;
	}
	friend int operator -(Date dateEnd,Date dateBegin)
	{
		int result = 0;
		//clear day difference
		result += dateEnd.moveTo1st();
		result -= dateBegin.moveTo1st();
		//clear month difference
		result += dateEnd.moveToJanuary();
		result -= dateBegin.moveToJanuary();
		//clear year difference
		result += getLengthBetweenYear(dateBegin.year,dateEnd.year);
		return result;
	}
};

int main()
{
	std::cout << (Date(2020,3,1) - Date(2020,1,1)) << std::endl;
}
