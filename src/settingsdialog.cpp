#include "settingsdialog.h"
#include <QtCore\qsettings.h>
#include <QtWidgets\qmessagebox.h>
#include <QtWidgets\qabstractbutton.h>
#include <QtGui\qevent.h>
#include "global.h"

using namespace Global;

SettingsDialog::SettingsDialog()
{
}

void SettingsDialog::SetupUi(){

	setupUi(this);
	retranslateUi();
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	le_vlcPath->setText(cfg.value("vlcPath", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"").toString());
	le_rcHost->setText(cfg.value("rcHost", "127.0.0.1").toString());
	le_rcPort->setText(cfg.value("rcPort", 32323).toString());
	cb_language->setCurrentIndex(cfg.value("lang", LANG_EN_US).toInt());

	if (musicbot.telnetIsConnected()){
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECTED.c_str());
	}
	if (musicbot.isEnabled())
		pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_DEACTIVATE_BOT.c_str());

	pb_selfChannel->setDisabled(true);
	pb_connectVlc->setDisabled(true);
	pb_enableBot->setDisabled(true);
	cb_channelList->setDisabled(true);

	uint64 schID = musicbot.getSchID();
	uint64* canais;
	if (ts3Functions.getChannelList(schID, &canais) != ERROR_ok){
		ts3Functions.logMessage("Error requesting channel list", LogLevel_ERROR, "Plugin", schID);
		return;
	}
	cb_channelList->clear();
	unsigned int i = 0;
	while (canais[i]){
		char* nomeCanal;
		if (ts3Functions.getChannelVariableAsString(schID, canais[i], 0, &nomeCanal) != ERROR_ok){
			ts3Functions.logMessage("Error requesting channel name", LogLevel_ERROR, "Plugin", schID);
			return;
		}
		cb_channelList->insertItem(i, nomeCanal);
		delete[] nomeCanal;
		i++;
	}
	cb_channelList->setCurrentIndex(0);
	cb_channelList->setCurrentText(cfg.value("channelName", cb_channelList->currentText()).toString());

	pb_selfChannel->setEnabled(true);
	if (!musicbot.telnetIsConnected()){
		pb_connectVlc->setEnabled(true);
	}
	pb_enableBot->setEnabled(true);
	cb_channelList->setEnabled(true);

}

void SettingsDialog::retranslateUi()
{
	this->setWindowTitle(languages[curLanguage].GUI_WINDOWTITLE.c_str());
	label_vlcPath->setText(languages[curLanguage].GUI_LABEL_VLC_EXE_PATH.c_str());
	le_vlcPath->setText("\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"");
	label_channel->setText(languages[curLanguage].GUI_LABEL_MUSIC_CHANNEL.c_str());
	pb_selfChannel->setText(languages[curLanguage].GUI_BUTTON_USE_CURRENT_CHANNEL.c_str());
	cb_channelList->clear();
	cb_channelList->insertItems(0, QStringList()
		<< "Default Channel"
		);
	label_language->setText(languages[curLanguage].GUI_LABEL_LANGUAGE.c_str());
	cb_language->clear();
	cb_language->insertItems(0, QStringList()
		<< "pt-BR"
		<< "en-US"
		);
	label_rcHost->setText("VLC rc ip:");
	le_rcHost->setText("127.0.0.1");
	label_rcPort->setText(languages[curLanguage].GUI_LAVEL_RC_PORT.c_str());
	le_rcPort->setText("32323");
	pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECT_TO_VLC.c_str());
	pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_ACTIVATE_BOT.c_str());
}


void SettingsDialog::accept(){

	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	cfg.setValue("vlcPath", le_vlcPath->text());
	cfg.setValue("rcHost", le_rcHost->text());
	cfg.setValue("rcPort", le_rcPort->text().toInt());
	cfg.setValue("lang", cb_language->currentIndex());
	curLanguage = cb_language->currentIndex();
	musicbot.setVlcPath(le_vlcPath->text().toStdString());
	musicbot.setHostPort(le_rcHost->text().toStdString(), le_rcPort->text().toInt());

	uint64 schID = musicbot.getSchID();
	uint64* canais;
	if (ts3Functions.getChannelList(schID, &canais) != ERROR_ok){
		ts3Functions.logMessage("Error requesting channel list", LogLevel_ERROR, "Plugin", schID);
	} else {
		cfg.setValue("channelName", cb_channelList->currentText());
		unsigned int i = 0;
		while (canais[i]){
			char* nomeCanal;
			if (ts3Functions.getChannelVariableAsString(schID, canais[i], 0, &nomeCanal) != ERROR_ok){
				ts3Functions.logMessage("Error requesting channel name", LogLevel_ERROR, "Plugin", schID);
				break;
			}
			std::string nome = nomeCanal;
			if (nome == cb_channelList->currentText().toStdString()){
				musicbot.setChannelID(canais[i]);
				delete[] nomeCanal;
				break;
			}
			delete[] nomeCanal;
			i++;
		}
	}

	QDialog::accept();

}

