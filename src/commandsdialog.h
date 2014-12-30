#ifndef _COMMANDSDIALOG_H
#define _COMMANDSDIALOG_H

#include <QtWidgets\qdialog.h>
#include "ui_commandsdialog.h"

class CommandsDialog : public QDialog, public Ui::CommandsDialog
{
	Q_OBJECT

public:
	CommandsDialog();
	void SetupUi();
	void translateUi();
	~CommandsDialog();

	protected slots:
	void accept();
	void reject();
};

#endif // _COMMANDSDIALOG_H
