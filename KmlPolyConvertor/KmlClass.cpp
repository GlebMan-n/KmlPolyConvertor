#include "KmlClass.h"



//шаг отсчета в градусах
short degr_global = 15;
double near_distance_global = 5;
bool square_on = false;

KmlClass::KmlClass(QObject* parent)
{
	_stopped = true;
	isStarted = false;
	if(parent)
		this->setParent(parent);	

	emit signValue(0);
}

KmlClass::~KmlClass()
{
	this->deleteLater();
}

void KmlClass::run()
{
	isStarted = true;
	_stopped = false;
	while(!_stopped)
	{
		_vectorPos.clear();
		//загрузка xml
		try
		{
			_vectorPos = _loadPolyFromKmlFile(_path);
		}
		catch(...)
		{
			CalcFunctions::logError("_loadPolyFromKmlFile "+ _path);
			break;
		}
		
		//сортировка полигонов
		try
		{
			_sortPosPoints();
		}
		catch(...)
		{
			CalcFunctions::logError("_sortPosPoints()" + _path);
			break;
		}

		//вычисление итогового полигона
		try
		{
			_calcResultPolygons();
		}
		catch(...)
		{
			CalcFunctions::logError("_calcResultPolygons()" + _path);
			break;
		}
		try
		{
			_savePolygons();
		}
		catch(...)
		{
			CalcFunctions::logError("_savePolygons()");
			break;
		}

		
		break;
	}
	_vectorPos.clear();

	emit signFinish();
	//this->deleteLater();
}
void KmlClass::loadKmlFile(QString path)
{
		_path = path;
}

std::vector <Pos> KmlClass::_loadPolyFromKmlFile(QString path)
{
	emit signStatus("loading kml...");
	std::vector <Pos> vectorPosLocal;
	vectorPosLocal.clear();
	QDomDocument doc("kmlFile");
	QFile file(path);

	if (!file.open(QIODevice::ReadOnly))
	{
		emit signStatus("cant find file");
		return vectorPosLocal;
	}

	emit signStatus("sets content...");
	if (!doc.setContent(&file)) 
	{
		file.close();
		emit signStatus("cant open file");
		return vectorPosLocal;
	}

	file.close();
	emit signStatus("content ok");
	QString tmp;
	tmp = "";

	//весь файл уровень <kml>
	QDomElement docElem = doc.documentElement();
	tmp += docElem.tagName();
	//получаем корренной элемент уровень <document>
	QDomNode document = docElem.firstChild();
	QDomElement docElem1 = document.toElement();
	tmp += docElem1.tagName();
	//первая запись уровня <document> 
	QDomNode nextDocNode = document.firstChild();
	QDomElement docElem2 = nextDocNode.toElement();
	tmp += docElem2.tagName();
	
	if(docElem1.tagName() == "Folder")
	{
		emit signStatus("file with folder");
		QDomNode nextFolderNode = document.firstChild();
		while(!nextFolderNode.isNull()) 
		{
			QDomElement nextFolderElem = nextFolderNode.toElement();
			QString tmp;
			tmp = nextFolderElem.tagName();

			if(nextFolderElem.tagName() == "name")
			{									
			}

			if(nextFolderElem.tagName() == "visibility")
			{							
			}

			if(nextFolderElem.tagName() == "open")
			{		
			}

			if(nextFolderElem.tagName() == "Document")
			{
				vectorPosLocal = _copyVectorPos(vectorPosLocal,_docParser(nextFolderElem.firstChild()));
			}

			nextFolderNode = nextFolderNode.nextSibling();
		}
		
		return vectorPosLocal;
	}
	else
	{
		emit signStatus("file without folder");
		return _docParser(nextDocNode);
	}
}

std::vector <Pos> KmlClass::_copyVectorPos(std::vector <Pos> vector1, std::vector <Pos> vector2)
{
	std::vector <Pos> result;
	std::copy(vector1.begin(), vector1.end(), std::back_inserter(result) );
    std::copy(vector2.begin(), vector2.end(), std::back_inserter(result) );
	return result;
}

