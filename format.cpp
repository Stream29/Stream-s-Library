/*
  This program provides a alternative to std::format() in C++20.
  It is not perfect due to the author's programing level.
  Thanks!
  Author : Stream in NEUQ
*/

#include <initializer_list>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

template <typename T>

string format(string text,initializer_list<T> args)
{
	stringstream result;
	auto nowArg = args.begin();
	for(size_t i = 0;i+1 < text.size();i ++)
	{
		if(text[i]=='{' && text[i+1]=='}')
		{
			result << *nowArg;
			nowArg ++;
			i ++;
		}
		else
		{
			result << text[i];
		}
	}
	result << text.back();
	return result.str();
}
