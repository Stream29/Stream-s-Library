#include <iostream>

#include "VectorIO.cpp"

#include <typeinfo>
#include <cxxabi.h>
#define varName(x) std::string(#x)
#define test_view(x) std::cout << type(x) << ' ' << varName(x) << " = " << x << std::endl
#define fmt(x) (varName(x) + " ="), x
#define nowFunc std::string(__PRETTY_FUNCTION__)
#define nowInfo (nowFunc+" at line "+std::to_string(__LINE__))
#define typeName(x) abi::__cxa_demangle(x.name(),0,0,0)
#define type(x) typeName(typeid(x))

template <typename... T>
void print(T&& ...args)
{
	((std::cout << std::forward<T>(args) << ' '), ...) << std::endl;
}

inline void wait()
{
	system("pause");
}

