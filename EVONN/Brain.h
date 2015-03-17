#pragma once
#include <string>
#include <vector>
#include "Neuron.h"
#include "tinyxml2.h"

struct BrainSchema {
	std::vector<Data> constants;
	std::vector<DataType> input;
	std::vector<DataType> output;
	void addConstant(Data d) {
		constants.push_back(d);
	}
	void addInput(DataType dt) {
		input.push_back(dt);
	}
	void addOutput(DataType dt) {
		output.push_back(dt);
	}
};

class Brain
{
public:
	Brain(std::string fname);
	Brain(const BrainSchema &schema);
	~Brain();
	void store(std::string fname);
	void tweak();
};