std::vector <Pos> KmlClass::_docParser(QDomNode nextDocNode)
{
	
	emit signStatus("start parsing...");
	std::vector <Pos> vectorPosLocal;
	vectorPosLocal.clear();

	while(!nextDocNode.isNull()) 
	{
		//получаем элемент из записи
		QDomElement nextDocElem = nextDocNode.toElement();
		//элемент не пустой
		if(!nextDocElem.isNull()) 
		{

			//ПОЛУЧАЕМ СТИЛИ
			if(nextDocElem.tagName() == "Style")
			{
				
				KmlStyle kmlStyle;
				kmlStyle.id = nextDocElem.attribute("id");
				kmlStyle.threahold_value = nextDocElem.attribute("threshold_value").toDouble();
				QDomNode nextStyleNode = nextDocElem.firstChild();

					
				while(!nextStyleNode.isNull()) 
				{
					QDomElement nextStyleElem = nextStyleNode.toElement();
	
					if(nextStyleElem.tagName() == "LineStyle")
					{
						QDomNode nextLineStyleNode = nextStyleElem.firstChild();
						while(!nextLineStyleNode.isNull()) 
						{
							QDomElement nextLineStyleElem = nextLineStyleNode.toElement();
														
							if(nextLineStyleElem.tagName() == "color")
							{
								QString tmp = nextLineStyleElem.text();
								kmlStyle.lineStyle.visible = tmp.left(2).toInt();
								kmlStyle.lineStyle.color = tmp.right(6);									
							}

							if(nextLineStyleElem.tagName() == "width")
							{
								kmlStyle.lineStyle.width = nextLineStyleElem.text().toInt();								
							}

							nextLineStyleNode = nextLineStyleNode.nextSibling();
						}
					}

					if(nextStyleElem.tagName() == "PolyStyle")
					{
						
						QDomNode nextPolyStyleNode = nextStyleElem.firstChild();
						while(!nextPolyStyleNode.isNull()) 
						{
							QDomElement nextPolyStyleElem = nextPolyStyleNode.toElement();
												
							if(nextPolyStyleElem.tagName() == "color")
							{
								QString tmp = nextPolyStyleElem.text();
								kmlStyle.polygonStyle.visible = tmp.left(2).toInt();
								kmlStyle.polygonStyle.color = tmp.right(6);									
							}

							nextPolyStyleNode = nextPolyStyleNode.nextSibling();
						}
					}

					//следующая запись
					nextStyleNode = nextStyleNode.nextSibling();

				}
				//сохраняем стиль в вектор
				//std::vector <KmlStyle> vectorKmlStyles;
				//vectorKmlStyles.push_back(kmlStyle);
			}
			////////////////СТИЛИ ПОЛУЧИЛИ
			//////////////////////////////
					
					
			//ПОЛУЧАЕМ ОТМЕТКИ (ПОЛИГОНЫ)
			
			if(nextDocElem.tagName() == "Placemark")
			{
				
				QDomNode nextPlacemarkNode = nextDocElem.firstChild();

				//получим имя отметки
				QString placemarkName = nextDocElem.attribute("name");
				//получим имя стиля
				QString styleName = nextDocElem.attribute("styleUrl");
				QString coordinates;
				
				//по имени стиля можно определить стиль полигона
				
				while(!nextPlacemarkNode.isNull()) 
				{
					QDomElement nextPlacemarkElem = nextPlacemarkNode.toElement();

					//получаем полигон
					if(nextPlacemarkElem.tagName() == "Polygon")
					{
						QDomNode nexPolygontNode = nextPlacemarkElem.firstChild();
						QString extrude;
						QString tessellate;
						while(!nexPolygontNode.isNull()) 
						{
							QDomElement nextPolygonElem = nexPolygontNode.toElement();


							if(nextPolygonElem.tagName() == "extrude")
								extrude = nextPolygonElem.text();					
							
							if(nextPolygonElem.tagName() == "tessellate")
								tessellate = nextPolygonElem.text();	

							if(nextPolygonElem.tagName() == "outerBoundaryIs")
							{
								QDomNode nextOuterBoundaryIsNode = nextPolygonElem.firstChild();
								while(!nextOuterBoundaryIsNode.isNull()) 
								{
									QDomElement nextOuterBoundaryIsElem = nextOuterBoundaryIsNode.toElement();
									
									if(nextOuterBoundaryIsElem.tagName() == "LinearRing")
									{
										QDomNode nextLinearRingNode = nextOuterBoundaryIsElem.firstChild();
										while(!nextLinearRingNode.isNull()) 
										{
											QDomElement nextLinearRingElem = nextLinearRingNode.toElement();
											if(nextLinearRingElem.tagName() == "coordinates")
											{
												//координаты получены! нарисовать полигон по координатам
												//и дело сделано (стиль можно получить в styleName)
												coordinates = nextLinearRingElem.text();
												
												//получаем квадрат
												Pos pos1;
												pos1.lat = coordinates.section(',', 1, 1).toDouble();
												pos1.lon = coordinates.section(',', 0, 0).toDouble();

												if(_isPosGood(pos1) && square_on)
													vectorPosLocal.push_back(pos1);	

												Pos pos2;
												pos2.lat = coordinates.section(',', 3, 3).toDouble();
												pos2.lon = coordinates.section(',', 2, 2).section(' ',1,1).toDouble();
												
												if(_isPosGood(pos2) && square_on)
													vectorPosLocal.push_back(pos2);		

												Pos pos3;
												pos3.lat = coordinates.section(',', 5, 5).toDouble();
												pos3.lon = coordinates.section(',', 4, 4).section(' ',1,1).toDouble();

												if(_isPosGood(pos3) && square_on)
													vectorPosLocal.push_back(pos3);		

												Pos pos4;
												pos4.lat = coordinates.section(',', 7, 7).toDouble();
												pos4.lon = coordinates.section(',', 6, 6).section(' ',1,1).toDouble();

												if(_isPosGood(pos4) && square_on)
													vectorPosLocal.push_back(pos4);	

												////получаем центр квадрата
												if(! square_on)
												{
													Pos centrPoly;
													centrPoly.lat = (pos1.lat + pos2.lat + pos3.lat + pos4.lat) / 4 ;
													centrPoly.lon = (pos1.lon + pos2.lon + pos3.lon + pos4.lon) / 4 ;
													emit signStatus(QString::number(centrPoly.lat)+" "+QString::number(centrPoly.lon));
													////формируем массив точек
													if(_isPosGood(centrPoly))
														vectorPosLocal.push_back(centrPoly);
												}
												//
												//сортируем точки по расстоянию друг от друга
											}
											if(_stopped)
												break;
											nextLinearRingNode = nextLinearRingNode.nextSibling();
										}
										
									}
									if(_stopped)
										break;
									nextOuterBoundaryIsNode = nextOuterBoundaryIsNode.nextSibling();
								}
							}
							if(_stopped)
								break;
							nexPolygontNode = nexPolygontNode.nextSibling();
						}
					}
					//следующая запись
					if(_stopped)
						break;
					nextPlacemarkNode = nextPlacemarkNode.nextSibling();
				}
			}
			//ПОЛУЧИЛИ ПОЛИГОНЫ
			/////////////////////////////
		}
		if(_stopped)
			break;
		//вызываем следующий элемент уровня <document>
		nextDocNode = nextDocNode.nextSibling();

	}
	return vectorPosLocal;
}

