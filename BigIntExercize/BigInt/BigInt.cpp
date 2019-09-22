#include "pch.h"
#include "BigInt.h"


BigInt::BigInt() : m_data(1){

}

BigInt::BigInt(int_type num) : m_data(1, num) {

}

BigInt::BigInt(int_signed num) : m_data(1) {
	if (num < 0) {
		m_negativeFlag = true;
		num = -num;
	}

	m_data[0] = num;
}

BigInt::BigInt(BigInt& other) 
	: m_data(other.m_data)
	, m_negativeFlag(other.m_negativeFlag){

}

BigInt::BigInt(BigInt&& other)
	: m_data(other.m_data)
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

/*
BigInt& BigInt::operator+(BigInt& other) {


}
*/

BigInt::~BigInt() {

}