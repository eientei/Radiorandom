#include "Interact.h"

void  Generic::DB::Interact::LoadSchema(std::string filepath) {
	Lock();
	std::fstream file;
	std::string s;
	file.open(filepath.c_str(), std::fstream::in);

	

	while(file.good()) {
		char buf[1024];
		file.getline(buf,sizeof(buf));
		s += buf;
		if ((*(s.end()-1)) == ';') {
			*this << s << Exec;
			s.clear();
		}
	}
	file.close();
	Unlock();
	//guard.commit();
	//Result posts_size = *this << "select sum(size) from posts";

}
