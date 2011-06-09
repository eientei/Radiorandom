#include "Server.h"


void radio_random::posts() {
	radiorandom::posts c;
	set_menu(c,menu_item("[Playlist]","/posts"));
	set_submenu(c, "Posts", menu_item("[Index]","/posts"));
	c.many = false;
	std::multimap<std::string,std::string> getreq = request().get();
	
	std::string sortby = getreq.find("sortby")->second;
	std::string direction = getreq.find("direction")->second;
	std::string stroffset = getreq.find("page")->second;
	int offset = 0;
	sscanf(stroffset.c_str(),"%d",&offset);
	
	if (sortby != "score" && sortby != "size" && sortby != "filename" && sortby != "tags")
		sortby = "posted";
	if (direction != "asc")
		direction = "desc";
	
	
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result posts;
	int postslimit = settings().get<int>("limits.posts");
	posts = radiorandom_sql << "select count(*) from files	";
	posts.next();
	int postscount = posts.get<int>(0);
	int page = (offset - 1) * postslimit;
	if (page < 0) page = 0;
		c.prefix = "?sortby=" + sortby + "&amp;direction=" + direction;

	if (postscount > postslimit) {
		c.many = true;
		c.page = offset;
		c.total = postscount;
		c.pagesize = postslimit;
		char buf[1024];
		snprintf(buf,1024,"%d",page + 1);
		c.suffix="&page=" + std::string(buf);
	}
	posts = radiorandom_sql << "select * from files order by " + sortby + " " + direction + " limit ? offset ?" << postslimit << page;
	while (posts.next()) {
		std::string fn = posts.get<std::string>("filename");
		std::string hash = posts.get<std::string>("hash");
		std::string filepath = posts.get<std::string>("filepath");
		std::string tags = posts.get<std::string>("tags");
		int score = posts.get<int>("score");
		int size = posts.get<int>("size");
		int posted = posts.get<int>("posted");
		c.postsset.push_back(post_item(hash,fn,filepath,tags,score,size,posted));
	}
	
	
	if (sortby == "filename") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_filename_dir = direction;
	}
	if (sortby == "score") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_score_dir = direction;
	}
	if (sortby == "size") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_size_dir = direction;
	}
	if (sortby == "tags") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_tags_dir = direction;
	}
	if (sortby == "posted") {
		if (direction == "asc") direction = "desc";
		else direction = "asc";
		c.sort_posted_dir = direction;
	}
	
	render("html_posts",c);	
}

void radio_random::posts_new() {
	radiorandom::posts_new c;
	set_menu(c,menu_item("[Playlist]","/posts"));
	set_submenu(c, "Posts", menu_item("[Upload]","/posts/new"));
	if(request().request_method()=="POST") {
		c.load(context());
		cppcms::http::request::files_type fs = request().files();
		if (fs.size() < 1) {
			c.message = "No file.";
			render("html_posts_new",c);	
			return;
		}
		cppcms::http::file *file = fs[0].get();
		if (file->size() < 1024) {
			c.message = "File is too small";
			render("html_posts_new",c);	
			return;
		}
		std::string path = settings().get<std::string>("paths.temp") + "/tmpfile";
		file->save_to(path);
		const char *magic_full;
		magic_t magic_cookie;
		magic_cookie = magic_open(MAGIC_MIME);
		magic_load(magic_cookie, NULL);
		magic_full = magic_file(magic_cookie, path.c_str());
		std::string mime(magic_full);
		magic_close(magic_cookie);
		if (
			   mime.find("audio/mpeg") != 0
			&& mime.find("application/ogg") != 0
			&& mime.find("audio/x-wav") != 0
			&& mime.find("audio/x-flac") != 0
			&& mime.find("audio/x-mod") != 0
			&& mime.find("audio/mp4") != 0
		)  {
			printf("deleting %s\n",mime.c_str());
			remove(path.c_str());
			c.message = "File " + mime + " were not recognized as an audio file.";
			render("html_posts_new",c);
			return;
		}
		
		std::string suffix = "";
		
		std::string hash = sha1hash_file(path);

		cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
		cppdb::result files = radiorandom_sql << "select count(*) from files where hash = ?" << hash;
		files.next();
		if (files.get<int>(0)) {
			files.next();
			cppdb::result files = radiorandom_sql << "select * from files where hash = ?" << hash;
			files.next();
			c.exists = true;
			c.exists_filename = files.get<std::string>("filename");
			c.exists_filepath = "/posts/" + files.get<std::string>("hash");
			c.exists_size = files.get<int>("size");
			c.exists_score = files.get<int>("score");
			c.exists_tags = files.get<std::string>("tags");
			c.exists_posted = files.get<int>("posted");
			remove(path.c_str());
			c.message = "Such file already exists.";
			render("html_posts_new",c);
			return;
		}
		
		struct stat filestatus;
		stat(path.c_str(),&filestatus);
		
		if (mime.find("audio/mpeg") == 0) {
			suffix = "mp3";
		} else if (mime.find("application/ogg") == 0) {
			suffix = "ogg";
		} else if (mime.find("audio/x-wav") == 0) {
			suffix = "wav";
		} else if (mime.find("audio/x-flac") == 0) {
			suffix = "flac";
		} else if (mime.find("audio/mp4") == 0) {
			suffix = "aac";
		}
		
		time_t rawtime;
		struct tm * timeinfo;
		char timebuf[1024];
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strftime(timebuf,1024,"%F",timeinfo);
		
		std::string dirpath = settings().get<std::string>("paths.data") + "/" + timebuf;
		mkdir(dirpath.c_str(),0755);
		
		std::string newpath = dirpath + "/" + hash + "." + suffix;
		std::string webpath = std::string("/data/") + timebuf + "/" + hash + "." + suffix;
		
		rename(path.c_str(),newpath.c_str());
		printf("%s\n",newpath.c_str());
		
		radiorandom_sql << "insert into files values (NULL,?,?,?,?,0,?,strftime('%s','now'))" << file->filename() << webpath << hash << filestatus.st_size << c.tags.value() << cppdb::exec;
		
		c.thanks = "Thatk you for uploading!";
	}
	render("html_posts_new",c);	
}

void radio_random::posts_show(std::string id) {
	
}
