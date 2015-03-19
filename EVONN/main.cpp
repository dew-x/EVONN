#include "Trainer.h"

int main() {
	BrainSchema schema;
	schema.addConstant(Data((int)0));
	schema.addConstant(Data((int)1));
	schema.addConstant(Data((int)-1));
	for (int i = 0; i < 10; ++i) {
		schema.addInput(DT_INTEGER);
	}
	schema.addOutput(DT_INTEGER);
	Trainer t("train", CONSTANT, 200, 25);
	Brain b("test.xml");
	b.store("test2.xml");
}