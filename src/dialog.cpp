#include "dialog.h"
#include <QtCore\qsettings.h>
#include "global.h"

Dialog::Dialog()
{
}

void Dialog::SetupUi(){

	setupUi(this);
	QSettings cfg(QString::fromStdString(Global::getConfigFilePath()), QSettings::IniFormat);
	lineEdit->setText(cfg.value("vlcPath", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"").toString());
	spinBox->setValue(cfg.value("channelId", 0).toInt());

}


void Dialog::accept(){

	QSettings cfg(QString::fromStdString(Global::getConfigFilePath()), QSettings::IniFormat);
	cfg.setValue("vlcPath", lineEdit->text());
	cfg.setValue("channelId", spinBox->value());

	Global::musicbot.setVlcPath(lineEdit->text().toStdString());
	Global::musicbot.setChannelID(spinBox->value());
	QDialog::accept();

}

void Dialog::reject(){

	QDialog::reject();

}

void Dialog::openLangCfg(){
	/*
	Dialog a;
	a.SetupUi();
	a.exec();
	*/
}

Dialog::~Dialog()
{

}
