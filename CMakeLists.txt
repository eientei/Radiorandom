cmake_minimum_required(VERSION 2.8)

########################################################################

add_definitions(-pedantic -Wall -g)
set(CMAKE_BUILD_TYPE Debug)
include_directories(
	../
)

########################################################################

project(GenTemplates)
set (Templates_html
	../radiorandom/templates/master/generic.tmpl
	../radiorandom/templates/master/menu.tmpl
	../radiorandom/templates/master/master.tmpl
#
#	../src/Templates/Generic/Master.tmpl
#	../src/Templates/Generic/Setup.tmpl
#	../src/Templates/Generic/Error.tmpl	
#	../src/Templates/Generic/Index.tmpl
#	../src/Templates/Generic/Tos.tmpl
#	
#	../src/Templates/Users/Users.tmpl
#	../src/Templates/Users/UsersNew.tmpl
#	../src/Templates/Users/UsersShow.tmpl
#	../src/Templates/Users/UsersLogin.tmpl
#	../src/Templates/Users/UsersProfile.tmpl
#	../src/Templates/Users/UsersProfileEmail.tmpl
#	../src/Templates/Users/UsersProfilePassword.tmpl
#	../src/Templates/Users/UsersProfileSettings.tmpl
#	
#	../src/Templates/Posts/Posts.tmpl
)
add_custom_command(
	OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	COMMAND cppcms_tmpl_cc ${Templates_html} -o ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp
	DEPENDS ${Templates_html}
)
add_library(templates SHARED ${CMAKE_CURRENT_BINARY_DIR}/templates_html.cpp)
target_link_libraries(templates 
	-lcppcms
)

########################################################################

project(Data)
add_library(data STATIC
	../radiorandom/data/content/menu_set.cpp
	../radiorandom/data/content/user_set.cpp
)
#add_library(data-pstring STATIC 
#	../src/Data/PString/PString.cpp
#	../src/Data/PString/PlainIOHighLevel.cpp
#)
#add_library(data-menuset STATIC 
#	../src/Data/MenuSet/MenuSet.cpp
#)

#add_library(data-userset STATIC 
#	../src/Data/UserSet/UserSet.cpp
#)

#add_library(data-postset STATIC 
#	../src/Data/PostSet/PostSet.cpp
#)

########################################################################
project(Helpers)
add_library(helpers STATIC 
	../radiorandom/helpers/auth/auth.cpp
	../radiorandom/helpers/hash/hash.cpp
	../radiorandom/helpers/db/db.cpp
	../radiorandom/helpers/format/format.cpp
	../radiorandom/helpers/filesystem/filesystem.cpp
	../radiorandom/helpers/navigation/navigation.cpp
	#../radiorandom/helpers/auth/user_exist.cpp
	#../radiorandom/helpers/auth/session_exist.cpp

	#../radiorandom/helpers/db/tag_parser.cpp
	#../radiorandom/helpers/db/sqlfy_pattern.cpp
	#../radiorandom/helpers/db/sqlfy_pseudo.cpp
	
	#../radiorandom/helpers/format/uri_format.cpp
	#../radiorandom/helpers/format/file_size.cpp
	#../radiorandom/helpers/format/user_access.cpp
	#../radiorandom/helpers/format/time_passed.cpp
	
	#../radiorandom/helpers/filesystem/file_exist.cpp
	
	#../radiorandom/helpers/hash/sha1.cpp
	
	#../radiorandom/helpers/navigation/menu.cpp
	#../radiorandom/helpers/navigation/generator.cpp
)

#add_library(helper-db-tagsparser STATIC 
#	../src/Helpers/DB/TagsParser.cpp
#)

#add_library(helper-filesystem-fileexists STATIC 
#	../src/Helpers/FileSystem/FileExists.cpp
#)

#add_library(helper-navigation-menu STATIC 
#	../src/Helpers/Navigation/Menu.cpp
#)

#add_library(helper-navigation-navigationgenerator STATIC 
#	../src/Helpers/Navigation/NavigationGenerator.cpp
#)

#add_library(helper-auth-authuser STATIC 
	##../src/Helpers/Auth/AuthUser.cpp
#)

#add_library(helper-auth-validsession STATIC 
#	../src/Helpers/Auth/ValidSession.cpp
#)

#add_library(helper-auth-validuser STATIC 
#	../src/Helpers/Auth/ValidUser.cpp
#)

#add_library(helper-auth-makesession STATIC 
#	../src/Helpers/Auth/MakeSession.cpp
#)

#add_library(helper-format-filesize STATIC 
#	../src/Helpers/Format/FileSize.cpp
#)

#add_library(helper-format-useraccess STATIC 
#	../src/Helpers/Format/UserAccess.cpp
#)

#add_library(helper-format-passedtime STATIC 
#	../src/Helpers/Format/PassedTime.cpp
#)

#add_library(helper-hash-sha1 STATIC 
#	../src/Helpers/Hash/SHA1.cpp
#)

########################################################################
project(DB)
add_library(db STATIC 
	../radiorandom/db/db.cpp
)

########################################################################

project(PlainIO)
add_library(plainio STATIC 
	../radiorandom/plainio/plainio.cpp
)

########################################################################

project(Server)

set(server_lib
	helpers
	db
	data
	plainio

	-lcppcms
	-lcppdb
	-lmagic
	-lssl
	-lcrypto
	-luriparser
)

add_executable(radiorandom-server 
	../radiorandom/apps/server.cpp
	
#	../src/Apps/Generic/Index.cpp
#	../src/Apps/Generic/Setup.cpp
#	../src/Apps/Generic/Tos.cpp
	
#	../src/Apps/Users/Users.cpp
#	../src/Apps/Users/UsersNew.cpp
#	../src/Apps/Users/UsersShow.cpp
#	../src/Apps/Users/UsersLogin.cpp
#	../src/Apps/Users/UsersSearch.cpp
#	../src/Apps/Users/UsersLogout.cpp
#	../src/Apps/Users/UsersProfile.cpp
#	../src/Apps/Users/UsersProfilePassword.cpp
#	../src/Apps/Users/UsersProfileEmail.cpp
#	../src/Apps/Users/UsersProfileSettings.cpp
	
#	../src/Apps/Posts/Posts.cpp
#	../src/Apps/Posts/PostsNew.cpp
#	../src/Apps/Posts/PostsShowId.cpp
#	../src/Apps/Posts/PostsShowHash.cpp
#	../src/Apps/Posts/PostsShowTags.cpp
#	../src/Apps/Posts/PostsShowDate.cpp
#	../src/Apps/Posts/PostsVoteup.cpp
#	../src/Apps/Posts/PostsVotedown.cpp
)
target_link_libraries(radiorandom-server ${server_lib})
set_target_properties(radiorandom-server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "../")