bool KmlClass::_isPosGood(Pos pos)
{
	return (pos.lat > 0 && pos.lat < 90 && pos.lon > 0 && pos.lon < 180);
}
void KmlClass::setPath(QString path)
{
	_path = path;
}

void  KmlClass::clear()
{

}

void KmlClass::stop()
{
	_stopped = true;
}

bool KmlClass::isStopped()
{
	return _stopped;
}

bool KmlClass::_isNearPos(Pos pos1, Pos pos2)
{
	double distPoint = CalcFunctions::findRasstRadians(pos1.lat*CCT_PI_180,pos2.lat*CCT_PI_180,pos1.lon*CCT_PI_180,pos2.lon*CCT_PI_180);
	return distPoint < near_distance_global;
}

bool KmlClass::_savePolygons()
{
	try
	{
		//пути
		QString currDate = QTime::currentTime().toString ("hhmmss");
		QString path = QCoreApplication::applicationDirPath();

		QFileInfo fileInfo(_path);
		path +=	QDir::separator();
		path += fileInfo.fileName();
	
		QFile file (path);
		if (!file.open(QIODevice::Append | QIODevice::Text))
			return false;



		//получаем полигон

		emit signProgressMax(_polygons.size());
		emit signProgressMin(0);
		emit signStatus("save polygons");
		emit signValue(0);
		QString header = QString("<?xml version=\"1.0\" encoding=\"UTF-8\"?><kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\" xmlns:kml=\"http://www.opengis.net/kml/2.2\" xmlns:atom=\"http://www.w3.org/2005/Atom\">") +
		 QString("<Folder><name>Polygon folder</name><visibility>0</visibility><open>1</open><Document><name>polygons</name><visibility>0</visibility>")+
		 QString("<Style id=\"styleNo1\" threshold_value=\"45.0\"><LineStyle><width>0</width><color>80ffff00</color></LineStyle><PolyStyle><color>80ffff00</color></PolyStyle></Style>") +
		QString("<open>1</open>\n");

		file.write(header.toLocal8Bit(), header.size());

		for(int polyNo = 0; polyNo < _polygons.size(); polyNo++)
		{
			emit signValue(polyNo);
			//получаем cледующий полигон
			std::vector <Pos> polygon = _polygons.at(polyNo);
			//получаем точку полигона
			QString formatAdd = "<Placemark><styleUrl>#styleNo1</styleUrl><Polygon><extrude>0</extrude><tessellate>0</tessellate><outerBoundaryIs><LinearRing><coordinates>\n";
			file.write(formatAdd.toLocal8Bit(), formatAdd.size());

			for(int pointNo = 0; pointNo < polygon.size(); pointNo++)
			{
					Pos pos = 	polygon.at(	pointNo);	
					QString coordStr = "\t"+QString::number(pos.lon) + "," + QString::number(pos.lat)+",0\n";
					file.write(coordStr.toLocal8Bit(), coordStr.size());
			}	

			formatAdd = "</coordinates></LinearRing></outerBoundaryIs></Polygon></Placemark>\n";
			file.write(formatAdd.toLocal8Bit(), formatAdd.size());
			
		}
		emit signValue(_polygons.size());
		emit signStatus("save polygons ok");

		QString tmp = QString("</Document></Folder></kml>");
		file.write(tmp.toLocal8Bit(), tmp.size());
		file.close ();
	}
	catch(...)
	{
		emit signStatus("save polygons fail");
	}

	return true;
}

