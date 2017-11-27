/********************************************************************************
** Form generated from reading UI file 'fileclient.ui'
**
** Created: Wed Mar 22 20:18:36 2017
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILECLIENT_H
#define UI_FILECLIENT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FileClient
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *sendButton;
    QPushButton *openButton;
    QLabel *sendStautsLabel;

    void setupUi(QDialog *FileClient)
    {
        if (FileClient->objectName().isEmpty())
            FileClient->setObjectName(QString::fromUtf8("FileClient"));
        FileClient->resize(400, 210);
        lineEdit = new QLineEdit(FileClient);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(180, 20, 113, 27));
        lineEdit_2 = new QLineEdit(FileClient);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(180, 60, 113, 27));
        label = new QLabel(FileClient);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 20, 56, 17));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 0, 0);"));
        label_2 = new QLabel(FileClient);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 60, 56, 17));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        sendButton = new QPushButton(FileClient);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(240, 110, 85, 27));
        openButton = new QPushButton(FileClient);
        openButton->setObjectName(QString::fromUtf8("openButton"));
        openButton->setGeometry(QRect(100, 110, 85, 27));
        sendStautsLabel = new QLabel(FileClient);
        sendStautsLabel->setObjectName(QString::fromUtf8("sendStautsLabel"));
        sendStautsLabel->setGeometry(QRect(90, 160, 221, 31));
        sendStautsLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 255, 255);"));

        retranslateUi(FileClient);

        QMetaObject::connectSlotsByName(FileClient);
    } // setupUi

    void retranslateUi(QDialog *FileClient)
    {
        FileClient->setWindowTitle(QApplication::translate("FileClient", "FileClient", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FileClient", "IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FileClient", "\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        sendButton->setText(QApplication::translate("FileClient", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        openButton->setText(QApplication::translate("FileClient", "\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        sendStautsLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FileClient: public Ui_FileClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILECLIENT_H
