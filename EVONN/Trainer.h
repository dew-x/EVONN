#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include <fstream>
#include "dirent.h"
#include "Brain.h"

enum train_t {
	CONSTANT,
	VARIABLE
};

struct FileData {
	std::string fname;
	double score;
};

class Trainer
{
private:
	std::string folder;
	train_t mode;
	unsigned storageSize;
	unsigned randomChances;
	std::vector<FileData> data;
public:
	Trainer(const char *folder, train_t mode, unsigned storageSize, unsigned randomChances);
	~Trainer();
	Brain* getRandom(const BrainSchema &schema);
	Brain* getBest();
	double getBestFitness();
	void add(Brain *brain, double score);
private:
	void readFolder();
	void indexFile(std::string fname, double score);
	void sortData();
	void sortDataBack(unsigned pos);
	void deleteFile(std::string fname);
	std::string mkFname(double score);
	bool fileExists(std::string fname);
};

