/********************************************************************************
** Form generated from reading UI file 'PetStoreObserverGit.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PETSTOREOBSERVERGIT_H
#define UI_PETSTOREOBSERVERGIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PetStoreObserverGitClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PetStoreObserverGitClass)
    {
        if (PetStoreObserverGitClass->objectName().isEmpty())
            PetStoreObserverGitClass->setObjectName(QString::fromUtf8("PetStoreObserverGitClass"));
        PetStoreObserverGitClass->resize(600, 400);
        menuBar = new QMenuBar(PetStoreObserverGitClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        PetStoreObserverGitClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PetStoreObserverGitClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PetStoreObserverGitClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(PetStoreObserverGitClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        PetStoreObserverGitClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(PetStoreObserverGitClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        PetStoreObserverGitClass->setStatusBar(statusBar);

        retranslateUi(PetStoreObserverGitClass);

        QMetaObject::connectSlotsByName(PetStoreObserverGitClass);
    } // setupUi

    void retranslateUi(QMainWindow *PetStoreObserverGitClass)
    {
        PetStoreObserverGitClass->setWindowTitle(QApplication::translate("PetStoreObserverGitClass", "PetStoreObserverGit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PetStoreObserverGitClass: public Ui_PetStoreObserverGitClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PETSTOREOBSERVERGIT_H
