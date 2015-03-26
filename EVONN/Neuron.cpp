#include "Neuron.h"

Neuron::Neuron()
{
}

Neuron::Neuron(const std::vector<Data> &values, unsigned position, DataType returns)
{
	prepareConstants();
	std::vector<unsigned> possible(0);
	for (unsigned i = 0; i < functions.size(); ++i) {
		if (functions[i]->isPossible(values, position, returns)) {
			possible.push_back(i);
		}
	}
	if (possible.size() == 0) {
		throw std::invalid_argument("NO POSSIBLE NEURONS");
	}
	id = possible[rand() % possible.size()];
	func = functions[id];
	links = func->doLinks(values, position);
}

Neuron::Neuron(unsigned id, const std::vector<unsigned> &links)
{
	prepareConstants();
	this->id = id;
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

Data Neuron::eval(const std::vector<Data> &values) {
	std::vector<Data> tmp(links.size());
	for (unsigned i = 0; i < links.size(); ++i) {
		tmp[i] = values[links[i]];
	}
	return func->eval(tmp);
}

void Neuron::prepareConstants() {
	functions = {
		new NF_sum_u(),
		new NF_sum_r(),
		new NF_sum_s(),
		new NF_sum_v(),
		new NF_if_u(),
		new NF_if_s(),
		new NF_if_r(),
		new NF_if_v(),
		new NF_if_b(),
	};
}

