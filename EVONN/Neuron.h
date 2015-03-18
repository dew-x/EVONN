#pragma once
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include "NeuronFunction.h"
#include "data.h"

class Neuron {
	private:
		std::vector<unsigned> links;
		unsigned id;
		DataType output;
		NeuronFunction func;
	public:
		Neuron();
		Neuron(std::vector<Data> values, unsigned position, DataType returns);
		Neuron(unsigned id, const std::vector<unsigned> &links);
		~Neuron();
		Data eval(std::vector<Data> values);
		unsigned getId() { return id; }
		std::vector<unsigned> getLinks() { return links; }
		DataType getOutput() { return output; }
	private:
		void prepareConstants();
};

