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
	void retranslateUi();
	void translateUi();
    ~SettingsDialog();

protected slots:
	void accept();
	void reject();
	void connectVlc();
	void toggleBot();
	void useSelfChannel();
	void onLanguageChange(int lang);
};

#endif // _SETTINGSDIALOG_H
