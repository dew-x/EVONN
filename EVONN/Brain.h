#pragma once
#include <string>
#include <vector>
#include "Neuron.h"
#include "tinyxml2.h"
#include "error.h"
#include <stdexcept>

struct BrainSchema {
	std::vector<Data> constants;
	std::vector<DataType> input;
	std::vector<DataType> output;
	std::vector<DataType> variables;
	void addConstant(Data d) {
		constants.push_back(d);
	}
	void addInput(DataType dt) {
		input.push_back(dt);
	}
	void addOutput(DataType dt) {
		output.push_back(dt);
	}
	void addVariable(DataType dt) {
		output.push_back(dt);
	}
};

class Brain
{
	std::vector<Data> values;
	std::vector<Neuron> neurons;
	unsigned inputSize;
	unsigned constantSize;
	unsigned outputSize;
	unsigned hiddenSize;
	unsigned variableSize;
public:
	Brain(std::string fname);
	Brain(const BrainSchema &schema);
	~Brain();
	void store(std::string fname);
	void tweak();
	void eval(const std::vector<Data> &input, std::vector<Data> &output);
};

