#include "NeuronFunction.h"


NeuronFunction::NeuronFunction()
{
}


NeuronFunction::~NeuronFunction()
{
}

bool NeuronFunction::isPossible(const std::vector<Data> &values, unsigned position, DataType returns) {
	if (returns == this->returns) {
		std::vector<requireInfo> tmp(requires.size());
		copy(requires.begin(), requires.end(), tmp.begin());
		for (unsigned i = 0; i < position; ++i) {
			for (unsigned j = 0; j < tmp.size(); ++j) {
				if (tmp[j].dt == values[i].dt && tmp[j].quantity>0) {
					--tmp[j].quantity;
					break;
				}
			}
		}
		/* check all requires met */
		for (unsigned j = 0; j < tmp.size(); ++j) {
			if (tmp[j].quantity>0) {
				return false;
			}
		}
		return true;
	}
	else return false;
}

std::vector<unsigned> NeuronFunction::doLinks(const std::vector<Data> &values, unsigned position) {

}
