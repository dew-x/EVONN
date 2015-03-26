#pragma once
#include <vector>
#include <iostream>
#include "data.h"

enum require_t {
	REQ_FIXED,
	REQ_MAX,
	REQ_MIN,
};

struct requireInfo {
	DataType dt;
	unsigned quantity;
	require_t type;
};

class NeuronFunction
{
protected:
	DataType returns;
	std::vector<requireInfo> requires;
public:
	NeuronFunction();
	~NeuronFunction();
	DataType getOutput() { return returns; }
	bool isPossible(const std::vector<Data> &values, unsigned position, DataType returns);
	std::vector<unsigned> doLinks(const std::vector<Data> &values, unsigned position);
	Data virtual eval(std::vector<Data> &input) = 0;
};

class NF_sum_u : public NeuronFunction {
	public:
		NF_sum_u() {
			returns = DT_UNSIGNED;
			requires = {
				{ DT_UNSIGNED,2,REQ_MIN }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			ret.u = 0;
			for (unsigned i = 0; i < input.size(); ++i) {
				ret.u += input[i].u;
			}
			return ret;
		}
};

class NF_sum_r : public NeuronFunction {
	public:
		NF_sum_r() {
			returns = DT_REAL;
			requires = {
				{ DT_NUMBER, 2,REQ_MIN }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			ret.r = 0;
			for (unsigned i = 0; i < input.size(); ++i) {
				ret.r += input[i].getAsReal();
			}
			return ret;
		}
};

class NF_sum_s : public NeuronFunction {
	public:
		NF_sum_s() {
			returns = DT_SIGNED;
			requires = {
				{ DT_INTEGER, 2, REQ_MIN }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			ret.s = 0;
			for (unsigned i = 0; i < input.size(); ++i) {
				ret.s += input[i].getAsSigned();
			}
			return ret;
		}
};

class NF_sum_v : public NeuronFunction {
	public:
		NF_sum_v() {
			returns = DT_VECTOR;
			requires = {
				{ DT_VECTOR, 2, REQ_MIN }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			ret.v.x = 0;
			ret.v.y = 0;
			for (unsigned i = 0; i < input.size(); ++i) {
				ret.v.x += input[i].v.x;
				ret.v.y += input[i].v.y;
			}
			return ret;
		}
};

class NF_if_u : public NeuronFunction {
	public:
		NF_if_u() {
			returns = DT_UNSIGNED;
			requires = {
				{ DT_BOOLEAN, 1, REQ_FIXED },
				{ DT_UNSIGNED, 2, REQ_FIXED }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			if (input[0].b) ret.u = input[1].u;
			else ret.u = input[2].u;
			return ret;
		}
};

class NF_if_s : public NeuronFunction {
	public:
		NF_if_s() {
			returns = DT_SIGNED;
			requires = {
				{ DT_BOOLEAN, 1, REQ_FIXED },
				{ DT_INTEGER, 2, REQ_FIXED }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			if (input[0].b) ret.s = input[1].getAsSigned();
			else ret.s = input[2].getAsSigned();
			return ret;
		}
};

class NF_if_r : public NeuronFunction {
	public:
		NF_if_r() {
			returns = DT_REAL;
			requires = {
				{ DT_BOOLEAN, 1, REQ_FIXED },
				{ DT_NUMBER, 2, REQ_FIXED }
			};
		}
		Data eval(std::vector<Data> &input) {
			Data ret(returns);
			if (input[0].b) ret.r = input[1].getAsReal();
			else ret.r = input[2].getAsReal();
			return ret;
		}
};

class NF_if_v : public NeuronFunction {
public:
	NF_if_v() {
		returns = DT_VECTOR;
		requires = {
			{ DT_BOOLEAN, 1, REQ_FIXED },
			{ DT_VECTOR, 2, REQ_FIXED }
		};
	}
	Data eval(std::vector<Data> &input) {
		Data ret(returns);
		if (input[0].b) ret.v = input[1].v;
		else ret.v = input[2].v;
		return ret;
	}
};

class NF_if_v : public NeuronFunction {
public:
	NF_if_v() {
		returns = DT_BOOLEAN;
		requires = {
			{ DT_BOOLEAN, 3, REQ_FIXED }
		};
	}
	Data eval(std::vector<Data> &input) {
		Data ret(returns);
		if (input[0].b) ret.b = input[1].b;
		else ret.b = input[2].b;
		return ret;
	}
};

