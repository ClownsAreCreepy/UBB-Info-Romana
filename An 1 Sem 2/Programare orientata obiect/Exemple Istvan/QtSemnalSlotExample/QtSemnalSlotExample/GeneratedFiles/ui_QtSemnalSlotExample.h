/********************************************************************************
** Form generated from reading UI file 'QtSemnalSlotExample.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTSEMNALSLOTEXAMPLE_H
#define UI_QTSEMNALSLOTEXAMPLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtSemnalSlotExampleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtSemnalSlotExampleClass)
    {
        if (QtSemnalSlotExampleClass->objectName().isEmpty())
            QtSemnalSlotExampleClass->setObjectName(QString::fromUtf8("QtSemnalSlotExampleClass"));
        QtSemnalSlotExampleClass->resize(600, 400);
        menuBar = new QMenuBar(QtSemnalSlotExampleClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtSemnalSlotExampleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtSemnalSlotExampleClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtSemnalSlotExampleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtSemnalSlotExampleClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtSemnalSlotExampleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtSemnalSlotExampleClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtSemnalSlotExampleClass->setStatusBar(statusBar);

        retranslateUi(QtSemnalSlotExampleClass);

        QMetaObject::connectSlotsByName(QtSemnalSlotExampleClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtSemnalSlotExampleClass)
    {
        QtSemnalSlotExampleClass->setWindowTitle(QApplication::translate("QtSemnalSlotExampleClass", "QtSemnalSlotExample", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtSemnalSlotExampleClass: public Ui_QtSemnalSlotExampleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTSEMNALSLOTEXAMPLE_H
