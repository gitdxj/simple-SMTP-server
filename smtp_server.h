#ifndef SMTP_SERVER_H
#define SMTP_SERVER_H


#include <QtWidgets/QMainWindow>
#include "ui_smtp_server.h"
#include "tcpthread.h"
#include "getMail.h"

class SMTP_server : public QMainWindow, public Ui_SMTP_serverClass
{
	Q_OBJECT

public:
	tcpThread *thread;

	SMTP_server(QWidget *parent = 0);
	~SMTP_server();
public slots:
	void onCommunication(QString);
	void on_userList_item_clicked(QListWidgetItem *item);

private:
	//Ui::SMTP_serverClass ui;
	//QPixmap image;
protected:
	//void paintEvent(QPaintEvent *);
};

#endif // SMTP_SERVER_H
