#include "tcpthread.h"
#include <direct.h>
using namespace std;

tcpThread::tcpThread(QObject *parent)
	: QThread(parent)
{
	user_list = new UserList();
	User xiaoming("xiaoming", "123456");
	User xiaohong("xiaohong", "123456");
	user_list->add_user(xiaoming);
	user_list->add_user(xiaohong);
}

tcpThread::~tcpThread()
{

}

int tcpThread::readCommand(int sockfd, string &Command) {
	char* buffer = new char[20240];

	memset(buffer, 0, 20240);
	int iResult;
	iResult = recv(sockfd, buffer, 20240, 0);

	if('\n' == buffer[strlen(buffer) - 1])
    		buffer[strlen(buffer) - 2] = '\0';
	Command = buffer;

	QString QCommand = QString::fromStdString(Command);
	emit Communication(QCommand+'\n');

	return iResult;
}

//command to write to a socket
void tcpThread::writeCommand(int sockfd, string message) {
	int size = message.length();
	send(sockfd, message.c_str(), size, 0); //c_str returns const char*

	//show on the console
	QString QMessage = QString::fromStdString(message);
	emit Communication(QMessage+'\n');

	return;
}

void tcpThread::processConnection(SOCKET &arg)
{
	
	// *******************************************************
	// * This is a little bit of a cheat, but if you end up
	// * with a FD of more than 64 bits you are in trouble
	// *******************************************************

	//int sockfd = *(int *)arg;
	int sockfd = arg;

	int connectionActive = 1;
	//int seenMAIL = 0;
	//int seenRCPT = 0;
	//int seenDATA = 0;
	//int seenUser = 0;
	//int seenPassword = 0;

	int seenMAIL = 1;
	int seenRCPT = 1;
	int seenDATA = 1;
	int seenUser = 1;
	int seenPassword = 1;
	int seenAUTH = 0;
	
	//strings used to store MAIL FROM, RCPT TO, username, host, and input values throughout the commands
	string forwardPath = "";
	string reversePath = "";
	string cmdString = "";
	string getString = "";
	string parameter = "";
	string messageBuffer = "";
	string username = "";
	string hostname = "";
	string sendername = "";
	int findAtSymbol = 0;
	
	//used for displaying time in localhost messages
	
	string dataRead = "";
	ofstream ofs;
	
	writeCommand(sockfd, "220 Ready\r\n");
	

	int iResult;
	do {

		// *******************************************************
		// * Read the command from the socket.
		// *******************************************************
		iResult = readCommand(sockfd, getString);

		//show on the console
		//cout<<"C: "<<getString<<endl;
		int findColon = getString.find(":");
		
		cmdString = getString.substr(0, findColon);
		parameter = getString.substr(findColon + 1, getString.length() - findColon);

		
		// *******************************************************
		// * Parse the command.
		// *******************************************************
		int command = parseCommand(cmdString);

		// *******************************************************
		// * Act on each of the commands we need to implement. 
		// *******************************************************
		switch (command) {
		case HELO :
			writeCommand(sockfd, "250 Dong's smtp server Hello\r\n");
			break;
		case EHLO:
			writeCommand(sockfd, "250 Dong's smtp server Hello\r\n");
			break;
		case AUTH:
			{
				string username, password;//username == "eGlhb21pbmc=" password == "MTIzNDU2"
				writeCommand(sockfd, "334 dXNlcm5hbWU6\r\n");
				iResult = readCommand(sockfd, username);
				writeCommand(sockfd, "334 UGFzc3dvcmQ6\r\n");
				iResult = readCommand(sockfd, password);
				string decoded_name, decoded_pass;
				decoded_name = std_base64_decode(username);
				decoded_pass = std_base64_decode(password);
				if(user_list->match(decoded_name, decoded_pass))
				{
					writeCommand(sockfd, "235 Authentication successful\r\n");
					sendername = decoded_name;
					seenAUTH = 1;

				}
				else
					closesocket(sockfd);
			
				break;
			}
		case MAIL :
			//if(!seenAUTH)
			//{
			//	writeCommand(sockfd, "553 authentication is required\r\n");
			//	break;
			//}

			seenMAIL = 1;
			seenRCPT = 0;
			seenDATA = 0;
		
			forwardPath = "";
			reversePath = parameter;
			messageBuffer = "";
			
			writeCommand(sockfd, "250 OK\r\n");
			break;
		case RCPT :
			if(seenMAIL){
			
				seenRCPT = 1;
				forwardPath = parameter.substr(1, parameter.length() - 2);
			
				writeCommand(sockfd, "250 OK\r\n");
			}
			else{
				writeCommand(sockfd, "503 Need MAIL FROM command\r\n");
			}
			
			break;
		case DATA :
			if(seenMAIL && seenRCPT)
			{
				messageBuffer = "";
			
				writeCommand(sockfd, "354 Send message content; end with <CRLF>.<CRLF>\r\n");
				iResult = readCommand(sockfd, dataRead);
				while(dataRead[dataRead.length()-1] != '.')
				{
					messageBuffer.append(dataRead);
					iResult = readCommand(sockfd, dataRead);
				}
			
			

				if(dataRead[dataRead.length()-1] == '.')
					messageBuffer.append(dataRead);
				
				//removes the last new line from the message
				messageBuffer = messageBuffer.substr(0, messageBuffer.length() - 1); //remove the '.'
				
				int findAngle = reversePath.find('<');
				findAtSymbol = reversePath.find("@");
				string sendername = reversePath.substr(findAngle + 1, findAtSymbol - 1 - findAngle);

				string mailName = "mail.txt";
				string mailPath;
				mailPath = DEFAULT_MAIL_PATH + "\\" + sendername;
				mailName = mailPath + "\\" + mailName;

				emit Communication(QString::fromStdString(mailPath+'\n'));
				//get the base64 code of the picture
				string base64_code = get_image_base64_code(messageBuffer);

				//wirte base64 code into image.txt and convert it into picture
				string pic_txt = mailPath + "\\" + "image.txt";

				ofstream fimage(pic_txt);
				fimage << base64_code;
				fimage.close();
				outputImage(mailPath);
				
				ofs.open(mailName, ios::out);
				ofs << "From " + reversePath << endl;
				ofs << messageBuffer << "\n";
				ofs.close();
				writeCommand(sockfd, "250 OK\r\n");
				//writeCommand(sockfd, "221 Bye\r\n");
				seenDATA = 1;
				//return;
				break;
			}
			else 
			{
				writeCommand(sockfd, "Must specify RCPT TO and MAIL FROM first\n");
				break;
			}

		case RSET :
			seenMAIL = 0;
			seenRCPT = 0;
			seenDATA = 0;
			forwardPath = "";
			reversePath = "";
			messageBuffer = "";
			
			writeCommand(sockfd, "250 OK\r\n");
			break;
		case NOOP :
			break;
		case QUIT :
			writeCommand(sockfd, "221 Connection closing\r\n");
			shutdown(sockfd, SD_SEND);
			closesocket(sockfd);
			break;
		default :

			//cout << "Unknown command (" << cmdString << ")" << endl;
			writeCommand(sockfd, "500 Unkown command(" + cmdString + ")\r\n");
		}
	} while (iResult>0);
	arg = INVALID_SOCKET;
}

void tcpThread::run()
{


	WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);

    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
    }
	while(1)
	{
    // Accept a client socket
		std::cout<<"Waiting for connection\n";
		while(ClientSocket == INVALID_SOCKET || ClientSocket == SOCKET_ERROR)
			ClientSocket = accept(ListenSocket, NULL, NULL);

		processConnection(ClientSocket);
	}
}
