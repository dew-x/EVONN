#include "Trainer.h"


Trainer::Trainer(const char *folder, train_t mode, unsigned storageSize, unsigned randomChances)
{
	this->folder = std::string(folder);
	this->mode = mode;
	this->storageSize = storageSize;
	this->randomChances = randomChances;
	data = std::vector<FileData>(0);
	readFolder();
}


Trainer::~Trainer()
{
	data.clear();
}

Brain* Trainer::getRandom(const BrainSchema &schema) {
	unsigned random = rand()%100;
	Brain *ret = NULL;
	if (random < randomChances || data.size()==0) {
		ret = new Brain(schema);
	} else {
		unsigned mod = (data.size() * (data.size() + 1)) / 2;
		random = rand() % mod;
		unsigned size = data.size();
		unsigned id = 0;
		while (random>size && size>0) {
			random -= size;
			--size;
			++id;
		}
		ret = new Brain(folder + "/" + data[id].fname);
		ret->tweak();
		if (mode == VARIABLE) {
			data[id].score /= 2;
			sortDataBack(id);
		}
	}
	return ret;
}

Brain* Trainer::getBest() {
	Brain *ret = NULL;
	if (data.size()>0) {
		ret = new Brain(folder+"/"+data[0].fname);
	}
	return ret;
}

double Trainer::getBestFitness() {
	if (data.size() > 0) return data[0].score;
	else return 0.0;
}

void Trainer::add(Brain *brain, double score) {
	if (score > data[data.size() - 1].score) {
		std::string fname = mkFname(score);
		if (!fileExists(fname)) {
			brain->store(folder + "/" + fname);
			indexFile(fname, score);
		}
	}
}

void Trainer::readFolder() {
	DIR *pdir = NULL;
	struct dirent *pent = NULL;
	pdir = opendir(folder.c_str());
	if (pdir != NULL) {
		while (pent = readdir(pdir)) // while there is still something in the directory to list
		{
			if (pent == NULL) // if pent has not been initialised correctly
			{
				std::cerr << "Directory read failed" << std::endl;
				break;
			}
			std::string fname = std::string(pent->d_name);
			if (fname != "." && fname != "..") {
				double value = atof(fname.substr(0, fname.length() - 4).c_str());
				indexFile(fname, value);
			}
		}
		closedir(pdir);
	}
}

void Trainer::indexFile(std::string fname, double score) {
	if (data.size() < storageSize) {
		FileData tmp = { fname, score };
		data.push_back(tmp);
		sortData();
	}
	else {
		if (score>data[data.size() - 1].score) {
			deleteFile(data[data.size() - 1].fname);
			data[data.size() - 1].score = score;
			data[data.size() - 1].fname = fname;
			sortData();
		}
		else {
			deleteFile(fname);
		}
	}
}

void Trainer::sortData() {
	unsigned last = data.size() - 1;
	while (last > 0 && data[last].score>data[last-1].score) {
		std::swap(data[last], data[last - 1]);
		--last;
	}
}

void Trainer::sortDataBack(unsigned pos) {
	while (pos < data.size()-1 && data[pos].score<data[pos + 1].score) {
		std::swap(data[pos], data[pos + 1]);
		++pos;
	}
}

void Trainer::deleteFile(std::string fname) {
	remove((folder+"/"+fname).c_str());
}

std::string Trainer::mkFname(double score) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(15) << score << ".xml";
	return out.str();
}

bool Trainer::fileExists(std::string fname) {
	std::ifstream infile((folder+"/"+fname).c_str());
	return infile.good();
}