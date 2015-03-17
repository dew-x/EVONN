#include "Trainer.h"

int main() {
	BrainSchema shema;
	shema.addConstant(Data(0));
	shema.addConstant(Data(1));
	shema.addConstant(Data(-1));
	for (int i = 0; i < 10; ++i) {
		shema.addInput(DT_INTEGER);
	}
	shema.addOutput(DT_INTEGER);
	Trainer t("train", CONSTANT, 200, 25);
}