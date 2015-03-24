#include "Trainer.h"
#include <vector>
#include "Brain.h"
#include "data.h"

int main() {
	BrainSchema schema;
	schema.addConstant(Data((int)0));
	//schema.addConstant(Data((int)1));
	//schema.addConstant(Data((int)-1));
	for (int i = 0; i < 2; ++i) {
		schema.addInput(DT_SIGNED);
	}
	schema.addOutput(DT_SIGNED);
	Trainer t("train", CONSTANT, 200, 25);
	Brain b(schema);
	std::vector<Data> input(2) , output(0);
	for (unsigned i = 0; i < 2; ++i) {
		input[i] = Data(int(-1*i));
		input[i].print();
	}
	try {
		b.eval(input, output);
	}
	catch (const std::invalid_argument& e) {
		std::cout << "ERROR " << e.what() << std::endl;
	}
	for (unsigned i = 0; i < output.size(); ++i) {
		output[i].print();
	}
	b.store("test.xml");
	Brain b1("test.xml");
	b1.store("test2.xml");
	system("PAUSE");
}