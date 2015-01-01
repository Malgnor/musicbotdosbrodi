#include "commandsdialog.h"
#include <QtCore\qsettings.h>
#include "global.h"

using namespace Global;

CommandsDialog::CommandsDialog()
{
}

void CommandsDialog::SetupUi(){

	setupUi(this);
	translateUi();
	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	cfg.beginReadArray("commandsEnabled");
	for (int i = 0; i < COMMANDS_QTD; i++){
		cfg.setArrayIndex(i);
		chb_commands[i]->setChecked(cfg.value("cmd", true).toBool());
	}
	cfg.endArray();

}

void CommandsDialog::translateUi(){
	this->setWindowTitle(languages[curLanguage].GUI_TITLE_COMMANDS.c_str());
	chb_commands[0]->setText(languages[curLanguage].USER_COMMAND_YOUTUBE.c_str());
	chb_commands[1]->setText(languages[curLanguage].USER_COMMAND_HELP.c_str());
	chb_commands[2]->setText(languages[curLanguage].USER_COMMAND_PLAYING.c_str());
	chb_commands[3]->setText(languages[curLanguage].USER_COMMAND_LENGTH.c_str());
	chb_commands[4]->setText(languages[curLanguage].USER_COMMAND_NEXT.c_str());
	chb_commands[5]->setText(languages[curLanguage].USER_COMMAND_PREV.c_str());
	chb_commands[6]->setText(languages[curLanguage].USER_COMMAND_PAUSE.c_str());
	chb_commands[7]->setText(languages[curLanguage].USER_COMMAND_PLAY.c_str());
	chb_commands[8]->setText(languages[curLanguage].USER_COMMAND_GOTO.c_str());
	chb_commands[9]->setText(languages[curLanguage].USER_COMMAND_TIME.c_str());
}

void CommandsDialog::accept(){

	QSettings cfg(QString::fromStdString(getConfigFilePath()), QSettings::IniFormat);
	bool cmds[COMMANDS_QTD];
	cfg.beginWriteArray("commandsEnabled");
	for (int i = 0; i < COMMANDS_QTD; i++){
		cfg.setArrayIndex(i);
		cmds[i] = chb_commands[i]->isChecked();
		cfg.setValue("cmd", cmds[i]);
	}
	cfg.endArray();

	musicbot.setCommandsEnabled(cmds);

	QDialog::accept();

}

void CommandsDialog::reject(){

	QDialog::reject();

}

CommandsDialog::~CommandsDialog()
{

}
