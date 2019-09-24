#include "pch.h"
#include "BigInt.h"
#include <algorithm>
#include <iostream>


BigInt::BigInt() : m_data(1){

}

// BigInt::BigInt(int_type num) : m_data(1, num) {
// 
// }

BigInt::BigInt(sint_type num) : m_data(1) {
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
	, m_negativeFlag(other.m_negativeFlag){

}

BigInt::BigInt(BigInt&& other)
	: m_data(std::move(other.m_data))
	, m_negativeFlag(std::move(other.m_negativeFlag)) {

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
		const uint_union b =  { i < other.m_data.size() ? other.m_data[i] : 0 };
		
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

	const bool aIsPositive = GreaterOrEqualAbs(other);

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

bool BigInt::GreaterOrEqualAbs(const BigInt& other)
{
	if (m_data.size() != other.m_data.size())
	{
		return m_data.size() > other.m_data.size();
	}

	for (size_t i = 0; i < m_data.size(); i++)
	{
		const size_t index = m_data.size() - i - 1;
		
		if (m_data[index] != other.m_data[index])
		{
			return m_data[index] > other.m_data[index];
		}
	}

	return true; //they are equal
}

BigInt BigInt::Division(const BigInt& other)
{
	if (!GreaterOrEqualAbs(other))
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


	while (GreaterOrEqualAbs(other))
	{
		dataResult.push_front(0);

		while (GreaterOrEqualAbs(divisor))
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

std::ostream& operator<<(std::ostream& os, const BigInt& bInt)
{
	if (bInt.m_negativeFlag)
	{
		os << '-';
	}

	for (size_t i = 0; i < bInt.m_data.size(); i++)
	{
/*		const BigInt = */
		const size_t index = bInt.m_data.size() - i - 1;
		os << '0' + bInt.m_data[index];
	}

	return os;
}
