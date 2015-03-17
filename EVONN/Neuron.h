#pragma once

enum DataType {
	DT_UNDEFINED = 0,
	DT_BOOLEAN = 1,
	DT_NATURAL = 2,
	DT_INTEGER = 4,
	DT_REAL = 8,
	DT_VECTOR = 16,
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
	Data(bool b) {
		this->b = b;
		dt = DT_BOOLEAN;
	}
	Data(unsigned long long u) {
		this->u = u;
		dt = DT_NATURAL;
	}
	Data(unsigned u) {
		this->u = (unsigned long long)u;
		dt = DT_NATURAL;
	}
	Data(signed long long s) {
		this->s = s;
		dt = DT_INTEGER;
	}
	Data(int s) {
		this->s = (signed long long)s;
		dt = DT_INTEGER;
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
		dt = DT_NATURAL;
	}
	void setValue(unsigned u) {
		this->u = (unsigned long long)u;
		dt = DT_NATURAL;
	}
	void setValue(signed long long s) {
		this->s = s;
		dt = DT_INTEGER;
	}
	void setValue(int s) {
		this->s = (signed long long)s;
		dt = DT_INTEGER;
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
};



class Neuron
{
public:
	Neuron();
	~Neuron();
};

