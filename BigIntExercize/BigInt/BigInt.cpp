#include "pch.h"
#include "BigInt.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <limits>
#include <cstdio>
#include <inttypes.h>
#include <vector>

constexpr uint64_t max_power10_in_max_power2[] = { 0, 100, 10000, 10000000, 1000000000, 1000000000000, 100000000000000, 10000000000000000, 10000000000000000000 };

constexpr uint64_t max_power10()
{
	return max_power10_in_max_power2[sizeof(BigInt::int_type)];
}

template <uint64_t T>
struct count_digits
{
	static constexpr uint64_t value = 1 + count_digits<T / 10>::value;

};

template <>
struct count_digits<0>
{
	static constexpr uint64_t value = 0;
};

constexpr uint64_t max_digits()
{
	return count_digits<max_power10()>::value;
}

BigInt::int_type BigInt::uint_union::rightmost() const
{
	return big_val;
}

BigInt::int_type BigInt::uint_union::leftmost() const
{
	const int_type h = big_val >> sizeof(int_type) * CHAR_BIT;
	return h;
}

BigInt::int_type BigInt::sint_union::toPositive() const
{
	if (big_val >= 0)
	{
		return big_val;
	}
	else
	{
		const int_type max = std::numeric_limits<int_type>::max();
		return max + (big_val + (sint_doublesize_type)1);
	}
}

bool BigInt::sint_union::sign() const
{
	return big_val >= 0;
}





BigInt::BigInt() 
	: m_data(1)
	, m_negativeFlag(false)
{}

BigInt::BigInt(sint_type num) : m_data(1) 
{
	if (num < 0) {
		m_negativeFlag = true;
		num = -num;
	}
	else
	{
		m_negativeFlag = false;
	}

	m_data[0] = num;
}

BigInt::BigInt(const BigInt& other) 
	: m_data(other.m_data)
	, m_negativeFlag(other.m_negativeFlag)
{}

BigInt::BigInt(BigInt&& other)
	: m_data(std::move(other.m_data))
	, m_negativeFlag(other.m_negativeFlag) 
{}

BigInt::BigInt(const std::string& numStr) : BigInt()
{
	if (numStr.length() == 0)
	{
		return;
	}

	if (numStr.c_str()[0] == '-')
	{
		m_negativeFlag = true;
	}

	for (size_t i = m_negativeFlag ? 1 : 0; i < numStr.length(); ++i)
	{
		const char c = numStr.c_str()[i];
		const int_type cipher = c - '0';

		*this *= 10;
		Sum(cipher);
	}
}

BigInt& BigInt::operator=(const BigInt& other) {
	m_data = other.m_data;
	m_negativeFlag = other.m_negativeFlag;

	return *this;
}

BigInt& BigInt::operator=(BigInt&& other) {
	std::swap(m_data, other.m_data);
	m_negativeFlag = other.m_negativeFlag;

	return *this;
}

BigInt::~BigInt() {

}

void BigInt::Sum(const BigInt& other)
{
	int_type rest{ 0 };

	const size_t maxLenght = std::max<size_t>(m_data.size(), other.m_data.size());
	m_data.resize(maxLenght);

	for (size_t i = 0; i < maxLenght; i++)
	{
		const uint_union a = {m_data[i]};
		const uint_union b =  { i < other.m_data.size() ? other.m_data[i] : (int_type)0 };
		
		const uint_union sum = { a.big_val + b.big_val + rest};

		m_data[i] = sum.rightmost();
		rest = sum.leftmost();
	}

	if (rest > 0)
	{
		m_data.push_back(rest);
	}
}

void BigInt::Sub(const BigInt& other)
{
	sint_doublesize_type rest{ 0 };

	const size_t maxLenght = std::max<size_t>(m_data.size(), other.m_data.size());
	m_data.resize(maxLenght);

	const bool aIsPositive = CompareAbs(other) >= 0;

	for (size_t i = 0; i < maxLenght; i++)
	{
		const sint_doublesize_type aSign = aIsPositive ? 1 : -1;
		const sint_doublesize_type bSign = -aSign;
		const sint_union a = { m_data[i] };
		const sint_union b = { i < other.m_data.size() ? other.m_data[i] : 0 };

		const sint_union sum = { aSign * a.big_val + bSign * b.big_val + rest };

		m_data[i] = sum.toPositive();
		rest = sum.sign() ? 0 : -1;
	}

	while (m_data.back() == 0 && m_data.size() > 1)
	{
		m_data.pop_back();
	}

	m_negativeFlag = (!m_negativeFlag && !aIsPositive) || (m_negativeFlag && aIsPositive); //NXOR
}

short BigInt::CompareAbs(const BigInt& other) const
{
	if (m_data.size() != other.m_data.size())
	{
		return m_data.size() > other.m_data.size() ? 1 : -1;
	}

	for (size_t i = 0; i < m_data.size(); i++)
	{
		const size_t index = m_data.size() - i - 1;
		
		if (m_data[index] != other.m_data[index])
		{
			return m_data[index] > other.m_data[index] ? 1 : -1;
		}
	}

	return 0; //they are equal
}

