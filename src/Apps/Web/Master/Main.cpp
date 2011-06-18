#include "../Web.h"

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void Web::main(std::string url) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	long mtime, seconds, useconds;
	
	
	std::string lock = GetFromConfig<std::string>("setup.lockfile");
	if (!Generic::FileSystem::Check(lock).ExistFile()) {
		if (url != "/setup"){
			response().set_redirect_header("/setup");
			return;
		}
	}
	if (!dispatcher().dispatch(url)) {
		MakeError("html",404,"Url " + url + " was not found");
	}
	gettimeofday(&end, NULL);
	
	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;
	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	printf("Elapsed time: %ld milliseconds\n", mtime);
}
