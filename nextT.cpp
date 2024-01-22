#include <iostream>
#include <tuple>

template <typename T>
T next()
{
	T temp;
	std::cin >> temp;
	return temp;
}

template <typename... T>
std::tuple<T...> multinext()
{
	return {next<T>()...};
}
