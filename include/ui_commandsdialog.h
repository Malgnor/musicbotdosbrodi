/********************************************************************************
** Form generated from reading UI file 'commandsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef COMMANDSDIALOG_H
#define COMMANDSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include <QtWidgets/qcheckbox.h>
#include <sstream>

QT_BEGIN_NAMESPACE

class Ui_CommandsDialog
{
public:
	QWidget *horizontalLayoutWidget;
	QHBoxLayout *horizontalLayout;
	QWidget *horizontalLayoutWidget_2;
	QHBoxLayout *horizontalLayout_2;
	QWidget *horizontalLayoutWidget_3;
	QHBoxLayout *horizontalLayout_3;
	QWidget *horizontalLayoutWidget_4;
	QHBoxLayout *horizontalLayout_4;
	QWidget *horizontalLayoutWidget_5;
	QHBoxLayout *horizontalLayout_5;
	QWidget *horizontalLayoutWidget_6;
	QHBoxLayout *horizontalLayout_6;
	QDialogButtonBox *buttonBox;
	QCheckBox* chb_commands[10];	

	void setupUi(QDialog *CommandsDialog)
	{
		if (CommandsDialog->objectName().isEmpty())
			CommandsDialog->setObjectName(QStringLiteral("CommandsDialog"));
		CommandsDialog->resize(400, 200);
		QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		sizePolicy.setHorizontalStretch(0);
		sizePolicy.setVerticalStretch(0);
		sizePolicy.setHeightForWidth(CommandsDialog->sizePolicy().hasHeightForWidth());
		CommandsDialog->setSizePolicy(sizePolicy);
		CommandsDialog->setMinimumSize(QSize(400, 200));
		CommandsDialog->setMaximumSize(QSize(400, 200));
		horizontalLayoutWidget = new QWidget(CommandsDialog);
		horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
		horizontalLayoutWidget->setGeometry(QRect(10, 10, 381, 21));
		horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
		horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
		horizontalLayout->setContentsMargins(0, 0, 0, 0);
		horizontalLayoutWidget_2 = new QWidget(CommandsDialog);
		horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
		horizontalLayoutWidget_2->setGeometry(QRect(10, 40, 381, 21));
		horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
		horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
		horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
		horizontalLayoutWidget_3 = new QWidget(CommandsDialog);
		horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
		horizontalLayoutWidget_3->setGeometry(QRect(10, 70, 381, 21));
		horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
		horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
		horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
		horizontalLayoutWidget_4 = new QWidget(CommandsDialog);
		horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
		horizontalLayoutWidget_4->setGeometry(QRect(10, 100, 381, 21));
		horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
		horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
		horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
		horizontalLayoutWidget_5 = new QWidget(CommandsDialog);
		horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
		horizontalLayoutWidget_5->setGeometry(QRect(10, 130, 381, 21));
		horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
		horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
		horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
		horizontalLayoutWidget_6 = new QWidget(CommandsDialog);
		horizontalLayoutWidget_6->setObjectName(QStringLiteral("horizontalLayoutWidget_6"));
		horizontalLayoutWidget_6->setGeometry(QRect(10, 160, 381, 25));
		horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_6);
		horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
		horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
		buttonBox = new QDialogButtonBox(horizontalLayoutWidget_6);
		buttonBox->setObjectName(QStringLiteral("buttonBox"));
		buttonBox->setOrientation(Qt::Horizontal);
		buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
		buttonBox->setCenterButtons(true);

		horizontalLayout_6->addWidget(buttonBox);

		unsigned int i = 0;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands0"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands1"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_2);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands2"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_2->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_2);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands3"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_2->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_3);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands4"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_3->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_3);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands5"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_3->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_4);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands6"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_4->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_4);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands7"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_4->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_5);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands8"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_5->addWidget(chb_commands[i]);
		i++;

		chb_commands[i] = new QCheckBox(horizontalLayoutWidget_5);
		chb_commands[i]->setObjectName(QStringLiteral("chb_commands9"));
		chb_commands[i]->setChecked(false);
		chb_commands[i]->setTristate(false);

		horizontalLayout_5->addWidget(chb_commands[i]);

		QObject::connect(buttonBox, SIGNAL(accepted()), CommandsDialog, SLOT(accept()));
		QObject::connect(buttonBox, SIGNAL(rejected()), CommandsDialog, SLOT(reject()));

		QMetaObject::connectSlotsByName(CommandsDialog);
	}

};

namespace Ui {
	class CommandsDialog : public Ui_CommandsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // COMMANDSDIALOG_H
