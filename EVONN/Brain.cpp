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
		values[i + inputSize + constantSize] = Data(schema.variables[i]);
	}
	for (unsigned i = 0; i < outputSize; ++i) {
		values[i + inputSize + constantSize + variableSize + hiddenSize].dt = schema.output[i];
	}
	for (unsigned i = 0; i < hiddenSize+outputSize; ++i) {
		// gen random
		neurons[i] = Neuron();
	}
}


Brain::~Brain()
{
	neurons.clear();
	values.clear();
}

void Brain::store(std::string fname) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLPrinter printer;
	printer.OpenElement("brain");
	// store number of input
	printer.OpenElement("input");
	printer.PushText(inputSize);
	printer.CloseElement();
	// store number of input
	printer.OpenElement("constant");
	printer.PushText(constantSize);
	printer.CloseElement();
	// store number of input
	printer.OpenElement("variable");
	printer.PushText(variableSize);
	printer.CloseElement();
	// store number of hidden
	printer.OpenElement("hidden");
	printer.PushText(hiddenSize);
	printer.CloseElement();
	// store number of output
	printer.OpenElement("output");
	printer.PushText(outputSize);
	printer.CloseElement();
	printer.OpenElement("dataList");
	for (unsigned i = 0; i < inputSize + constantSize + variableSize + hiddenSize + outputSize; ++i) {
		printer.OpenElement("data");
		printer.OpenElement("type");
		printer.PushText(values[i].dt);
		printer.CloseElement();
		printer.OpenElement("value");
		printer.PushText(values[i].hexStr().c_str(),false);
		printer.CloseElement();
		printer.CloseElement();
	}
	printer.CloseElement();
	/*for (unsigned i = 0; i < output + hidden; ++i) {
		printer.OpenElement("node");
		printer.PushAttribute("inf", nodes[i].in);
		printer.PushAttribute("outf", nodes[i].out);
		printer.PushAttribute("size", nodes[i].ids.size());
		for (unsigned j = 0; j < nodes[i].ids.size(); ++j) {
			printer.OpenElement("link");
			printer.PushText(nodes[i].ids[j]);
			printer.CloseElement();
		}
		printer.CloseElement();
	}*/
	printer.CloseElement();
	doc.Parse(printer.CStr());
	doc.SaveFile(fname.c_str());
}

void Brain::tweak() {

}