void SettingsDialog::useSelfChannel(){
	if (musicbot.getMyID() == 0){
		if (!musicbot.setMyID()){
			return;
		}
	}
	uint64 schID = musicbot.getSchID();
	uint64 cID;
	if (ts3Functions.getChannelOfClient(schID, musicbot.getMyID(), &cID) != ERROR_ok)
	{
		ts3Functions.logMessage("Error requesting channel id", LogLevel_ERROR, "Plugin", schID);
		return;
	}
	char* nome;
	if (ts3Functions.getChannelVariableAsString(schID, cID, 0, &nome) != ERROR_ok){
		ts3Functions.logMessage("Error requesting channel name", LogLevel_ERROR, "Plugin", schID);
		return;
	}
	cb_channelList->setCurrentText(nome);
}

void SettingsDialog::connectVlc(){
	QMessageBox msgBox;
	if (musicbot.telnetConnnect(le_rcHost->text().toStdString(), le_rcPort->text().toInt())){
		msgBox.setText(languages[curLanguage].BOT_CONNECT_SUCESS.c_str());
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECTED.c_str());
		pb_connectVlc->setDisabled(true);
	} else {
		msgBox.setText(languages[curLanguage].BOT_CONNECT_FAIL.c_str());
	}
	msgBox.exec();
}

void SettingsDialog::toggleBot(){
	QMessageBox msgBox;
	if (musicbot.isEnabled()){
		if (musicbot.disable()){
			msgBox.setText(languages[curLanguage].BOT_DEACTIVATED_SUCESS.c_str());
			pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_ACTIVATE_BOT.c_str());
		} else {
			msgBox.setText(languages[curLanguage].BOT_DEACTIVATED_FAIL.c_str());
		}
	} else {
		musicbot.setVlcPath(le_vlcPath->text().toStdString());
		if (musicbot.isConnected()){
			uint64 schID = musicbot.getSchID();
			uint64* canais;
			if (ts3Functions.getChannelList(schID, &canais) != ERROR_ok){
				ts3Functions.logMessage("Error requesting channel list", LogLevel_ERROR, "Plugin", schID);
				return;
			}
			unsigned int i = 0;
			while (canais[i]){
				char* nomeCanal;
				if (ts3Functions.getChannelVariableAsString(schID, canais[i], 0, &nomeCanal) != ERROR_ok){
					ts3Functions.logMessage("Error requesting channel name", LogLevel_ERROR, "Plugin", schID);
					return;
				}
				std::string nome = nomeCanal;
				if (nome == cb_channelList->currentText().toStdString()){
					musicbot.setChannelID(canais[i]);
					delete[] nomeCanal;
					break;
				}
				delete[] nomeCanal;
				i++;
			}
		}
		if (musicbot.enable()){
			msgBox.setText(languages[curLanguage].BOT_ACTIVATED_SUCESS.c_str());
			pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_DEACTIVATE_BOT.c_str());
		} else {
			msgBox.setText(languages[curLanguage].BOT_ACTIVATED_FAIL.c_str());
		}
	}
	msgBox.exec();
}

void SettingsDialog::onLanguageChange(int lang){
	curLanguage = lang;
	translateUi();
}

void SettingsDialog::translateUi()
{
	this->setWindowTitle(languages[curLanguage].GUI_WINDOWTITLE.c_str());
	label_vlcPath->setText(languages[curLanguage].GUI_LABEL_VLC_EXE_PATH.c_str());
	label_channel->setText(languages[curLanguage].GUI_LABEL_MUSIC_CHANNEL.c_str());
	pb_selfChannel->setText(languages[curLanguage].GUI_BUTTON_USE_CURRENT_CHANNEL.c_str());
	label_language->setText(languages[curLanguage].GUI_LABEL_LANGUAGE.c_str());
	label_rcPort->setText(languages[curLanguage].GUI_LAVEL_RC_PORT.c_str());
	if (musicbot.telnetIsConnected())
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECTED.c_str());
	else
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECT_TO_VLC.c_str());
	if (musicbot.isEnabled())
		pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_DEACTIVATE_BOT.c_str());
	else
		pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_ACTIVATE_BOT.c_str());
}

void SettingsDialog::reject(){

	QDialog::reject();

}

SettingsDialog::~SettingsDialog()
{

}
