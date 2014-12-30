#ifndef _SETTINGSDIALOG_H
#define _SETTINGSDIALOG_H

#include <QtWidgets\qdialog.h>
#include "ui_settingsdialog.h"

class SettingsDialog : public QDialog, public Ui::SettingsDialog
{
    Q_OBJECT

public:
	SettingsDialog();
	void SetupUi();
	void translateUi();
	void retranslateUi();
    ~SettingsDialog();

protected slots:
	void accept();
	void reject();
	void connectVlc();
	void toggleBot();
	void useSelfChannel();
	void onLanguageChange(int lang);
	void commandControl();
	void voteToggle(bool enabled);
};

#endif // _SETTINGSDIALOG_H
