#include "smtp_server.h"

using namespace std;

SMTP_server::SMTP_server(QWidget *parent)
	: QMainWindow(parent)
{
	this->setupUi(this);
	
	vector<string> user;
	getJustCurrentDir(DEFAULT_MAIL_PATH ,  user);
	for(int i = 0; i<user.size(); i++)
	{
		QListWidgetItem *item = new QListWidgetItem;
		item->setText(QString::fromStdString(user[i]));
		this->userList->addItem(item);
	}
	connect(this->userList, &QListWidget::itemClicked, this, &SMTP_server::on_userList_item_clicked);


	thread = new tcpThread(this);
	connect(thread, &tcpThread::Communication, this, &SMTP_server::onCommunication);
}

SMTP_server::~SMTP_server()
{

}

void SMTP_server::onCommunication(QString QMessage)
{
	this->messageBrowser->insertPlainText(QMessage);
}

void SMTP_server::on_userList_item_clicked(QListWidgetItem *item)
{
	this->contentBrowser->clear();
	// C:/mail/user/mails/mail.txt
	QString QUserName = item->text();
	//text() == "user/mail"
	string username = QUserName.toStdString();
	string path = DEFAULT_MAIL_PATH + "\\" +  username + "\\";
	string mailname = path + "mail.txt";
	ifstream infile(mailname);
	string temp;
	while(getline(infile, temp))
	{
		temp = temp + '\n';
		QString QTemp = QString::fromStdString(temp);
		this->contentBrowser->insertPlainText(QTemp);
	}
	infile.close();

	QString picname = QString::fromStdString(path) + "image.png";
	
	//QImage *image = new QImage;
	//image->load(QString::fromStdString(picname));
	
	QImage image;
	//image.load(picname);
	if(!image.load(picname))
		this->messageBrowser->insertPlainText("failure");
	this->pic_label->setPixmap(QPixmap::fromImage(image));
	this->pic_label->resize(QSize(image.width(),image.height()));
	this->pic_label->show();
	//this->pic_label->setPixmap(QPixmap::fromImage(*image));
	//this->pic_label->resize(QSize(image->width(), image->height()));
	//this->pic_label->show();
	
	//QString fileName = QFileDialog::getOpenFileName(this,"Choose Image","x:/image",("Image File(*.*)")) ;
 //   QImage image ;
 //   image.load(fileName) ;

 //   label = new QLabel();
 //   label->setPixmap(QPixmap::fromImage(image));
 //   label->resize(QSize(image.width(),image.height()));
 //   ui->scrollImag->setWidget(label);

}

