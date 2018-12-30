#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include "func.h"

#pragma comment (lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "25"


class tcpThread : public QThread
{
	Q_OBJECT

public:
	tcpThread(QObject *parent);
	~tcpThread();
	void run();

	int readCommand(int sockfd, std::string &Command);
	void writeCommand(int sockfd, std::string message);
	void processConnection(SOCKET &arg);
signals:
	void Communication(QString);

private:
	UserList *user_list;
	
};

#endif // TCPTHREAD_H
