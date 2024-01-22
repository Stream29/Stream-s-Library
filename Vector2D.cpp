#include <vector>
#include <iostream>

template <typename T>
struct Vector2D
{
	std::vector<T> data;
	size_t xSize = 0;
	size_t ySize = 0;
	Vector2D() = default;
	Vector2D(size_t _xSize,size_t _ySize): xSize(_xSize),ySize(_ySize)
	{
		data.resize(xSize*ySize);
	}
	void resize(size_t _xSize,size_t _ySize)
	{
		xSize = _xSize;
		ySize = _ySize;
		data.resize(xSize*ySize);
	}
	T& at(size_t x,size_t y)
	{
		return data[x*ySize + y];
	}
};

template <typename T>
std::ostream& operator <<(std::ostream& os,Vector2D<T>& v)
{
	for(size_t x = 0;x < v.xSize;x ++)
	{
		for(size_t y = 0;y < v.ySize;y ++)
		{
			os << v.at(x,y) << " ";
		}
		os << std::endl;
	}
	return os;
}
