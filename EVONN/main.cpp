#include "Trainer.h"

int main() {
	BrainSchema schema;
	schema.addConstant(Data((int)0));
	schema.addConstant(Data((int)1));
	schema.addConstant(Data((int)-1));
	for (int i = 0; i < 10; ++i) {
		schema.addInput(DT_SIGNED);
	}
	schema.addOutput(DT_SIGNED);
	Trainer t("train", CONSTANT, 200, 25);
	Brain b(schema);
	b.store("test.xml");
	Brain b1("test.xml");
	b1.store("test2.xml");
	system("PAUSE");
}