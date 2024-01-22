#include <iostream>
#include <array>

template <size_t _Line,size_t _Column,size_t MOD = 2147483647,typename _ValueType = int>
struct Matrix
{
	using ValueType = std::decay_t<_ValueType>;
	
	std::array<ValueType,_Column*_Line> __data {0};
	
	ValueType& at(size_t _line,size_t _column)
	{
		return __data[_line*_Column + _column];
	}
	
	const ValueType& at(size_t _line,size_t _column) const
	{
		return __data[_line*_Column + _column];
	}
	
	Matrix() = default;
	
	Matrix(const auto& base)
	{
		for(size_t i = 0;i < std::min(_Line,_Column);i ++)
		{
			this->at(i,i) = base % MOD;
		}
	}
	
	Matrix(const std::initializer_list<auto>& list)
	{
		size_t index = 0;
		auto ptr = __data.begin();
		auto iter = list.begin();
		size_t maxIndex = std::min(_Line*_Column,list.size());
		for(;index < maxIndex;index ++,ptr ++,iter ++)
		{
			*ptr = *iter % MOD;
		}
	}
	
	template <size_t _ResultColumn,typename _ValueTypeB>
	auto operator *(const Matrix<_Column,_ResultColumn,MOD,_ValueTypeB>& b) const
	{
		Matrix<_Line,_ResultColumn,MOD,std::common_type_t<_ValueType,_ValueTypeB>> result;
		for(size_t nowLine = 0;nowLine < _Line;nowLine ++)
		{
			for(size_t nowColumn = 0;nowColumn < _ResultColumn;nowColumn ++)
			{
				for(size_t i = 0;i < _Column;i ++)
				{
					result.at(nowLine,nowColumn) += this->at(nowLine,i) * b.at(i,nowColumn);
					result.at(nowLine,nowColumn) %= MOD;
				}
			}
		}
		return result;
	}
};

auto pow(auto base,size_t time)
{
	using BaseType = std::decay_t<decltype(base)>;
	
	BaseType result(1);
	
	while(time > 0)
	{
		if(time & 1)
		{
			result = result * base;
		}
		time >>= 1;
		base = base * base;
	}
	
	return result;
}
