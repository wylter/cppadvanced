#pragma once

#include <deque>
#include <limits>

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
				return max + big_val;
			}
		}

		sint_type toNegative() const
		{
			if (big_val >= 0)
			{
				return 0;
			}
			else
			{
				return big_val;
			}
		}

		bool sign()
		{
			return big_val > 0;
		}
	};



	BigInt();
	//BigInt(int_type);
	BigInt(sint_type);
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
	bool GreaterAbs(const BigInt& other);

	bool m_negativeFlag;
	container_type m_data;
};