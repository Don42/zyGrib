CONFIG += qt release
# CONFIG += qt debug console

TEMPLATE = app
TARGET   = zyGrib

DEPENDPATH  += . util map GUI
INCLUDEPATH += . util map GUI
INCLUDEPATH += curvedrawer

# ----------------------------------------------------
# platform specific
# ----------------------------------------------------
win32 {
	INCLUDEPATH += C:/libs/include/  C:/libs/qwt/include/
	LIBS += -LC:/libs/lib/ -lbz2 -lz -lproj -lqwt -lnova
	DESTDIR = release
	RC_FILE += resource.rc
}
else {
macx {
	QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5
	INCLUDEPATH += /usr/local/qwt-6.0.1/include/
	LIBS += -lbz2 -lz -lproj -L/usr/local/qwt-6.0.1/lib/ -lqwt -lnova
	DESTDIR = ..
	CONFIG += i386
	ICON = ../data/img/zyGrib.icns
}
else {
	DESTDIR = .
	INCLUDEPATH += /usr/include/qwt /usr/local/qwt6/include/
	LIBS += -lbz2 -lz -lproj -L/usr/local/qwt6/lib/ -lqwt -lnova

}
}
# ----------------------------------------------------

CFLAGS += -std=c99 

OBJECTS_DIR = objs
MOC_DIR = objs
UI_DIR  = GUI

QT += network xml

CODECFORTR = UTF-8
CODECFORSRC = UTF-8
TRANSLATIONS =  ../data/tr/zyGrib_fr.ts \
				../data/tr/zyGrib_cz.ts \
				../data/tr/zyGrib_de.ts \
				../data/tr/zyGrib_fi.ts \
				../data/tr/zyGrib_it.ts \
				../data/tr/zyGrib_nl.ts \
				../data/tr/zyGrib_pt.ts \
				../data/tr/zyGrib_ru.ts \
				../data/tr/zyGrib_ar.ts \
				../data/tr/zyGrib_es.ts

!win32 {
	# conditional, because uic dont work in my cross compilator environment.
	# ui_*.h files are made under linux before windows compilation.
	
	FORMS += GUI/PositionEditorWidget.ui \
		 	 GUI/PoiEditorDialog.ui \
			 GUI/ColorEditorWidget.ui \
			 GUI/LineEditorWidget.ui \
			 GUI/TextStyleEditorWidget.ui \
			 GUI/GraphicsParamsDialog.ui \
			 GUI/MeteotableOptionsDialog.ui \
		 	 GUI/AngleConverterWidget.ui 
}

HEADERS += \
			 GUI/PositionEditorWidget.h \
			 GUI/ColorEditorWidget.h \
			 GUI/LineEditorWidget.h \
			 GUI/TextStyleEditorWidget.h \
		 	 GUI/AngleConverterWidget.h \
		 	 GUI/AngleConverterDialog.h \
				curvedrawer/BoatSpeed.h \
				curvedrawer/CurveDrawer.h \
				curvedrawer/CustomQwtClasses.h \
			Astro.h \
           BoardPanel.h \
		   ColorScale.h \
		   ColorScaleWidget.h \
		   DataDefines.h \
		   DataColors.h \
		   DataQString.h \
		   DataMeteoAbstract.h \
           DataPointInfo.h \
           DateChooser.h \
		   DialogBoxBase.h \
		   DialogBoxColumn.h \
           DialogFonts.h \
           DialogGraphicsParams.h \
           DialogLoadGRIB.h \
           DialogLoadIAC.h \
           DialogLoadMBLUE.h \
           DialogProxy.h \
           DialogSelectMetar.h \
           DialogServerStatus.h \
           DialogUnits.h \
           FileLoader.h \
           FileLoaderGRIB.h \
           FileLoaderIAC.h \
           FileLoaderMBLUE.h \
           Font.h \
           GshhsRangsReader.h \
           GshhsReader.h \
           GisReader.h \
           GribAnimator.h \
           GribPlot.h \
           GribReader.h \
           GribRecord.h \
		   GriddedPlotter.h \
		   GriddedRecord.h \
		   GriddedReader.h \
           IacPlot.h \
           IacReader.h \
           ImageWriter.h \
		   IrregularGridded.h \
           IsoLine.h \
		   LongTaskProgress.h \
           LonLatGrid.h \
           MbzFile.h \
           MbluePlot.h \
           MblueReader.h \
           MblueRecord.h \
           Metar.h \
           MeteoTable.h \
           MeteoTableWidget.h \
           MeteotableOptionsDialog.h \
           MainWindow.h \
           MapDrawer.h \
           MenuBar.h \
           Orthodromie.h \
           POI.h \
           POI_Editor.h \
           PositionEditor.h \
           Projection.h \
           Settings.h \
           SkewT.h \
           Terrain.h \
           Therm.h \
           Util.h \
           Version.h \
           zuFile.h

SOURCES += \
			 GUI/PositionEditorWidget.cpp \
			 GUI/ColorEditorWidget.cpp \
			 GUI/LineEditorWidget.cpp \
			 GUI/TextStyleEditorWidget.cpp \
		 	 GUI/AngleConverterWidget.cpp \
		 	 GUI/AngleConverterDialog.cpp \
				curvedrawer/BoatSpeed.cpp \
				curvedrawer/CurveDrawer.cpp \
				curvedrawer/CustomQwtClasses.cpp \
		Astro.cpp \
        MbzFile.cpp \
		MblueRecord.cpp \
		MblueReader.cpp \
		MbluePlot.cpp \
           BoardPanel.cpp \
		   ColorScale.cpp \
		   ColorScaleWidget.cpp \
		   DataColors.cpp \
		   DataQString.cpp \
		   DataMeteoAbstract.cpp \
           DataPointInfo.cpp \
           DateChooser.cpp \
		   DialogBoxColumn.cpp \
           DialogFonts.cpp \
           DialogGraphicsParams.cpp \
           DialogLoadGRIB.cpp \
           DialogLoadIAC.cpp \
           DialogLoadMBLUE.cpp \
           DialogProxy.cpp \
           DialogSelectMetar.cpp \
           DialogServerStatus.cpp \
           DialogUnits.cpp \
           FileLoaderGRIB.cpp \
           FileLoaderIAC.cpp \
           FileLoaderMBLUE.cpp \
           Font.cpp \
		   GriddedPlotter.cpp \
		   GriddedReader.cpp \
		   GriddedRecord.cpp \
           GshhsRangsReader.cpp \
           GshhsReader.cpp \
           GribAnimator.cpp \
           GribPlot.cpp \
           GisReader.cpp \
           GribReader.cpp \
           GribRecord.cpp \
           IacPlot.cpp \
           IacReader.cpp \
           IacReaderUtil.cpp \
           ImageWriter.cpp \
		   IrregularGridded.cpp \
           IsoLine.cpp \
		   LongTaskProgress.cpp \
           LonLatGrid.cpp \
           main.cpp \
           MainWindow.cpp \
           MapDrawer.cpp \
           MenuBar.cpp \
           Metar.cpp \
           MeteoTable.cpp \
           MeteoTableWidget.cpp \
           MeteotableOptionsDialog.cpp \
           Orthodromie.cpp \
           POI.cpp \
           POI_Editor.cpp \
           PositionEditor.cpp \
           Projection.cpp \
           Projection_libproj.cpp \
           Settings.cpp \
           SkewT.cpp \
           SkewTWindow.cpp \
           Terrain.cpp \
           Therm.cpp \
           Util.cpp \
           zuFile.cpp


