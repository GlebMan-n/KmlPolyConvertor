#include "kmlpolyconvertor.h"


KmlPolyConvertor::KmlPolyConvertor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{	
	_kmlClass = NULL;
	ui.setupUi(this);
	_pathToKml.clear();
	_loadSettings();
	connect(ui.begin,SIGNAL(clicked()),SLOT(_slotBegin()));

	_numOfCore = 0;
	_threadInWork = 0;
	_numOfCore =  QThread::idealThreadCount () ;
}

KmlPolyConvertor::~KmlPolyConvertor()
{
	_saveSettings();
	//if(_kmlClass )
	//{
	//	if(!_kmlClass->isStopped())
	//	{
	//		_kmlClass->stop();
	//		while (!_kmlClass->isFinished())
	//		{
	//			MyThread::msleep(50);
	//		}
	//	}

	//	delete _kmlClass;
	//	_kmlClass = NULL;
	//}
}

void KmlPolyConvertor::_slotBegin()
{
	QString tmp;
	tmp = _pathToKml;
	_pathToKml.clear();
	_pathToKml = QFileDialog::getExistingDirectory(this, tr("Open KML Directory"),
                                             "/home",
                                             QFileDialog::ShowDirsOnly
                                             | QFileDialog::DontResolveSymlinks);

	if(_pathToKml.isEmpty() || _pathToKml.isNull())
	{
		_pathToKml = tmp;
		return;
	}

	QFileInfoList fileList;
	QDir dir(_pathToKml);
	fileList = dir.entryInfoList(QStringList() << "*.kml" , QDir::Files, QDir::Time);
	QString tmp1 = fileList.at(0).absoluteFilePath();
	klmClasses.clear();
	for(int i = 0; i < fileList.size(); i++)
	{
		_kmlClass = new KmlClass(this);	
		connect(_kmlClass,SIGNAL(signFinish()),SLOT(_delKmlClass()));
		_kmlClass->setPath(fileList.at(i).absoluteFilePath ());
		klmClasses.push_back(_kmlClass);
	}

	_slotRunThread();

}

void KmlPolyConvertor::_saveSettings()
{
	QSettings settings (QCoreApplication::applicationDirPath () + "/settings.ini", QSettings::IniFormat);
	settings.setValue("path/PathToKml",_pathToKml);
	settings.sync();
}

bool KmlPolyConvertor::_loadSettings()
{
	QString path_to_ini = QCoreApplication::applicationDirPath () + "/settings.ini";
	if (QFile::exists(path_to_ini) ) 
	{
		QSettings settings (path_to_ini, QSettings::IniFormat);
		_pathToKml = settings.value("path/PathToKml").toString();
		return true;
	}
	return false;
}

void KmlPolyConvertor::_slotSetStatus(QString status)
{
	//ui.statusLbl->setText(status);
	statusBar()->showMessage(status, 2000);

}
void KmlPolyConvertor::_delKmlClass()
{
	_threadInWork--;
	_slotRunThread();
}

void KmlPolyConvertor::_slotRunThread()
{

	bool ready = true;
	for(int i = 0; i < klmClasses.size(); i++)
	{
		if(_threadInWork == _numOfCore)
			return;

		if(!klmClasses.at(i)->isStarted)
		{
			klmClasses.at(i)->start();
			_slotSetStatus("#" + QString::number(i));
			_threadInWork++;
			ready = false;
			break;
		}
	}
	if(!ready)
		_slotRunThread();
	else
	{
		for(int i = 0; i < klmClasses.size(); i++)
		{
			KmlClass* kmlClass = klmClasses.at(i);
			if(kmlClass )
			{
				if(!kmlClass->isStopped())
				{
					kmlClass->stop();
					while (!kmlClass->isFinished())
					{
						MyThread::msleep(50);
					}
				}

				kmlClass->deleteLater();
				
			}
		}
		_slotSetStatus("redy work");
	}
}