#include "Brain.h"


Brain::Brain(std::string fname)
{
}

Brain::Brain(const BrainSchema &schema)
{
	inputSize = schema.input.size();
	outputSize = schema.output.size();
	constantSize = schema.constants.size();
	variableSize = schema.variables.size();
	hiddenSize = (rand() % (inputSize + outputSize + hiddenSize + variableSize)) + 1;
	values = std::vector<Data>(inputSize + constantSize + variableSize + hiddenSize + outputSize);
	neurons = std::vector<Neuron>(hiddenSize + outputSize);
	for (unsigned i = 0; i < inputSize; ++i) {
		values[i].dt = schema.input[i];
	}
	for (unsigned i = 0; i < constantSize; ++i) {
		values[i + inputSize] = schema.constants[i];
	}
	for (unsigned i = 0; i < variableSize; ++i) {
		values[i + inputSize + constantSize] = Data((DataType)schema.variables[i]);
	}
	for (unsigned i = 0; i < outputSize; ++i) {
		values[i + inputSize + constantSize + variableSize + hiddenSize].dt = schema.output[i];
	}
	for (unsigned i = 0; i < hiddenSize; ++i) {
		// gen random
	}
}


Brain::~Brain()
{
}

void Brain::store(std::string fname) {

}

void Brain::tweak() {

}