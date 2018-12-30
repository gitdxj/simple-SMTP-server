#ifndef USER
#define USER
#include <string>
#include <vector>

class User
{
private:
	std::string username;
	std::string password;
public:
	User();
	User(std::string username, std::string password);
	std::string get_username();
	std::string get_password();
};

class UserList
{
private:
	std::vector<User> user_list;
public:
	UserList(){}
	bool match(std::string username, std::string password);
	void add_user(std::string username, std::string password);
	void add_user(User user);
};


#endif