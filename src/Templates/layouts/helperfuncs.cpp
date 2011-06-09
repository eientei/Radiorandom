#include "helperfuncs.h"

std::string make_session(std::string username) {
	time_t rawtime;
	struct tm * timeinfo;
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select id from users where username = ?;" << username;
	
	int id;
	while (users.next()) {
		id = users.get<int>("id");
	}
	users.clear();
	char buf[1024];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buf,1024,"%c",timeinfo);
	std::string hash = sha1hash(buf);
	printf("ok\n");
	radiorandom_sql << "insert into sessions values (?,?,strftime('%s','now'));" << hash << id << cppdb::exec;
	return hash;
}

std::string navgen_helper(int begin, int end, int page, int pagesize, std::string prefix, int pn=1) {
	std::string result = "";
	std::string c_class,href;
	char buf[1024];
	
	for (int i=begin; i < end; i+=pagesize) {
		snprintf(buf,1024,"%d",pn);
		if (pn == page) {
			c_class="current";
			href="";
		} else {
			c_class = "rest";
			href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
		}
		result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
		pn++;
	}
	return result;
}

std::string navigation_generator(std::string prefix, int page, int pagesize,int total) {
	std::string result = "";
		int total_pages = total/pagesize;
		if (total%pagesize > 0) total_pages += 1;
		char buf[1024];
		std::string c_class="rest";
		std::string href="";
		if (page == 1) {
			result += "<a class=\"prev\">&lt;&lt;</a>";
		} else {
			snprintf(buf,1024,"%d",page-1);
			result += "<a class=\"prev-active\" href=\"" + prefix + "&amp;page=" + std::string(buf) + "\">&lt;&lt;</a>";
		}
		if (total_pages < 8) {
			result += navgen_helper(0,total,page,pagesize,prefix);
		} else {
			if (page > 5) {
				result += "<a class=\"rest\" href=\"" + prefix + "&amp;page=1\">1</a>";
				result += "...";
			}
			
			if (page < 6) {
				result += navgen_helper(0,(5+(page>=5&&2)+(page>5)+((page>=3) && abs(3-page)))*pagesize,page,pagesize,prefix);
			}
			
			if ((page >= 6) && (((total_pages - page) >= 5))) {
				result += navgen_helper((page-2)*pagesize,(page+3)*pagesize,page,pagesize,prefix,(page-2));
			}
			
			
			if ((total_pages - page) < 3) {
				result += navgen_helper(total-(5)*pagesize,total,page,pagesize,prefix,(total_pages - 4));
			} else if ((total_pages - page) < 4) {
				result += navgen_helper(total-(6)*pagesize,total,page,pagesize,prefix,(total_pages - 5));
			} else if ((total_pages - page) < 5) {
				result += navgen_helper(total-(7)*pagesize,total,page,pagesize,prefix,(total_pages - 6));
			}

			if ((total_pages - page) > 4) {
				snprintf(buf,1024,"%d",total_pages);
				result += "...";
				result += "<a class=\"rest\" href=\"" + prefix + "&amp;page=" + buf + "\">" + buf + "</a>";
			}
		}
		if (page == total_pages) {
			result += "<a class=\"next\">&gt;&gt;</a>";
		} else {
			snprintf(buf,1024,"%d",page+1);
			result += "<a class=\"next-active\" href=\"" + prefix + "&amp;page=" + std::string(buf) + "\">&gt;&gt;</a>";
		}
	/*
		std::string result = "";

		if (total_pages <= 7) {
			for (int i=0; i < total; i+=pagesize) {
				snprintf(buf,1024,"%d",pn);
				if (pn == page) {
					c_class="current";
					href="";
				} else {
					c_class = "rest";
					href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
				}
				result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
				pn++;
			}
		} else {
				if (page <= 5) {
					int lim = 5;
					if (page >= 4) {
						lim += (page-3);
					}
					for (int i=0; i < lim * pagesize; i+=pagesize) {
					snprintf(buf,1024,"%d",pn);
					if (pn == page) {
						c_class="current";
						href="";
					} else {
						c_class = "rest";
						href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
					}
					result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
					pn++;
				}
			} else if ((total_pages - page) > 3) {
				pn = page-2;
				for (int i=(page-2)*pagesize; i < (page+3)*pagesize; i+=pagesize) {
					snprintf(buf,1024,"%d",pn);
					if (pn == page) {
						c_class="current";
						href="";
					} else {
						c_class = "rest";
						href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
					}
					result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
					pn++;
				}
			}
				if ((total_pages - page) > 3) {
					result += "...";
					c_class = "rest";
					if (page == total_pages) c_class = "current";
					snprintf(buf,1024,"%d",total_pages);
					href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
					result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
				} else {
					int diff = 6;
					pn = page-diff+(total_pages - page);
					for (int i=(page-diff+(total_pages - page))*pagesize; i <= total; i+=pagesize) {
						snprintf(buf,1024,"%d",pn);
						if (pn == page) {
							c_class="current";
							href="";
						} else {
							c_class = "rest";
							href = " href=\"" + prefix + "&amp;page=" + buf + "\"";
						}
						result += "<a class=\"" + c_class + "\"" + href + ">" + std::string(buf) + "</a>";
						pn++;
					}
				}
		}

		*/
		return result;
}

