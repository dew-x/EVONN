#include "Brain.h"


Brain::Brain(std::string fname)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(fname.c_str());
	// first element
	tinyxml2::XMLNode *rootnode = doc.FirstChild();
	rootnode->FirstChildElement("input")->QueryUnsignedText((unsigned*)&inputSize);
	rootnode->FirstChildElement("constant")->QueryUnsignedText((unsigned*)&constantSize);
	rootnode->FirstChildElement("variable")->QueryUnsignedText((unsigned*)&variableSize);
	rootnode->FirstChildElement("hidden")->QueryUnsignedText((unsigned*)&hiddenSize);
	rootnode->FirstChildElement("output")->QueryUnsignedText((unsigned*)&outputSize);
	values = std::vector<Data>(inputSize + constantSize + variableSize + hiddenSize + outputSize);
	neurons = std::vector<Neuron>(hiddenSize + outputSize);
	tinyxml2::XMLNode *dataListNode = rootnode->FirstChildElement("dataList");
	tinyxml2::XMLNode *dataNode = dataListNode->FirstChildElement("data");
	for (unsigned i = 0; i < inputSize + constantSize + variableSize + hiddenSize + outputSize; ++i) {
		dataNode->FirstChildElement("type")->QueryUnsignedText((unsigned*)&values[i].dt);
		std::string value=dataNode->FirstChildElement("value")->GetText();
		values[i].parseHexStr(value);
		dataNode = dataNode->NextSibling();
	}
	tinyxml2::XMLNode *neuronsNode = rootnode->FirstChildElement("neurons");
	tinyxml2::XMLNode *neuronNode = neuronsNode->FirstChildElement("neuron");
	for (unsigned i = 0; i < hiddenSize + outputSize; ++i) {
		unsigned id;
		neuronNode->FirstChildElement("id")->QueryUnsignedText(&id);
		std::vector<unsigned> links(0);
		tinyxml2::XMLNode *linksNode = neuronNode->FirstChildElement("links");
		tinyxml2::XMLNode *linkNode = linksNode->FirstChildElement("link");
		while (linkNode!=0) {
			unsigned link;
			linkNode->ToElement()->QueryUnsignedText(&link);
			links.push_back(link);
			linkNode = linkNode->NextSibling();
		}
		neurons[i] = Neuron(id, links);
		neuronNode = neuronNode->NextSibling();
	}
}

Brain::Brain(const BrainSchema &schema)
{
	inputSize = schema.input.size();
	outputSize = schema.output.size();
	constantSize = schema.constants.size();
	variableSize = schema.variables.size();
	hiddenSize = (rand() % (inputSize + outputSize + hiddenSize + variableSize)) + 1;
	values = std::vector<Data>(inputSize + constantSize + variableSize + hiddenSize + outputSize);
	neurons = std::vector<Neuron> (hiddenSize + outputSize);
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
	for (unsigned i = 0; i < hiddenSize; ++i) {
		try {
			neurons[i] = Neuron(values, i + inputSize + constantSize + variableSize, DT_UNDEFINED);
		}
		catch (int e) {
			std::cout << "ERROR: " << e << std::endl;
		}
		values[i + inputSize + constantSize + variableSize].dt = neurons[i].getOutput();
	}
	for (unsigned i = hiddenSize; i < outputSize + hiddenSize; ++i) {
		try {
			neurons[i] = Neuron(values, i + inputSize + constantSize + variableSize, values[i].dt);
		}
		catch (int e) {
			std::cout << "ERROR: " << e << std::endl;
		}
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
		printer.CloseElement();//type
		printer.OpenElement("value");
		printer.PushText(values[i].hexStr().c_str(),false);
		printer.CloseElement();//value
		printer.CloseElement();//data
	}
	printer.CloseElement();//dataList
	printer.OpenElement("neurons");
	for (unsigned i = 0; i < hiddenSize + outputSize; ++i) {
		printer.OpenElement("neuron");
		printer.OpenElement("id");
		printer.PushText(neurons[i].getId());
		printer.CloseElement();
		printer.OpenElement("links");
		std::vector<unsigned> links = neurons[i].getLinks();
		for (unsigned j = 0; j < links.size(); ++j) {
			printer.OpenElement("link");
			printer.PushText(links[j]);
			printer.CloseElement(); // id
		}
		printer.CloseElement();//links
		printer.CloseElement();//neuron
	}
	printer.CloseElement();//neurons
	printer.CloseElement();//brain
	doc.Parse(printer.CStr());
	doc.SaveFile(fname.c_str());
}

void Brain::tweak() {

}

void Brain::eval(const std::vector<Data> &input, std::vector<Data> &output) {
	// prepare input
	for (unsigned i = 0; i < inputSize; ++i) {
		if (values[i].dt == input[i].dt) {
			values[i].u = input[i].u;
		}
		else {
			throw std::invalid_argument("BAD INPUT");
		}
	}
	// run neurons
	for (unsigned i = 0; i < hiddenSize + outputSize; ++i) {
		Data value=neurons[i].eval(values);
		std::cout << i <<" ";
		value.print();
		values[inputSize + constantSize + variableSize + i] = value;
	}
	// copy output
	output = std::vector<Data>(outputSize);
	for (unsigned i = 0; i < outputSize; ++i) {
		output[i] = values[i + inputSize + constantSize + variableSize + hiddenSize];
	}
}