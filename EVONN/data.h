#pragma once
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "error.h"

enum DataType {
	DT_UNDEFINED = 0,
	DT_BOOLEAN = 1,
	DT_UNSIGNED = 2,
	DT_SIGNED = 4,
	DT_REAL = 8,
	DT_VECTOR = 16,
	DT_NUMBER = DT_UNSIGNED | DT_SIGNED | DT_REAL,
	DT_INTEGER = DT_UNSIGNED | DT_SIGNED
};

struct vec2 {
	float x, y;
};

struct Data {
	DataType dt;
	union {
		bool b;
		unsigned long long u;
		signed long long s;
		double r;
		vec2 v;
	};
	// nasty fix
	Data() {
		dt = DT_UNDEFINED;
		u = 0;
	}
	Data(DataType dt) {
		this->dt = dt;
		switch (dt)
		{
		case DT_BOOLEAN:
			b = (rand() % 2 == 0);
			break;
		case DT_UNSIGNED:
			u = rand();
			break;
		case DT_SIGNED:
			s = rand() - (RAND_MAX / 2);
			break;
		case DT_REAL:
			r = (double(rand()) / RAND_MAX) * 2 - 1;
			break;
		case DT_VECTOR:
			v.x = (float(rand()) / RAND_MAX) * 2 - 1;
			v.y = (float(rand()) / RAND_MAX) * 2 - 1;
			break;
		default:
			u = 0;
			break;
		}
	}
	Data(bool b) {
		this->b = b;
		dt = DT_BOOLEAN;
	}
	Data(unsigned long long u) {
		this->u = u;
		dt = DT_UNSIGNED;
	}
	Data(unsigned u) {
		this->u = (unsigned long long)u;
		dt = DT_UNSIGNED;
	}
	Data(signed long long s) {
		this->s = s;
		dt = DT_SIGNED;
	}
	Data(int s) {
		this->s = (signed long long)s;
		dt = DT_SIGNED;
	}
	Data(double r) {
		this->r = r;
		dt = DT_REAL;
	}
	Data(float r) {
		this->r = (double)r;
		dt = DT_REAL;
	}
	Data(vec2 v) {
		this->v = v;
		dt = DT_VECTOR;
	}
	Data(float x, float y) {
		this->v = { x, y };
		dt = DT_VECTOR;
	}
	void setValue(bool b) {
		this->b = b;
		dt = DT_BOOLEAN;
	}
	void setValue(unsigned long long u) {
		this->u = u;
		dt = DT_UNSIGNED;
	}
	void setValue(unsigned u) {
		this->u = (unsigned long long)u;
		dt = DT_UNSIGNED;
	}
	void setValue(signed long long s) {
		this->s = s;
		dt = DT_SIGNED;
	}
	void setValue(int s) {
		this->s = (signed long long)s;
		dt = DT_SIGNED;
	}
	void setValue(double r) {
		this->r = r;
		dt = DT_REAL;
	}
	void setValue(float r) {
		this->r = (double)r;
		dt = DT_REAL;
	}
	void setValue(vec2 v) {
		this->v = v;
		dt = DT_VECTOR;
	}
	void setValue(float x, float y) {
		this->v = { x, y };
		dt = DT_VECTOR;
	}
	std::string hexStr() {
		std::ostringstream stringStream;
		stringStream << std::setfill('0') << std::setw(16) << std::hex << u;
		return stringStream.str();
	}
	void parseHexStr(std::string str) {
		std::stringstream ss;
		ss << std::hex << str;
		ss >> u;
	}
	signed long long getAsSigned() {
		if (dt == DT_SIGNED) return s;
		else if (dt == DT_UNSIGNED) return (signed long long) u;
		else throw CANT_DO_THAT_ERROR;
	}
	double getAsReal() {
		if (dt == DT_REAL) return r;
		else if (dt == DT_UNSIGNED) return (double)u;
		else if (dt == DT_SIGNED) return (double)s;
		else throw CANT_DO_THAT_ERROR;
	}
	void print() {
		switch (dt)
		{
		case DT_UNDEFINED:
			std::cout << "UNDEFINED" << std::endl;
			break;
		case DT_BOOLEAN:
			std::cout << "BOOL("<<b<<")" << std::endl;
			break;
		case DT_UNSIGNED:
			std::cout << "UNSIGNED(" << u << ")" << std::endl;
			break;
		case DT_SIGNED:
			std::cout << "SIGNED(" << s << ")" << std::endl;
			break;
		case DT_REAL:
			std::cout << "REAL(" << r << ")" << std::endl;
			break;
		case DT_VECTOR:
			std::cout << "VECTOR(" << v.x<<","<<v.y << ")" << std::endl;
			break;
		default:
			break;
		}
	}
};