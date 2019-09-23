#pragma once

#include <deque>

class BigInt {

public:
	typedef uint8_t int_type;
	typedef uint16_t int_doublesize_type;
	typedef int8_t int_signed;

	struct int_union_type
	{
		int_doublesize_type big_val;

		int_type rightmost() const
		{
			return big_val;
		}

		int_type leftmost() const
		{
			const int_type h = big_val >> sizeof(int_type) * 8;
			return h;
		}
	};

	BigInt();
	//BigInt(int_type);
	BigInt(int_signed);
	BigInt(BigInt& other);
	BigInt(BigInt&& other);
	BigInt& operator=(BigInt& other);
	BigInt& operator=(BigInt&& other);
	virtual ~BigInt();

// 	BigInt& operator+() const;
// 	BigInt& operator-() const;
	BigInt& operator+=(const BigInt& other);
	BigInt& operator-=(const BigInt& other);
	BigInt& operator*=(const BigInt& other);
	BigInt& operator/=(const BigInt& other);
// 	BigInt& operator~() const;
	BigInt& operator&=(const BigInt& other);
	BigInt& operator|=(const BigInt& other);
	BigInt& operator^=(const BigInt& other);
// 	BigInt& operator<<(const BigInt& other) const;
// 	BigInt& operator>>(const BigInt& other) const;


private:
	void Sum(const BigInt& other);
	void Sub(const BigInt& other);

	bool m_negativeFlag;
	std::deque<int_type> m_data;
};