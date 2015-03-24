#pragma once
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include "NeuronFunction.h"
#include "data.h"
#include "error.h"
#include <stdexcept>

class Neuron {
	private:
		std::vector<unsigned> links;
		std::vector<NeuronFunction*> functions;
		unsigned id;
		NeuronFunction *func;
	public:
		Neuron();
		Neuron(const std::vector<Data> &values, unsigned position, DataType returns);
		Neuron(unsigned id, const std::vector<unsigned> &links);
		~Neuron();
		Data eval(const std::vector<Data> &values);
		unsigned getId() { return id; }
		std::vector<unsigned> getLinks() { return links; }
		DataType getOutput() { return func->getOutput(); }
	private:
		void prepareConstants();
};

