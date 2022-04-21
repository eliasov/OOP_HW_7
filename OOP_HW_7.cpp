#include <iostream>

class Date
{
private:
	int m_day;
	int m_month;
	int m_year;
public:
	Date(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}

	const int& getDay() const
	{
		return m_day;
	}

	const int& getMonth() const
	{
		return m_month;
	}

	const int& getYear() const
	{
		return m_year;
	}

	friend std::ostream& operator<<(std::ostream& os, const Date& d)
	{
		os << d.m_day << '.' << d.m_month << '.' << d.m_year;

		return os;
	}
};

template <class T>
class _ptr
{
private:
	T* m_ptr;
public:
	_ptr(T* ptr = nullptr) : m_ptr(ptr) {}
	~_ptr() { delete m_ptr; }

	_ptr(_ptr& p)
	{
		m_ptr = p.m_ptr;
		p.m_ptr = nullptr;
	}

	_ptr& operator=(_ptr& p)
	{
		if (&p == this)
			return *this;

		delete m_ptr;
		m_ptr = p.m_ptr;
		p.m_ptr = nullptr;

		return *this;
	}

	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }

	bool isNull() const { return m_ptr == nullptr; }
};

const _ptr<Date>& compares_dates(const _ptr<Date>&, const _ptr<Date>&);

void ex_1();
void ex_2();

void ex_1()
{
	_ptr<Date> today(new Date(10, 07, 2021));

	std::cout << "Day: " << today->getDay() << std::endl;
	std::cout << "Month: " << today->getMonth() << std::endl;
	std::cout << "Year: " << today->getYear() << std::endl;
	std::cout << "today: " << *today << std::endl;

	_ptr<Date> date;

	std::cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	std::cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	date = today;

	std::cout << "today is " << (today.isNull() ? "null\n" : "not null\n");
	std::cout << "date is " << (date.isNull() ? "null\n" : "not null\n");

	std::cout << "date: " << *date << std::endl;
}

const _ptr<Date>& compares_dates(const _ptr<Date>& a, const _ptr<Date>& b)
{
	if (a->getYear() > b->getYear())
		return a;
	else if (a->getYear() < b->getYear())
		return b;
	else
	{
		if (a->getMonth() > b->getMonth())
			return a;
		else if (a->getMonth() < b->getMonth())
			return b;
		else
		{
			if (a->getDay() > b->getDay())
				return a;
			else
				return b;
		}
	}
}

void swap_dates(_ptr<Date>& a, _ptr<Date>& b)
{
	_ptr<Date> temp(a);
	a = b;
	b = temp;
}

void ex_2()
{
	_ptr<Date> date1(new Date(9, 07, 2022));
	_ptr<Date> date2(new Date(10, 07, 2022));
	_ptr<Date> date3(new Date(11, 07, 2022));

	std::cout << *compares_dates(date1, date2) << std::endl;
	swap_dates(date2, date3);
	std::cout << *compares_dates(date1, date2) << std::endl;
}

int main()
{
	ex_1();
	ex_2();

	return 0;
}