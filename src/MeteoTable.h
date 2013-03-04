/**********************************************************************
zyGrib: meteorological GRIB file viewer
Copyright (C) 2008-2012 - Jacques Zaninetti - http://www.zygrib.org

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#ifndef METEOTABLE_H
#define METEOTABLE_H

#include <QDialog>
#include <QFrame>
#include <QScrollArea>
#include <QPushButton>

#include "MeteoTableWidget.h"
#include "MeteotableOptionsDialog.h"

//===================================================================
// MeteoTable : dialog + MeteoTableWidget
//===================================================================
class MeteoTableDialog : public QWidget
{ Q_OBJECT
    public:
        MeteoTableDialog (
					GriddedPlotter *plotter, 
					double lon, double lat, QString locationName="");
        ~MeteoTableDialog();
		
		bool saveFileSYLK (QFile &file);
    
    private:
    	GriddedPlotter *plotter;
    	double   lon, lat;
    	QString  locationName;
		
		MeteoTableWidget 		*meteoTableWidget;
		DialogMeteotableOptions *optionsDialog;
		QScrollArea 			*scrollArea;
		QWidget                 *createDataTable ();
		QWidget * dataTable;
		QVBoxLayout *mainLayout;
		
		QScrollArea *hdrscroll;
     	
     	QPushButton *btClose;
     	QPushButton *btOptions;
		
     	QPushButton *btExport;
		void closeEvent(QCloseEvent *) {delete this;};
		
		bool SYLK_saveFile (QFile &file);
		int  SYLK_addData_gen   (QTextStream &out, int lig,int col, DataCode dtc);
		int  SYLK_addData_wind  (QTextStream &out, int lig,int col, DataCode dtc);
		int  SYLK_addData_current  (QTextStream &out, int lig,int col, DataCode dtc);
		int  SYLK_addData_waves (QTextStream &out, int lig,int col, DataCode dtc);
		
	private slots :
		void slotBtOptions ();
		void slotBtExport ();
		void slotOptionsChanged ();
		void reject ()	{delete this;};
};


#endif
