#pragma once

#include <deque>
#include<iosfwd>

class BigInt {

public:
	typedef uint32_t int_type;
	typedef int32_t sint_type;
	typedef uint64_t int_doublesize_type;
	typedef int64_t sint_doublesize_type;
	typedef std::deque<int_type> container_type;

	struct uint_union
	{
		int_doublesize_type big_val;

		int_type rightmost() const;
		int_type leftmost() const;
	};

	struct sint_union
	{
		sint_doublesize_type big_val;

		int_type toPositive() const;
		bool sign() const;
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

	explicit operator int_type() const;

	BigInt& operator+=(const BigInt& other);
	BigInt& operator-=(const BigInt& other);
	BigInt& operator*=(const BigInt& other);
	BigInt& operator/=(const BigInt& other);
	BigInt& operator%=(const BigInt& other);

	friend BigInt operator+(const BigInt& a);
	friend BigInt operator-(const BigInt& a);
	friend BigInt operator+(const BigInt& a, const BigInt& b);
	friend BigInt operator-(const BigInt& a, const BigInt& b);
	friend BigInt operator*(const BigInt& a, const BigInt& b);
	friend BigInt operator/(const BigInt& a, const BigInt& b);
	friend BigInt operator%(const BigInt& a, const BigInt& b);

	friend bool operator<(const BigInt &a, const BigInt &b);
	friend bool operator<=(const BigInt &a, const BigInt &b);
	friend bool operator>(const BigInt &a, const BigInt &b);
	friend bool operator>=(const BigInt &a, const BigInt &b);
	friend bool operator==(const BigInt &a, const BigInt &b);
	friend bool operator!=(const BigInt &a, const BigInt &b);

	BigInt& operator++();
	BigInt operator++(int);
	BigInt& operator--();
	BigInt operator--(int);

	friend std::ostream& operator<<(std::ostream&, const BigInt&);

	BigInt& operator&=(const BigInt& other);
	BigInt& operator|=(const BigInt& other);
	BigInt& operator^=(const BigInt& other);
	BigInt& operator<<=(const BigInt& other);
	BigInt& operator>>=(const BigInt& other);

	friend BigInt operator~(const BigInt& a);
	friend BigInt operator&(const BigInt& a, const BigInt& b);
	friend BigInt operator|(const BigInt& a, const BigInt& b);
	friend BigInt operator^(const BigInt& a, const BigInt& b);
	friend BigInt operator<<(const BigInt& a, const BigInt& b);
	friend BigInt operator>>(const BigInt& a, const BigInt& b);

	friend BigInt pow(const BigInt& ,const BigInt&);


private:
	void Sum(const BigInt& other);
	void Sub(const BigInt& other);
	short CompareAbs(const BigInt& other) const;
	BigInt Division(const BigInt& other);
	void ShiftLeft(int_type);
	void ShiftRight(int_type);

	bool m_negativeFlag;
	container_type m_data;
};

template <typename InputIt>
BigInt::BigInt(InputIt first, InputIt last, bool negativeFlag)
	: m_data(first, last)
	, m_negativeFlag(negativeFlag)
{
}