#include <Helpers/Format/PassedTime.h>

string passed_time(int t) {
	char buf[1024];
	string suffix = "seconds";
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
	return buf + string(" ") + suffix + " ago";
}