BigInt BigInt::Division(const BigInt& other)
{
	if (CompareAbs(other) < 0)
	{
		m_negativeFlag = false;
		container_type newData(1);

		BigInt rest{ *this };
		rest.m_negativeFlag = false;

		m_data = std::move(newData);
		return rest;
	}

	m_negativeFlag = (m_negativeFlag && !other.m_negativeFlag) || (!m_negativeFlag && other.m_negativeFlag); //XOR

	BigInt divisor(other);
	size_t differenceSize = m_data.size() - other.m_data.size(); //Min is 0
	divisor.m_data.insert(divisor.m_data.begin(), differenceSize, 0); //Multiply by base differenceSize times.

	container_type dataResult;


	while (CompareAbs(other) >= 0)
	{
		dataResult.push_front(0);

		while (CompareAbs(divisor) >= 0)
		{
			*this -= divisor;
			++dataResult.front();
		}

		divisor.m_data.pop_front();//Divide by base
	}

	while (dataResult.back() == 0 && dataResult.size() > 1)
	{
		dataResult.pop_back();
	}

	BigInt rest{ *this };
	rest.m_negativeFlag = false;

	m_data = std::move(dataResult);

	return rest;
}


void BigInt::ShiftLeft(int_type shiftNum)
{
	int_type rest{ 0 };

	for (size_t i = 0; i < m_data.size(); i++)
	{
		uint_union a = { m_data[i] };

		a.big_val <<= shiftNum;
		a.big_val |= rest;

		m_data[i] = a.rightmost();
		rest = a.leftmost();
	}

	if (rest > 0)
	{
		m_data.push_back(rest);
	}
}

void BigInt::ShiftRight(int_type shiftNum)
{
	int_type rest{ 0 };

	for (size_t i = 0; i < m_data.size(); i++)
	{
		const size_t index = m_data.size() - i - 1;
		const int_type maxShift = sizeof(int_type) * CHAR_BIT;

		uint_union a = { m_data[index] };
		a.big_val <<= maxShift;

		a.big_val >>= shiftNum;

		m_data[index] = a.leftmost();
		m_data[index] |= rest;
		rest = a.rightmost();
	}

	if (m_data.back() == 0 && m_data.size() > 1)
	{
		m_data.pop_back();
	}
}

BigInt::operator int_type() const
{
	return m_data[0];
}

BigInt& BigInt::operator+=(const BigInt& other)
{
	if ((m_negativeFlag && other.m_negativeFlag) || (!m_negativeFlag && !other.m_negativeFlag))
	{
		Sum(other);
	}
	else
	{
		Sub(other);
	}

	return *this;
}

BigInt& BigInt::operator-=(const BigInt& other)
{
	if ((m_negativeFlag && !other.m_negativeFlag) || (!m_negativeFlag && other.m_negativeFlag))
	{
		Sum(other);
	}
	else
	{
		Sub(other);
	}

	return *this;
}

BigInt& BigInt::operator*=(const BigInt& other)
{
	m_negativeFlag = (m_negativeFlag && !other.m_negativeFlag) || (!m_negativeFlag && other.m_negativeFlag); //XOR

	int_type rest{ 0 };

	
	const size_t newLenght = m_data.size() + other.m_data.size();
	container_type dataResult(newLenght - 1);

	for (size_t i = 0; i < m_data.size(); i++)
	{
		for (size_t j = 0; j < other.m_data.size(); j++)
		{
			const uint_union a = { m_data[i] };
			const uint_union b = { other.m_data[j]};

			const uint_union mul = { a.big_val * b.big_val + rest };

			const size_t index = i + j;
			dataResult[index] += mul.rightmost();
			rest = mul.leftmost();
		}
	}

	if (rest != 0)
	{
		dataResult.push_back(rest);
	}

	m_data = std::move(dataResult);

	return *this;
}

BigInt& BigInt::operator/=(const BigInt& other)
{
	Division(other);

	return *this;
}

BigInt& BigInt::operator%=(const BigInt& other)
{
	*this = Division(other);

	return *this;
}

BigInt operator+(const BigInt &a)
{
	return a;
}

BigInt operator-(const BigInt &a)
{
	BigInt c{ a };
	c.m_negativeFlag = !a.m_negativeFlag;

	return c;
}

BigInt operator+(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c += b;
	
	return c;
}

BigInt operator-(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c -= b;

	return c;
}

BigInt operator*(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c *= b;

	return c;
}

BigInt operator/(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c /= b;

	return c;
}

BigInt operator%(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c %= b;

	return c;
}

bool operator<(const BigInt &a, const BigInt &b)
{
	if (a.m_negativeFlag != b.m_negativeFlag)
	{
		return a.m_negativeFlag;
	}

	if (a.m_negativeFlag)
	{
		return a.CompareAbs(b) > 0;
	}
	else
	{
		return a.CompareAbs(b) < 0;
	}
}

