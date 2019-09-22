#pragma once

#include <deque>

class BigInt {

public:
	typedef uint8_t int_type;
	typedef int16_t int_signed;

	BigInt();
	BigInt(int_type);
	BigInt(int_signed);
	BigInt(BigInt& other);
	BigInt(BigInt&& other);
	BigInt& operator=(BigInt& other);
	BigInt& operator=(BigInt&& other);
	virtual ~BigInt();

	BigInt& operator+(BigInt& other);

private:
	bool m_negativeFlag;
	std::deque<int_type> m_data;
};