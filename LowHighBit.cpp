#include <concepts>
#include <iostream>

template <typename Num_t,unsigned int i>
requires (i >= sizeof(Num_t)*8) && std::integral<Num_t>
Num_t __highBit(Num_t n)
{
	return (n+1) >> 1;
}

template <typename Num_t,unsigned int i>
requires (i < sizeof(Num_t)*8) && std::integral<Num_t>
Num_t __highBit(Num_t n)
{
	return _highBit<Num_t,(i<<1)> (n | (n>>i));
}

template <typename Num_t>
requires std::integral<Num_t>
Num_t highBit(Num_t n)
{
	return _highBit<Num_t,1>(n);
}

template <typename Num_t>
requires std::integral<Num_t>
Num_t lowBit(Num_t n)
{
	return n & -n;
}
