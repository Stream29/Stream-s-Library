#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>


template<long long _BASE = (long long)1E9,char _split = '\0'>
class BigInteger
{
private:
	std::vector<long long> data;
	constexpr static long long BASE = _BASE;
	constexpr static int _getLength(long long base)
	{
		for(int length = 0;;length ++)
		{
			if(base < 10)
			{
				return length;
			}
			base /= 10;
		}
	}
	constexpr static int BASE_LENGTH = _getLength(BASE);
	void cutFrontZero()
	{
		while(!data.empty() && data.back()==0)
		{
			data.pop_back();
		}
	}
	void unify()
	{
		if(!data.empty())
		{
			for(size_t i = 0;i < data.size()-1;i ++)
			{
				if(data[i]*positivity() < 0)
				{
					//data[i] has wrong positivity
					data[i] += BASE * positivity();
					data[i+1] -= 1 * positivity();
				}
			}
		}
		cutFrontZero();
	}
	void sortOut()
	{
		for(size_t index = 0;index < data.size()-1;index ++)
		{
			data[index+1] += data[index] / BASE;
			data[index] %= BASE;
		}
		while(data.back() >= BASE)
		{
			data.push_back(data.back()/BASE);
			data[data.size()-2] %= BASE;
		}
		cutFrontZero();
		unify();
	}
	BigInteger& leftMove(int distance)
	{
		for(int i = 0;i < distance;i ++)
		{
			data.insert(data.begin(),0);
		}
		return *this;
	}
public:
	BigInteger() = default;
	BigInteger(std::string number)
	{
		if(number.front() == '-')
		{
			new (this) BigInteger(number.substr(1,number.size()-1));
			for(auto& n : data)
			{
				n = -n;
			}
			return;
		}
		while(number.size() > BASE_LENGTH)
		{
			data.push_back(
				std::stoll(
					number.substr(number.size()-BASE_LENGTH,BASE_LENGTH)));
			number = number.substr(0,number.size()-BASE_LENGTH);
			//阶梯形书写多行代码
		}
		data.push_back(std::stoll(number));
		cutFrontZero();
	}
	BigInteger(long long number)
	{
		new (this) BigInteger(std::to_string(number));
	}
	//类成员默认inline
	bool positivity() const
	{
		if(data.empty())
		{
			return true;
		}
		return data.back()<0 ? false : true;
	}
	friend bool operator <(const BigInteger& a,const BigInteger& b)
	{
		if(a.positivity() != b.positivity())
		{
			return !a.positivity();
		}
		if(a.data.size() != b.data.size())
		{
			return (a.data.size()<b.data.size()) ^ !a.positivity();
		}
		for(int i = a.data.size()-1;i >= 0;i --)
		{
			if(a.data[i] != b.data[i])
			{
				return (a.data[i]<b.data[i]) ^ !a.positivity();
			}
		}
		return false;
	}
	friend bool operator >(const BigInteger& a,const BigInteger& b)
	{
		if(a.positivity() != b.positivity())
		{
			return !b.positivity();
		}
		if(a.data.size() != b.data.size())
		{
			return (a.data.size()>b.data.size()) ^ !a.positivity();
		}
		for(int i = a.data.size()-1;i >= 0;i --)
		{
			if(a.data[i] != b.data[i])
			{
				return (a.data[i]>b.data[i]) ^ !a.positivity();
			}
		}
		return false;
	}
	BigInteger operator -() const
	{
		BigInteger result(*this);
		for(auto& n : result.data)
		{
			n = -n;
		}
		return result;
	}
	BigInteger& operator +=(const BigInteger& bi)
	{
		data.resize(std::max(data.size(),bi.data.size()));
		for(size_t index = 0;index < bi.data.size();index ++)
		{
			//proved index available for this and bi
			data[index] += bi.data[index];
		}
		sortOut();
		return *this;
	}
	friend BigInteger operator +(const BigInteger& a,const BigInteger& b)
	{
		BigInteger result;
		result += a;
		result += b;
		return result;
	}
	friend BigInteger operator -(const BigInteger& a,const BigInteger& b)
	{
		return a + (-b);
	}
	constexpr std::string toString() const
	{
		std::stringstream result;
		if(data.empty())
		{
			return "0";
		}
		result << data.back();
		for(auto riter = data.crbegin()+1;riter < data.crend();riter ++)
		{
			result << _split;
			result << std::setw(BASE_LENGTH) << std::setfill('0') << std::right;
			result << llabs(*riter);
		}
		return result.str();
	}
	friend std::ostream& operator <<(std::ostream& os,const BigInteger& bi)
	{
		os << bi.toString();
		return os;
	}
	friend bool operator ==(const BigInteger& a,const BigInteger& b)
	{
		return a.data == b.data;
	}
	BigInteger& operator *=(const int time)
	{
		for(auto& n: data)
		{
			n *= time;
		}
		sortOut();
		return *this;
	}
	friend BigInteger operator *(const BigInteger& bi,const int time)
	{
		BigInteger result(bi);
		result *= time;
		return result;
	}
	friend BigInteger operator *(const int time,const BigInteger& bi)
	{
		return bi * time;
	}
	friend BigInteger operator *(const BigInteger& a,const BigInteger& b)
	{
		BigInteger result;
		for(size_t i = 0;i < b.data.size();i ++)
		{
			result += (a*b.data[i]).leftMove(i);
		}
		return result;
	}
	friend BigInteger operator /(const BigInteger& a,const long long b)
	{
		if(a.data.empty())
		{
			return BigInteger(0);
		}
		BigInteger result = a;
		for(size_t i = result.data.size()-1;i > 0;i --)
		{
			result.data[i-1] += (result.data[i]%b) * BASE;
			result.data[i] /= b;
		}
		result.data[0] /= b;
		return result;
	}
	friend BigInteger operator /(const BigInteger& a,const BigInteger& b)
	{
		if(a < BigInteger(0))
		{
			return -(-a/b);
		}
		if(b < BigInteger(0))
		{
			return -(a/-b);
		}
		if(b == BigInteger(0))
		{
			throw std::logic_error("Divided by zero!");
		}
		if(a < b)
		{
			return BigInteger(0);
		}
		BigInteger result(1);
		BigInteger base(b);
		while(a > base*2)
		{
			base *= 2;
			result *= 2;
		}
		result += (a-base) / b;
		return result;
	}
	friend BigInteger operator %(const BigInteger& a,const BigInteger& b)
	{
		return a - a/b*b;
	}
};
auto operator ""_bi(unsigned long long number)
{
	return BigInteger(number);
}
auto operator ""_bi(char const * const text,std::size_t size)
{
	return BigInteger(std::string(text,size));
}

int main()
{
	BigInteger<1000,','> a(114514);
	std::cout << (a+=BigInteger<1000,','>(1)) << std::endl;
	return 0;
}
