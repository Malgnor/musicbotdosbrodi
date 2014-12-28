/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QDialogButtonBox *bb_okCancel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_vlcPath;
    QLineEdit *le_vlcPath;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_channel;
    QPushButton *pb_selfChannel;
    QComboBox *cb_channelList;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_language;
    QComboBox *cb_language;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_rcHost;
    QLineEdit *le_rcHost;
    QLabel *label_rcPort;
    QLineEdit *le_rcPort;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pb_connectVlc;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_6;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_7;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pb_enableBot;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QStringLiteral("SettingsDialog"));
        SettingsDialog->setWindowModality(Qt::NonModal);
        SettingsDialog->setEnabled(true);
        SettingsDialog->resize(520, 350);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SettingsDialog->sizePolicy().hasHeightForWidth());
        SettingsDialog->setSizePolicy(sizePolicy);
        SettingsDialog->setMinimumSize(QSize(520, 350));
        SettingsDialog->setMaximumSize(QSize(520, 350));
        SettingsDialog->setSizeGripEnabled(false);
        SettingsDialog->setModal(false);
        bb_okCancel = new QDialogButtonBox(SettingsDialog);
        bb_okCancel->setObjectName(QStringLiteral("bb_okCancel"));
        bb_okCancel->setGeometry(QRect(20, 310, 481, 32));
        bb_okCancel->setOrientation(Qt::Horizontal);
        bb_okCancel->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        bb_okCancel->setCenterButtons(true);
        layoutWidget = new QWidget(SettingsDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 501, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_vlcPath = new QLabel(layoutWidget);
        label_vlcPath->setObjectName(QStringLiteral("label_vlcPath"));

        horizontalLayout->addWidget(label_vlcPath);

        le_vlcPath = new QLineEdit(layoutWidget);
        le_vlcPath->setObjectName(QStringLiteral("le_vlcPath"));

        horizontalLayout->addWidget(le_vlcPath);

        layoutWidget1 = new QWidget(SettingsDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 50, 501, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_channel = new QLabel(layoutWidget1);
        label_channel->setObjectName(QStringLiteral("label_channel"));

        horizontalLayout_2->addWidget(label_channel);

        pb_selfChannel = new QPushButton(layoutWidget1);
        pb_selfChannel->setObjectName(QStringLiteral("pb_selfChannel"));

        horizontalLayout_2->addWidget(pb_selfChannel);

        cb_channelList = new QComboBox(layoutWidget1);
        cb_channelList->setObjectName(QStringLiteral("cb_channelList"));

        horizontalLayout_2->addWidget(cb_channelList);

        layoutWidget2 = new QWidget(SettingsDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 80, 501, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_language = new QLabel(layoutWidget2);
        label_language->setObjectName(QStringLiteral("label_language"));

        horizontalLayout_3->addWidget(label_language);

        cb_language = new QComboBox(layoutWidget2);
        cb_language->setObjectName(QStringLiteral("cb_language"));
        cb_language->setEnabled(false);

        horizontalLayout_3->addWidget(cb_language);

        horizontalLayoutWidget = new QWidget(SettingsDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 110, 501, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_rcHost = new QLabel(horizontalLayoutWidget);
        label_rcHost->setObjectName(QStringLiteral("label_rcHost"));

        horizontalLayout_4->addWidget(label_rcHost);

        le_rcHost = new QLineEdit(horizontalLayoutWidget);
        le_rcHost->setObjectName(QStringLiteral("le_rcHost"));

        horizontalLayout_4->addWidget(le_rcHost);

        label_rcPort = new QLabel(horizontalLayoutWidget);
        label_rcPort->setObjectName(QStringLiteral("label_rcPort"));

        horizontalLayout_4->addWidget(label_rcPort);

        le_rcPort = new QLineEdit(horizontalLayoutWidget);
        le_rcPort->setObjectName(QStringLiteral("le_rcPort"));

        horizontalLayout_4->addWidget(le_rcPort);

        horizontalLayoutWidget_2 = new QWidget(SettingsDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(10, 150, 501, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        pb_connectVlc = new QPushButton(horizontalLayoutWidget_2);
        pb_connectVlc->setObjectName(QStringLiteral("pb_connectVlc"));

        horizontalLayout_5->addWidget(pb_connectVlc);

        horizontalLayoutWidget_3 = new QWidget(SettingsDialog);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 190, 501, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_4 = new QWidget(SettingsDialog);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(10, 230, 501, 31));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        horizontalLayoutWidget_5 = new QWidget(SettingsDialog);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 270, 501, 31));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        pb_enableBot = new QPushButton(horizontalLayoutWidget_5);
        pb_enableBot->setObjectName(QStringLiteral("pb_enableBot"));

        horizontalLayout_8->addWidget(pb_enableBot);

        bb_okCancel->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        horizontalLayoutWidget->raise();
        label_language->raise();
        horizontalLayoutWidget_2->raise();
        horizontalLayoutWidget_3->raise();
        horizontalLayoutWidget_4->raise();
        horizontalLayoutWidget_5->raise();

        retranslateUi(SettingsDialog);
        QObject::connect(bb_okCancel, SIGNAL(accepted()), SettingsDialog, SLOT(accept()));
        QObject::connect(bb_okCancel, SIGNAL(rejected()), SettingsDialog, SLOT(reject()));
        QObject::connect(cb_channelList, SIGNAL(currentIndexChanged(QString)), SettingsDialog, SLOT(onChannelListChange(QString)));
        QObject::connect(pb_connectVlc, SIGNAL(clicked()), SettingsDialog, SLOT(connectVlc()));
        QObject::connect(pb_enableBot, SIGNAL(clicked()), SettingsDialog, SLOT(toggleBot()));
        QObject::connect(pb_selfChannel, SIGNAL(clicked()), SettingsDialog, SLOT(useSelfChannel()));

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "Configura\303\247\303\265es", 0));
        label_vlcPath->setText(QApplication::translate("SettingsDialog", "Caminho do execut\303\241vel do VLC win32:", 0));
        le_vlcPath->setText(QApplication::translate("SettingsDialog", "\"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe\"", 0));
        label_channel->setText(QApplication::translate("SettingsDialog", "Canal de m\303\272sica", 0));
        pb_selfChannel->setText(QApplication::translate("SettingsDialog", "Usar canal atual", 0));
        cb_channelList->clear();
        cb_channelList->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "Default Channel", 0)
        );
        label_language->setText(QApplication::translate("SettingsDialog", "Idioma", 0));
        cb_language->clear();
        cb_language->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "pt-BR", 0)
         << QApplication::translate("SettingsDialog", "en-US", 0)
        );
        label_rcHost->setText(QApplication::translate("SettingsDialog", "VLC rc ip:", 0));
        le_rcHost->setText(QApplication::translate("SettingsDialog", "127.0.0.1", 0));
        label_rcPort->setText(QApplication::translate("SettingsDialog", "porta:", 0));
        le_rcPort->setText(QApplication::translate("SettingsDialog", "32323", 0));
        pb_connectVlc->setText(QApplication::translate("SettingsDialog", "Conectar ao VLC", 0));
        pb_enableBot->setText(QApplication::translate("SettingsDialog", "Ativar bot", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