bool KmlClass::_sortPosPoints()
{
	try
	{
			//перебираем все точки
		emit signProgressMax(_vectorPos.size());
		emit signProgressMin(0);
		emit signStatus("Start sort");

		for(int i = 0; i < _vectorPos.size(); i++)
		{
			emit signValue(i);
			bool res = false;
			//получаем текущую точку массива
			Pos pos;
			try
			{
				pos = _vectorPos.at(i);
			}
			catch(...)
			{
				emit signStatus("Pos pos = _vectorPos.at(i)");
			}
			//если размер массива полигонов 0 создаем первый полигон
			if(_polygons.size() < 1)
			{
				
				try
				{	
					std::vector <Pos> polygon;
					polygon.push_back(_vectorPos.at(i));
					_polygons.push_back(polygon);
					res = true;	
				}
				catch(...)
				{
					CalcFunctions::logError("_polygons.size() < 1");
				}
			}

			//перебираем все полигоны, 
			for(int x = 0; x < _polygons.size(); x++)
			{
				if(res)
					break;
				//перебираем все полигоны
				//каждую точку каждого полигона проверяем
				//на близость с текущей
				for(int y = 0; y < _polygons.at(x).size(); y++)
				{
					if(_isNearPos(_vectorPos.at(i),_polygons.at(x).at(y)))
					{
						//если близка добавляем в массив
						try
						{
							_polygons.at(x).push_back(pos);
						}
						catch(...)
						{
							CalcFunctions::logError("_polygons.at(x).push_back(pos);");
						}
						res = true;
						break;
					}
				}

			}
				
			//если точка не близка 
			//создаем пустой полигон и помещаем туда точку
			if(_stopped)
				break;
			if(!res)
			{
				try
				{
					std::vector <Pos> polygon;
					polygon.push_back(_vectorPos.at(i));
					_polygons.push_back(polygon);
				}
				catch(...)
				{
					CalcFunctions::logError("if(!res)");
				}
			}
		}
		emit signStatus("Sort success");
		emit signValue(_vectorPos.size());
		_vectorPos.clear();
		return true;
	}
	catch(...)
	{
		emit signStatus("Fail");
		return false;
	}
}







std::vector <Pos> KmlClass::_getResultPoly(std::vector <Pos> polygon)
{
	std::vector <Pos> result;
	//широта начала отсчета
	short lat_global = 90;
	//долгота начала отсчета
	short lon_global = 180;
	while(true)
	{		
		//север - восток
		if(lon_global > 179 && lat_global < 91 && lat_global > 0) 
			lat_global -= degr_global;
		
		//запад - север
		if(lon_global < 1)
		{
			lat_global += degr_global;
			if(lat_global > 89) break;
		}

		//восток - запад
		if(lon_global > 0 && lon_global < 181 && lat_global < 1)	
			lon_global -= degr_global;
		
		Pos pos = Pos(lat_global, lon_global);
		result.push_back(_neerestPointInPolyTo(polygon,pos));
	}
	return result;
}

Pos KmlClass::_neerestPointInPolyTo(std::vector <Pos> polygon,Pos posTo)
{
	double dist = 1.7E+308;
	Pos result = Pos();

	for (int i = 0; i < polygon.size(); i++)
	{
		double rasst = CalcFunctions::findRasstRadians(polygon.at(i).lat*CCT_PI_180,posTo.lat*CCT_PI_180,polygon.at(i).lon*CCT_PI_180,posTo.lon*CCT_PI_180);
		if(dist > rasst)
		{
			dist = rasst;
			result = polygon.at(i);
		}
	}
	return result;
}

void KmlClass::_calcResultPolygons()
{
	for(int i = 0; i < _polygons.size(); i++)
	{
		_polygons.at(i) = _getResultPoly(_polygons.at(i));
	}
}
