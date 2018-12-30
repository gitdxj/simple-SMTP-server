#include "smtp_server.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	SMTP_server w;
	w.show();
	w.thread->start();
	return a.exec();
}
