#include "kmlpolyconvertor.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	KmlPolyConvertor w;
	w.show();
	return a.exec();
}
