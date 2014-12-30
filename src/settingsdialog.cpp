#include "settingsdialog.h"
#include <QtCore\qsettings.h>
#include <QtWidgets\qmessagebox.h>
#include "commandsdialog.h"
#include "global.h"

using namespace Global;

SettingsDialog::SettingsDialog()
{
}

void SettingsDialog::SetupUi(){

	setupUi(this);
	translateUi();
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	le_vlcPath->setText(cfg.value("vlcPath", "\"C:\\Program Files (x86)\\VideoLAN\\VLC\\vlc.exe\" --extraintf rc --rc-host 127.0.0.1:32323").toString());
	le_rcHost->setText(cfg.value("rcHost", "127.0.0.1").toString());
	le_rcPort->setText(cfg.value("rcPort", 32323).toString());
	cb_language->setCurrentIndex(cfg.value("lang", LANG_EN_US).toInt());
	chb_vote->setChecked(cfg.value("voteEnabled", false).toBool());
	sb_vote->setValue(int(cfg.value("pVoteNeeded", 0.5f).toFloat()*100.0f));

	if (!chb_vote->isChecked())
		sb_vote->setEnabled(false);

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
		ts3Functions.freeMemory(nomeCanal);
		i++;
	}
	ts3Functions.freeMemory(canais);
	cb_channelList->setCurrentIndex(0);
	cb_channelList->setCurrentText(cfg.value("channelName", cb_channelList->currentText()).toString());

	pb_selfChannel->setEnabled(true);
	if (!musicbot.telnetIsConnected()){
		pb_connectVlc->setEnabled(true);
	}
	pb_enableBot->setEnabled(true);
	cb_channelList->setEnabled(true);

}

void SettingsDialog::translateUi()
{
	this->setWindowTitle(languages[curLanguage].GUI_TITLE_SETTINGS.c_str());
	label_vlcPath->setText(languages[curLanguage].GUI_LABEL_VLC_EXE_PATH.c_str());
	le_vlcPath->setText("\"C:\\Program Files (x86)\\VideoLAN\\VLC\\vlc.exe\" --extraintf rc --rc-host 127.0.0.1:32323");
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
	label_rcHost->setText("VLC rc Ip:");
	le_rcHost->setText("127.0.0.1");
	label_rcPort->setText(languages[curLanguage].GUI_LABEL_RC_PORT.c_str());
	le_rcPort->setText("32323");
	chb_vote->setText(languages[curLanguage].GUI_CHB_COMMAND_BY_VOTES.c_str());
	sb_vote->setSuffix("%");
	sb_vote->setPrefix(languages[curLanguage].GUI_PREFFIX_NECESSARY_VOTES.c_str());
	pb_commandsControl->setText(languages[curLanguage].GUI_BUTTON_ENABLE_DISABLE_COMMANDS.c_str());
	pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECT_TO_VLC.c_str());
	pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_ACTIVATE_BOT.c_str());
}

void SettingsDialog::retranslateUi()
{
	this->setWindowTitle(languages[curLanguage].GUI_TITLE_SETTINGS.c_str());
	label_vlcPath->setText(languages[curLanguage].GUI_LABEL_VLC_EXE_PATH.c_str());
	label_channel->setText(languages[curLanguage].GUI_LABEL_MUSIC_CHANNEL.c_str());
	pb_selfChannel->setText(languages[curLanguage].GUI_BUTTON_USE_CURRENT_CHANNEL.c_str());
	label_language->setText(languages[curLanguage].GUI_LABEL_LANGUAGE.c_str());
	label_rcPort->setText(languages[curLanguage].GUI_LABEL_RC_PORT.c_str());
	chb_vote->setText(languages[curLanguage].GUI_CHB_COMMAND_BY_VOTES.c_str());
	sb_vote->setPrefix(languages[curLanguage].GUI_PREFFIX_NECESSARY_VOTES.c_str());
	pb_commandsControl->setText(languages[curLanguage].GUI_BUTTON_ENABLE_DISABLE_COMMANDS.c_str());
	if (musicbot.telnetIsConnected())
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECTED.c_str());
	else
		pb_connectVlc->setText(languages[curLanguage].GUI_BUTTON_CONNECT_TO_VLC.c_str());
	if (musicbot.isEnabled())
		pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_DEACTIVATE_BOT.c_str());
	else
		pb_enableBot->setText(languages[curLanguage].GUI_BUTTON_ACTIVATE_BOT.c_str());
}


void SettingsDialog::accept(){

	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	cfg.setValue("vlcPath", le_vlcPath->text());
	cfg.setValue("rcHost", le_rcHost->text());
	cfg.setValue("rcPort", le_rcPort->text().toInt());
	cfg.setValue("lang", cb_language->currentIndex());
	cfg.setValue("voteEnabled", chb_vote->isChecked());
	float pvn = ((float)sb_vote->value()) / 100.0f;
	cfg.setValue("pVoteNeeded", pvn);

	curLanguage = cb_language->currentIndex();
	musicbot.setVlcPath(le_vlcPath->text().toStdString());
	musicbot.setHostPort(le_rcHost->text().toStdString(), le_rcPort->text().toInt());
	musicbot.setVote(chb_vote->isChecked());
	musicbot.setPVoteNeeded(pvn);

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
				ts3Functions.freeMemory(nomeCanal);
				break;
			}
			ts3Functions.freeMemory(nomeCanal);
			i++;
		}
		ts3Functions.freeMemory(canais);
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
					ts3Functions.freeMemory(nomeCanal);
					break;
				}
				ts3Functions.freeMemory(nomeCanal);
				i++;
			}
			ts3Functions.freeMemory(canais);
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
	retranslateUi();
}

void SettingsDialog::commandControl(){
	CommandsDialog dlg;
	dlg.SetupUi();
	dlg.exec();
}

void SettingsDialog::voteToggle(bool enabled){
	if (enabled){
		sb_vote->setEnabled(true);
	} else {
		sb_vote->setEnabled(false);
	}
}

void SettingsDialog::reject(){

	QDialog::reject();

}

SettingsDialog::~SettingsDialog()
{

}
