#include "func.h"
using namespace std;



int parseCommand(string commandString) {
	string theString(commandString);
	
	if (theString.substr(0, 4) == "HELO" || theString.substr(0, 4) == "helo") {
		return HELO;
	}
	else if(theString.substr(0, 4) == "EHLO")
		return EHLO;
	else if (theString == "AUTH LOGIN")
		return AUTH;
	else if (theString == "MAIL FROM") {
		return MAIL;
	}
	else if (theString == "RCPT TO") {
		return RCPT;
	}
	else if (theString == "DATA") {
		return DATA;
	}
	else if (theString == "RSET") {
		return RSET;
	}
	else if (theString == "NOOP") {
		return NOOP;
	}
	else if (theString == "QUIT") {
		return QUIT;
	}
	
}




string get_image_base64_code(string &mail_content)
{
	int picture_position = mail_content.find("Content-Disposition");
	int position1 = mail_content.find('"', picture_position);
	int position2 = mail_content.find('"', position1+1);
	int position3 = mail_content.find('\n', position2);
	string base64_code = mail_content.substr(position2 + 5, position3 - position2 - 4);
	mail_content = mail_content.substr(0, position2 + 3);
	return base64_code;
}


string get_subject(string mail_content)
{
	int position1 = mail_content.find("Subject:");
	int position2 = mail_content.find(" ", position1);
	int position3 = mail_content.find('\n', position2);
	string subject = mail_content.substr(position1 + 1, position3 - 1);
	return subject;
}


string readFile(string filename)
{
	std::ifstream t("mail.txt");
	std::string str((std::istreambuf_iterator<char>(t)),
					 std::istreambuf_iterator<char>());
	string base64_code = get_image_base64_code(str);
	return str;
}