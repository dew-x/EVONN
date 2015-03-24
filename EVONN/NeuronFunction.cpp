#include "NeuronFunction.h"


NeuronFunction::NeuronFunction()
{
}


NeuronFunction::~NeuronFunction()
{
}

bool NeuronFunction::isPossible(const std::vector<Data> &values, unsigned position, DataType returns) {
	if (returns == this->returns || returns == DT_UNDEFINED) {
		std::vector<requireInfo> tmp(requires.size());
		copy(requires.begin(), requires.end(), tmp.begin());
		for (unsigned i = 0; i < position; ++i) {
			for (unsigned j = 0; j < tmp.size(); ++j) {
				if ((tmp[j].dt&values[i].dt)>0 && tmp[j].quantity>0) {
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
	std::vector<unsigned> ret(0);
	std::vector<std::vector<unsigned> > possible(requires.size(), std::vector<unsigned> (0));
	for (unsigned i = 0; i < position; ++i) {
		for (unsigned j = 0; j < requires.size(); ++j) {
			if ((requires[j].dt & values[i].dt)>0) {
				possible[j].push_back(i);
			}
		}
	}
	for (unsigned j = 0; j < requires.size(); ++j) {
		unsigned amount;
		switch (requires[j].type)
		{
			case REQ_FIXED:
				for (unsigned i = 0; i < requires[j].quantity; ++i) {
					// pick a random possible link
					unsigned id = rand() % possible[j].size();
					// add to links
					ret.push_back(possible[j][id]);
					// remove from possible
					possible[j].erase(possible[j].begin() + id);
				}
				break;
			case REQ_MAX:
				amount = (rand() % requires[j].quantity)+1;
				for (unsigned i = 0; i < amount; ++i) {
					// pick a random possible link
					unsigned id = rand() % possible[j].size();
					// add to links
					ret.push_back(possible[j][id]);
					// remove from possible
					possible[j].erase(possible[j].begin() + id);
				}
				break;
			case REQ_MIN:
				amount = (rand() % (possible[j].size()+1-requires[j].quantity)) + requires[j].quantity;
				for (unsigned i = 0; i < amount; ++i) {
					// pick a random possible link
					unsigned id = rand() % possible[j].size();
					// add to links
					ret.push_back(possible[j][id]);
					// remove from possible
					possible[j].erase(possible[j].begin() + id);
				}
				break;
			default:
				break;
		}
	}
	return ret;
}
