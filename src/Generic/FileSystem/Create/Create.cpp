#include "Create.h"


void Generic::FileSystem::Create::CreateFile(std::string fpath) {
	FILE *fp = fopen(filepath.c_str(),"w");
	fclose(fp);
}
