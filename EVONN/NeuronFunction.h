#pragma once
#include <vector>
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
};

class NF_sum_u : public NeuronFunction {
	public:
		NF_sum_u() {
			returns = DT_UNSIGNED;
			requires = {
				{ DT_UNSIGNED,2,REQ_MIN }
			};
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
};

class NF_sum_s : public NeuronFunction {
	public:
		NF_sum_s() {
			returns = DT_SIGNED;
			requires = {
				{ DT_INTEGER, 2, REQ_MIN }
			};
		}
};

