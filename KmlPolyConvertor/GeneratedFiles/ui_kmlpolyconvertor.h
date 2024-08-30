/********************************************************************************
** Form generated from reading UI file 'kmlpolyconvertor.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KMLPOLYCONVERTOR_H
#define UI_KMLPOLYCONVERTOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KmlPolyConvertorClass
{
public:
    QWidget *centralWidget;
    QPushButton *begin;
    QProgressBar *progressBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *KmlPolyConvertorClass)
    {
        if (KmlPolyConvertorClass->objectName().isEmpty())
            KmlPolyConvertorClass->setObjectName(QString::fromUtf8("KmlPolyConvertorClass"));
        KmlPolyConvertorClass->resize(300, 220);
        KmlPolyConvertorClass->setMinimumSize(QSize(300, 220));
        KmlPolyConvertorClass->setMaximumSize(QSize(300, 220));
        centralWidget = new QWidget(KmlPolyConvertorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        begin = new QPushButton(centralWidget);
        begin->setObjectName(QString::fromUtf8("begin"));
        begin->setGeometry(QRect(14, 90, 271, 71));
        QFont font;
        font.setFamily(QString::fromUtf8("Trebuchet MS"));
        font.setPointSize(20);
        begin->setFont(font);
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(14, 30, 271, 41));
        progressBar->setFont(font);
        progressBar->setValue(0);
        KmlPolyConvertorClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(KmlPolyConvertorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        KmlPolyConvertorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(KmlPolyConvertorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        KmlPolyConvertorClass->setStatusBar(statusBar);

        retranslateUi(KmlPolyConvertorClass);

        QMetaObject::connectSlotsByName(KmlPolyConvertorClass);
    } // setupUi

    void retranslateUi(QMainWindow *KmlPolyConvertorClass)
    {
        KmlPolyConvertorClass->setWindowTitle(QApplication::translate("KmlPolyConvertorClass", "GSM KML for Pyramida M", 0, QApplication::UnicodeUTF8));
        begin->setText(QApplication::translate("KmlPolyConvertorClass", "\320\262\321\213\320\261\321\200\320\260\321\202\321\214 \321\204\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class KmlPolyConvertorClass: public Ui_KmlPolyConvertorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KMLPOLYCONVERTOR_H