bool operator>(const BigInt &a, const BigInt &b)
{
	return b < a;
}

bool operator<=(const BigInt &a, const BigInt &b)
{
	return !(a > b);
}

bool operator>=(const BigInt &a, const BigInt &b)
{
	return !(a < b);
}

bool operator==(const BigInt &a, const BigInt &b)
{
	return a.CompareAbs(b) == 0;
}

bool operator!=(const BigInt &a, const BigInt &b)
{
	return !(a == b);
}

BigInt& BigInt::operator++()
{
	*this += 1;
	return *this;
}

BigInt BigInt::operator++(int)
{
	BigInt result(*this);
	++(*this);
	return result;
}

BigInt& BigInt::operator--()
{
	*this -= 1;
	return *this;
}

BigInt BigInt::operator--(int)
{
	BigInt result(*this);
	--(*this);
	return result;
}

std::string IntToStringFormatted(uint64_t num)
{
	constexpr uint64_t maxzeroes = max_digits() - 1;
	std::string format = "%0";
	format.append(std::to_string(maxzeroes));
	format.append(PRIu64);

	char buffer[maxzeroes + 1];
	sprintf_s(buffer, maxzeroes + 1, format.c_str(), num);

	return buffer;
}

std::ostream& operator<<(std::ostream& os, const BigInt& bInt)
{
	std::vector<std::string> result;

	BigInt a{ bInt };
	a.m_negativeFlag = false;

	constexpr BigInt::int_type divisor = max_power10();
	while (a > divisor)
	{
		const BigInt rest = a.Division(divisor);
		const std::string resultDigit = IntToStringFormatted(rest.m_data[0]);

		result.push_back(resultDigit);
	}

	const std::string resultDigit = std::to_string(a.m_data[0]); //Last rest
	result.push_back(resultDigit);

	if (bInt.m_negativeFlag)
	{
		result.push_back("-");
	}

	std::reverse(result.begin(), result.end());



	for (size_t i = 0; i < result.size(); i++)
	{
		os << result[i];
	}

	return os;
}


BigInt& BigInt::operator&=(const BigInt& other)
{
	for (size_t i = 0; i < m_data.size(); i++)
	{
		const int_type b = { i < other.m_data.size() ? other.m_data[i] : (int_type)0 };

		m_data[i] &= b;
	}

	return *this;
}

BigInt& BigInt::operator|=(const BigInt& other)
{
	for (size_t i = 0; i < m_data.size(); i++)
	{
		const int_type b = { i < other.m_data.size() ? other.m_data[i] : (int_type)0 };

		m_data[i] |= b;
	}

	return *this;
}

BigInt& BigInt::operator^=(const BigInt& other)
{
	for (size_t i = 0; i < m_data.size(); i++)
	{
		const int_type b = { i < other.m_data.size() ? other.m_data[i] : (int_type)0 };

		m_data[i] ^= b;
	}

	return *this;
}

BigInt& BigInt::operator<<=(const BigInt& other)
{
	BigInt otherCpy{ other };

	while (otherCpy > 0)
	{
		int_type shiftNum{ 0 };

		const int_type maxShift = sizeof(int_type) * CHAR_BIT;

		if (otherCpy >= maxShift)
		{
			shiftNum = maxShift;
		}
		else
		{
			shiftNum = (int_type)otherCpy;
		}

		otherCpy -= maxShift;

		ShiftLeft(shiftNum);
	}

	return *this;
}

BigInt& BigInt::operator>>=(const BigInt& other)
{
	BigInt otherCpy{ other };

	while (otherCpy > 0)
	{
		int_type shiftNum{ 0 };

		const int_type maxShift = sizeof(int_type) * CHAR_BIT;

		if (otherCpy >= maxShift)
		{
			shiftNum = maxShift;
		}
		else
		{
			shiftNum = (int_type)otherCpy;
		}

		otherCpy -= maxShift;

		ShiftRight(shiftNum);
	}

	return *this;
}

BigInt operator~(const BigInt &a)
{
	BigInt c{ a };

	for (size_t i = 0; i < c.m_data.size(); i++)
	{
		c.m_data[i] = ~c.m_data[i];
	}

	return c;
}

BigInt operator&(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c &= b;

	return c;
}

BigInt operator|(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c |= b;

	return c;
}

BigInt operator^(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c ^= b;

	return c;
}

BigInt operator<<(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c <<= b;

	return c;
}

BigInt operator>>(const BigInt &a, const BigInt &b)
{
	BigInt c{ a };

	c >>= b;

	return c;
}

BigInt pow(const BigInt& base, const BigInt& exp)
{
	BigInt base_{ base };
	BigInt exp_{ exp };
	BigInt result{ 1 };

	while(exp_ != 0)
	{
		const bool isExpOdd = exp_.m_data[0] & 1;
		if (isExpOdd)
		{
			result *= base_;
		}

		exp_ >>= 1;

		base_ *= base_;
	}

	return result;
}