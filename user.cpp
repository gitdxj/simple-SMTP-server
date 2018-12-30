#include "user.h"

using namespace std;

User::User()
{
}

User::User(string username, string password)
{
	this->username = username;
	this->password = password;
}

string User::get_username()
{
	return this->username;
}

string User::get_password()
{
	return this->password;
}

void UserList::add_user(string username, string password)
{
	User new_user(username, password);
	this->user_list.insert(user_list.begin(), new_user);
}

void UserList::add_user(User user)
{
	this->user_list.insert(user_list.begin(), user);
}

bool UserList::match(string username, string password)
{
	for(int i = 0; i < this->user_list.size(); i++)
		if(user_list[i].get_username() == username &&
			user_list[i].get_password() == password)
			return true;
	return false;
}