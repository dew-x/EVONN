#include "Neuron.h"

Neuron::Neuron()
{
}

Neuron::Neuron(const std::vector<Data> &values, unsigned position, DataType returns)
{
	prepareConstants();
	std::vector<unsigned> possible(0);
	for (unsigned i = 0; i < functions.size(); ++i) {
		if (functions[i].isPossible(values, position, returns)) {
			possible.push_back(i);
		}
	}
	id = possible[rand() % possible.size()];
	func = functions[id];
	links = func.doLinks(values, position);
}

Neuron::Neuron(unsigned id, const std::vector<unsigned> &links)
{
	prepareConstants();
	this->links = std::vector<unsigned>(links.size());
	for (unsigned i = 0; i < links.size(); ++i) {
		this->links[i] = links[i];
	}
	func = functions[id];
}

Neuron::~Neuron()
{
	functions.clear();
	links.clear();
}

Data Neuron::eval(std::vector<Data> values) {
	return Data();
}

void Neuron::prepareConstants() {
	functions = {
		NF_sum_u(),
		NF_sum_r(),
		NF_sum_s()
	};
}

