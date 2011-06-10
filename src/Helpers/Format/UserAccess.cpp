#include <Helpers/Format/UserAccess.h>

/// @file

string format_access(int level) {
	switch (level) {
		case -9999:
			return "Enemy of all";
		case -3:
			return "Banned";
		case -2:
			return "Restricted";
		case -1:
			return "Unholy nomad";
		case 0:
			return "Anonymous";
		case 1:
			return "Member";
		case 2:
			return "Advanced member";
		case 3: 
			return "Paid member";
		case 9999:
			return "Xaar";
	}
}
