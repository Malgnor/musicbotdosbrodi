#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets\qdialog.h>
#include "ui_dialog.h"

class Dialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT

public:
	Dialog();
	void SetupUi();
    ~Dialog();

protected slots:
	void accept();
	void reject();
	void openLangCfg();
};

#endif // DIALOG_H
