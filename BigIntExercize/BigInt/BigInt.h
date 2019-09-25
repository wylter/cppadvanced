#pragma once

#include <deque>
#include <limits>

class std::ostream;

class BigInt {

public:
	typedef uint8_t int_type;
	typedef uint16_t int_doublesize_type;
	typedef int16_t sint_doublesize_type;
	typedef int8_t sint_type;
	typedef std::deque<int_type> container_type;

	struct uint_union
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

	struct sint_union
	{
		sint_doublesize_type big_val;

		int_type toPositive() const
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

		bool sign() const
		{
			return big_val >= 0;
		}
	};



	BigInt();
	BigInt(sint_type);
	BigInt(const BigInt& other);
	BigInt(BigInt&& other);
	BigInt(const std::string&);
	template <typename InputIt>
	BigInt(InputIt first, InputIt last, bool negativeFlag = false);
	BigInt& operator=(const BigInt& other);
	BigInt& operator=(BigInt&& other);
	virtual ~BigInt();

// 	BigInt& operator+() const;
// 	BigInt& operator-() const;
	BigInt& operator+=(const BigInt& other);
	BigInt& operator-=(const BigInt& other);
	BigInt& operator*=(const BigInt& other);
	BigInt& operator/=(const BigInt& other);
	BigInt& operator%=(const BigInt& other);
// 	BigInt& operator~() const;
	BigInt& operator&=(const BigInt& other);
	BigInt& operator|=(const BigInt& other);
	BigInt& operator^=(const BigInt& other);
// 	BigInt& operator<<(const BigInt& other) const;
// 	BigInt& operator>>(const BigInt& other) const;

	friend BigInt operator+(const BigInt &a, const BigInt &b);
	friend BigInt operator-(const BigInt &a, const BigInt &b);
	friend BigInt operator*(const BigInt &a, const BigInt &b);
	friend BigInt operator/(const BigInt &a, const BigInt &b);
	friend BigInt operator%(const BigInt &a, const BigInt &b);
	friend bool operator<(const BigInt &a, const BigInt &b);
	friend bool operator<=(const BigInt &a, const BigInt &b);
	friend bool operator>(const BigInt &a, const BigInt &b);
	friend bool operator>=(const BigInt &a, const BigInt &b);

	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);

	friend std::ostream& operator<<(std::ostream&, const BigInt&);


private:
	void Sum(const BigInt& other);
	void Sub(const BigInt& other);
	short CompareAbs(const BigInt& other) const;
	BigInt Division(const BigInt& other);

	bool m_negativeFlag;
	container_type m_data;
};

template <typename InputIt>
BigInt::BigInt(InputIt first, InputIt last, bool negativeFlag /*= false*/)
	: m_data(first, last)
	, m_negativeFlag(negativeFlag)
{}