std::string format_size(size_t size) {
	char buf[1024];
	float fsize = size;
	std::string suffix("B");
	if (size / 1024 > 0) {
		suffix = "KB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "MB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "GB";
		size /= 1024;
		fsize /= 1024;
	}
	if (size / 1024 > 0) {
		suffix = "TB";
		size /= 1024;
		fsize /= 1024;
	}
	snprintf(buf,1024,"%.2f",fsize);
	
	return buf + std::string(" ") + suffix;
}

std::string format_time(size_t t) {
	char buf[1024];
	std::string suffix = "seconds";
	int current_time = time(NULL);
	int diff = (current_time - t);
	if (diff > 60) {
		diff /= 60;
		suffix = "minutes";
		if (diff == 1) suffix = "minute";
		if (diff > 60) {
			diff /= 60;
			suffix = "hours";
			if (diff == 1) suffix = "hour";
			if (diff > 24) {
				diff /= 24;
				suffix = "days";
				if (diff == 1) suffix = "day";
				if (diff > 30) {
					diff /= 30;
					suffix = "months";
					if (diff == 1) suffix = "month";
					if (diff > 12) {
						diff /= 12;
						suffix = "years";
						if (diff == 1) suffix = "year";
					}
				}
			}
		}
	}
	snprintf(buf,1024,"%d",diff);
	return buf + std::string(" ") + suffix + " ago";
}

std::string sha1hash(std::string buf, size_t length) {

	unsigned char outbuf[20];
	unsigned char hash_literal[128];
	SHA1((unsigned char*)buf.c_str(),length,outbuf);
	unsigned char *p=hash_literal;
	for (int i=0; i < 20; i++, p+=2) {
		snprintf((char *)p,3,"%02x",outbuf[i]);
	}
	
	return std::string((char *)hash_literal);
}

std::string sha1hash_file(std::string path) {
		FILE *f;
		unsigned char buf[8192];
		unsigned char out[32];
		char hash[128];
		SHA_CTX sc;
		f = fopen(path.c_str(),"r");
		SHA1_Init(&sc);
		for (;;) {
			size_t len;
			len = fread(buf,1,sizeof buf,f);
			if (len == 0) break;
			SHA1_Update(&sc,buf,len);
		}
		fclose(f);
		SHA1_Final(out,&sc);
		char *p = hash;
		for (int i=0; i < 20; i++, p+=2) {
			snprintf(p,3,"%02x",out[i]);
		}
		return std::string(hash);
}


bool valid_user(std::string username, std::string password_hash, bool raw) {
	std::string hash;
	if (raw) {
		hash = sha1hash(password_hash.c_str());
	} else {
		hash = password_hash;
	}
	cppdb::session radiorandom_sql("sqlite3:db=db/radiorandom.db");
	cppdb::result users = radiorandom_sql << "select count(*) from users where username = ? and password_hash = ?" << username << password_hash;
	users.next();
	return users.get<int>(0) == 1;
}
