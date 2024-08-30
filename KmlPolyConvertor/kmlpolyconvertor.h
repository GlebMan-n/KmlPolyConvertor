#ifndef KMLPOLYCONVERTOR_H
#define KMLPOLYCONVERTOR_H

#include <QtGui/QMainWindow>
#include "ui_kmlpolyconvertor.h"
#include <KmlClass.h>

class KmlClass;
class KmlPolyConvertor : public QMainWindow
{
	Q_OBJECT

public:
	KmlPolyConvertor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~KmlPolyConvertor();
	void _saveSettings();
	bool _loadSettings();
private:
	Ui::KmlPolyConvertorClass ui;
	KmlClass* _kmlClass;
	QString _pathToKml;
	short _numOfCore;
	short _threadInWork;
	struct MyThread : public QThread { using QThread::msleep;};
	std::vector<KmlClass*> klmClasses;
	private slots:
		void _slotBegin();
		void _slotSetStatus(QString status);
		void _slotRunThread();
		void _delKmlClass();
		
};

#endif // KMLPOLYCONVERTOR_H
