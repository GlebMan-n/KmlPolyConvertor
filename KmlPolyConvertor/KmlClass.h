#include <QtGui>
#include <CalcFunctions.h>
#include <QDomDocument>

struct PolygonStyle
{
	PolygonStyle()
	{
		color = "";
		visible = 100;
	}
	QString color;
	short visible;

};

struct LineStyle
{
	LineStyle()
	{
		color = "";
		visible = 100;
		width = 1;
	}
	QString color;
	short visible;
	short width;
};

struct KmlStyle
{
	KmlStyle()
	{
		id = "";
		threahold_value = 0;
		polygonStyle = PolygonStyle();
		lineStyle = LineStyle();
	}	

	QString id;
	double threahold_value;
	PolygonStyle polygonStyle;
	LineStyle lineStyle;
};



class KmlClass : public QThread
{
	Q_OBJECT
public:
	KmlClass(QObject* parent = 0);
	~KmlClass();
	void loadKmlFile(QString path);
	void setPath(QString path);
	void clear();
	void stop();
	bool isStopped();
	bool isStarted;
private:
	volatile bool _stopped;
	//вектор стилей для полигонов
	
	std::vector <Pos> _vectorPos;
	QString _path;	

	std::vector <std::vector <Pos>> _polygons;
	
	
private:
	//загружаем файл
	std::vector <Pos> _loadPolyFromKmlFile(QString path);
	//парсим документ, возвращаем вектор точек
	std::vector <Pos> _docParser(QDomNode nextDocNode);
	//рядом ли точки 
	bool _isNearPos(Pos pos1, Pos pos2);
	//перебераем и группируем все точки
	bool _sortPosPoints();
	//сохранение полигонов сгруппированыыми
	bool _savePolygons();
	Pos _neerestPointInPolyTo(std::vector <Pos> polygon,Pos posTo);
	std::vector <Pos> _getResultPoly(std::vector <Pos> polygon);
	void _calcResultPolygons();
	std::vector <Pos> _copyVectorPos(std::vector <Pos> vector1, std::vector <Pos> vector2);
	bool _isPosGood(Pos pos);

protected:
	void run();
signals:
	void signPosVector(QVector <Pos> vector);
	void signStatus(QString status);
	void signProgressMax(int max);
	void signProgressMin(int min);
	void signValue(int value);
	void signFinish();
};