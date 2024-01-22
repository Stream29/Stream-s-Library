#include <iostream>
#include <vector>
#include <utility>
#include <concepts>

template <typename T>
concept Container = requires {std::begin(T{});std::end(T{});} && !(std::is_same_v<T,std::string>);

std::istream& operator >>(std::istream& is,Container auto& v)
{
	//input for a resized vector
	for(auto& e : v)
	{
		is >> e;
	}
	return is;
}

std::ostream& operator <<(std::ostream& os,const Container auto& v)
{
	for(const auto& e : v)
	{
		os << e << ' ';
	}
	return os;
}

