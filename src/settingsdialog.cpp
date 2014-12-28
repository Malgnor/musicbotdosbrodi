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
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	le_vlcPath->setText(cfg.value("vlcPath", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"").toString());
	le_rcHost->setText(cfg.value("rcHost", "127.0.0.1").toString());
	le_rcPort->setText(cfg.value("rcPort", 32323).toString());

	if (musicbot.telnetIsConnected()){
		pb_connectVlc->setText("Conectado");
	}
	if (musicbot.isEnabled())
		pb_enableBot->setText("Desativar bot");

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


void SettingsDialog::accept(){

	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	cfg.setValue("vlcPath", le_vlcPath->text());
	cfg.setValue("rcHost", le_rcHost->text());
	cfg.setValue("rcPort", le_rcPort->text().toInt());
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
		msgBox.setText("Foi conectado com sucesso!");
		pb_connectVlc->setText("Conectado");
		pb_connectVlc->setDisabled(true);
	} else {
		msgBox.setText("Falha ao conectar");
	}
	msgBox.exec();
}

void SettingsDialog::toggleBot(){
	QMessageBox msgBox;
	if (musicbot.isEnabled()){
		if (musicbot.disable()){
			msgBox.setText("O bot foi desativado!");
			pb_enableBot->setText("Ativar bot");
		} else {
			msgBox.setText("Falha ao desativar!");
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
			msgBox.setText("O bot foi ativado!");
			pb_enableBot->setText("Desativar bot");
		} else {
			msgBox.setText("Falha ao ativar");
		}
	}
	msgBox.exec();
}

void SettingsDialog::reject(){

	QDialog::reject();

}

SettingsDialog::~SettingsDialog()
{

}
