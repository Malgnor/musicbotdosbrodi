#include "dialog.h"
#include <QtCore\qsettings.h>
#include "global.h"

Dialog::Dialog()
{
}

void Dialog::SetupUi(){
	setupUi(this);
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	lineEdit->setText(cfg.value("vlcPath", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"").toString());
	spinBox->setValue(cfg.value("channelId", 0).toInt());
	vlcPath = lineEdit->text().toStdString();
}


void Dialog::accept(){
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	cfg.setValue("vlcPath", lineEdit->text());
	cfg.setValue("channelId", spinBox->value());
	vlcPath = lineEdit->text().toStdString();
	QDialog::accept();
}

void Dialog::reject(){
	QDialog::reject();

}

void Dialog::openLangCfg(){
	Dialog a;
	a.SetupUi();
	a.exec();

}

Dialog::~Dialog()
{

}
