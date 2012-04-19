#include "../Web.h"

Web::Web(cppcms::service &srv) :
	cppcms::application(srv)	
{
	default_skin = GetFromConfig<std::string>("views.default_skin");
	
	dispatcher().assign("/(|/|index\\.)(|html|xml|json)",&Web::Index,this,2);
	dispatcher().assign("/setup(|/|\\.)(|html|xml|json)",&Web::Setup,this,2);
	dispatcher().assign("/tos(|/|\\.)(|html|xml|json)",&Web::TOS,this,2);
	
	dispatcher().assign("/users(|/|/index\\.|\\.)(|html|xml|json)($|\\?.*)",&Web::Users,this,2,99);
	dispatcher().assign("/users/(|/|show/)([0-9]*)($|\\.)($|html|xml|json)",&Web::UsersShow,this,2,4);
	dispatcher().assign("/users/(|index.(html|xml|json)/)([~-]*(id|access|name|joined|score):.*)",&Web::UsersSearch,this,2,3);
	dispatcher().assign("/users/new(|/|\\.)(|html|xml|json)",&Web::UsersNew,this,2);
	dispatcher().assign("/users/logout(|/|\\.)(|html|xml|json)",&Web::UsersLogout,this,2);
	dispatcher().assign("/users/login(|/|\\.)(|html|xml|json)",&Web::UsersLogin,this,2);
	dispatcher().assign("/users/profile(|/|\\.)(|html|xml|json)",&Web::UsersProfile,this,2);
	dispatcher().assign("/users/profile/password(|/|\\.)(|html|xml|json)",&Web::UsersProfilePassword,this,2);
	dispatcher().assign("/users/profile/email(|/|\\.)(|html|xml|json)",&Web::UsersProfileEmail,this,2);
	dispatcher().assign("/users/profile/settings(|/|\\.)(|html|xml|json)",&Web::UsersProfileSettings,this,2);
}

