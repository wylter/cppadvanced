#include "pch.h"
#include "BigInt.h"
#include <algorithm>


BigInt::BigInt() : m_data(1){

}

// BigInt::BigInt(int_type num) : m_data(1, num) {
// 
// }

BigInt::BigInt(int_signed num) : m_data(1) {
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

BigInt::BigInt(BigInt& other) 
	: m_data(other.m_data)
	, m_negativeFlag(other.m_negativeFlag){

}

BigInt::BigInt(BigInt&& other)
	: m_data(std::move(other.m_data))
	, m_negativeFlag(std::move(other.m_negativeFlag)) {

}

BigInt& BigInt::operator=(BigInt& other) {
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

	for (int i = 0; i < maxLenght; i++)
	{
		const int_union_type a = {m_data[i]};
		const int_union_type b =  { i < other.m_data.size() ? other.m_data[i] : 0 };
		
		const int_union_type sum = { a.big_val + b.big_val + rest};

		m_data[i] = sum.rightmost();
		rest = sum.leftmost();
	}

	if (rest > 0)
	{
		m_data.push_back(rest);
	}
}

BigInt& BigInt::operator+=(const BigInt& other)
{
	if ((m_negativeFlag && other.m_negativeFlag) || (!m_negativeFlag && !other.m_negativeFlag))
	{
		Sum(other);
	}

	return *this;
}

/*
BigInt& BigInt::operator+(const BigInt& other) {


}
*/