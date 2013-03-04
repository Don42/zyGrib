
#include "SkewT.h"

//---------------------------------------------------------------	
SkewTWindow::SkewTWindow (SkewT *skewt)
{
	this->skewt = skewt;
	createToolBar ();
	
	QScrollArea *scrollarea = new QScrollArea (this);
	scrollarea->setWidget (skewt);
	setCentralWidget (scrollarea);
	
	QByteArray geom = Util::getSetting ("skewt_windowGeometry", "" ).toByteArray();
	if (geom != "")
		restoreGeometry (geom);
	
	double tmax = Util::getSetting ("skewt_tempCMax", 40).toDouble();
	double pmin = Util::getSetting ("skewt_hpaMin", 190).toDouble();
	skewt->setTempPressLimits (tmax, pmin);
	
	QString cbase = Util::getSetting ("skewt_convectiveBase", "1000-1000").toString();
	skewt->setConvectiveBase (cbase);
	
	skewt->setFocus (Qt::PopupFocusReason);
	setWindowTitle ("SkewT "+skewt->getLocation());
}
//------------------------------------------------------
SkewTWindow::~SkewTWindow ()
{
	if (skewt) {
		delete skewt;
		skewt = NULL;
	}
}
//------------------------------------------------------
void SkewTWindow::closeEvent (QCloseEvent *)
{
	if (skewt) {
		delete skewt;
		skewt = NULL;
	}
}
//------------------------------------------------------
void SkewTWindow::resizeEvent (QResizeEvent *)
{
	Util::setSetting ("skewt_windowGeometry", saveGeometry());
}
//---------------------------------------------------------------	
void SkewTWindow::createToolBar ()
{
	QToolBar *toolBar = addToolBar (tr("skewt"));
    toolBar->setFloatable(false);
    toolBar->setMovable(false);
	//------------------------------------
    acExit = new QAction (this);
    acExit->setToolTip (tr("Close the window"));
	acExit->setIcon(QIcon(Util::pathImg("exit.png")));
	connect(acExit, SIGNAL(triggered()), this, SLOT(actionsCommonSlot()));
	toolBar->addAction (acExit);
	
    acPrint = new QAction (this);
    acPrint->setToolTip (tr("Print the diagram"));
	acPrint->setIcon(QIcon(Util::pathImg("printer.png")));
	connect(acPrint, SIGNAL(triggered()), this, SLOT(actionsCommonSlot()));
	toolBar->addAction (acPrint);
	
    acSaveImage = new QAction (this);
    acSaveImage->setToolTip (tr("Save current image"));
	acSaveImage->setIcon(QIcon(Util::pathImg("media-floppy.png")));
	connect(acSaveImage, SIGNAL(triggered()), this, SLOT(actionsCommonSlot()));
	toolBar->addAction (acSaveImage);
	
    toolBar->addSeparator();
	//------------------------------------
	toolBar->addWidget (new QLabel (tr("T max: ")));
	cbTempMax = new QComboBox (this);
	for (int t=-40; t<=80; t+=5)
		cbTempMax->addItem (QString("%1 °C").arg(t), t);
	cbTempMax->setMaxVisibleItems (50);
	connect(cbTempMax, SIGNAL(activated(int)), this, SLOT(actionsCommonSlot()));
	double tmax = Util::getSetting ("skewt_tempCMax", 40).toDouble();
	cbTempMax->setCurrentIndex (cbTempMax->findData (tmax));
	toolBar->addWidget (cbTempMax);
	//------------------------------------
	toolBar->addWidget (new QLabel (tr("P min: ")));
	cbHpaMin = new QComboBox (this);
	for (int p=100; p<=700; p+=100)
		cbHpaMin->addItem (QString("%1 hPa").arg(p), p-5);
	connect(cbHpaMin, SIGNAL(activated(int)), this, SLOT(actionsCommonSlot()));
	double pmin = Util::getSetting ("skewt_hpaMin", 190).toDouble();
	cbHpaMin->setCurrentIndex (cbHpaMin->findData (pmin));
	toolBar->addWidget (cbHpaMin);
	//------------------------------------
	double sz;
	toolBar->addWidget (new QLabel (tr("Size: ")));
	cbSizeW = new QComboBox (this);
	for (double s=600; s<=2000; s+=200)
		cbSizeW->addItem (QString("%1").arg(s), s);
	connect(cbSizeW, SIGNAL(activated(int)), this, SLOT(actionsCommonSlot()));
	sz = Util::getSetting ("skewt_sizeW", 800).toDouble();
	cbSizeW->setCurrentIndex (cbSizeW->findData (sz));
	toolBar->addWidget (cbSizeW);
	
	cbSizeH = new QComboBox (this);
	for (double s=600; s<=2000; s+=200)
		cbSizeH->addItem (QString("%1").arg(s), s);
	connect(cbSizeH, SIGNAL(activated(int)), this, SLOT(actionsCommonSlot()));
	sz = Util::getSetting ("skewt_sizeH", 800).toDouble();
	cbSizeH->setCurrentIndex (cbSizeH->findData (sz));
	toolBar->addWidget (cbSizeH);
	
    toolBar->addSeparator();
	//------------------------------------
	chkShowConv = new QCheckBox (tr("Base: "),this);
	chkShowConv->setChecked (Util::getSetting ("skewt_showConvectiveCurves",true).toBool());
	connect(chkShowConv, SIGNAL(stateChanged(int)), this, SLOT(actionsCommonSlot()));
	toolBar->addWidget (chkShowConv);
	cbConvBase = new QComboBox (this);
		if (skewt->hasSurfaceData) {
			cbConvBase->addItem (  ("Surface"), "surface");
			cbConvBase->addItem (  ("Avg Surface-10 hPa"), "surface-10");
			cbConvBase->addItem (  ("Avg Surface-20 hPa"), "surface-20");
			cbConvBase->addItem (  ("Avg Surface-50 hPa"), "surface-50");
			cbConvBase->addItem (  ("Avg Surface-100 hPa"), "surface-100");
		}
		cbConvBase->addItem ("1000 hPa", "1000-1000");
		cbConvBase->addItem ("975 hPa", "975-975");
		cbConvBase->addItem ("950 hPa", "950-950");
		cbConvBase->addItem ("925 hPa", "925-925");
		cbConvBase->addItem ("900 hPa", "900-900");
		cbConvBase->addItem ("850 hPa", "850-850");
		cbConvBase->addItem ("800 hPa", "800-800");
		cbConvBase->addItem ("750 hPa", "750-750");
		cbConvBase->addItem ("700 hPa", "700-700");
		cbConvBase->addItem ("650 hPa", "650-650");
		cbConvBase->addItem ("Avg 1000-975 hPa", "1000-975");
		cbConvBase->addItem ("Avg 1000-950 hPa", "1000-950");
		cbConvBase->addItem ("Avg 1000-925 hPa", "1000-925");
		cbConvBase->addItem ("Avg 1000-900 hPa", "1000-900");
		cbConvBase->addItem ("Avg 1000-850 hPa", "1000-850");
		cbConvBase->addItem ("Avg 1000-800 hPa", "1000-800");
	cbConvBase->setMaxVisibleItems (50);
	connect(cbConvBase, SIGNAL(activated(int)), this, SLOT(actionsCommonSlot()));
	QString sbase = Util::getSetting ("skewt_convectiveBase", "1000-1000").toString();
	cbConvBase->setCurrentIndex (cbConvBase->findData (sbase));
	cbConvBase->setEnabled (chkShowConv->isChecked());
	toolBar->addWidget (cbConvBase);
}
//---------------------------------------------------------------	
void SkewTWindow::actionsCommonSlot ()
{
	setCursor (Qt::WaitCursor);
	QObject *send = sender ();
	if (send == acExit) {
		this->hide ();
		this->destroy ();
		if (skewt) {
			delete skewt;
			skewt = NULL;
		}
	}	
	else if (send == cbTempMax) {
		int v = cbTempMax->itemData (cbTempMax->currentIndex()).toInt();
		Util::setSetting ("skewt_tempCMax", v);
		skewt->setTempPressLimits (v, skewt->getHpaMin());
	}
	else if (send == cbHpaMin) {
		int v = cbHpaMin->itemData (cbHpaMin->currentIndex()).toInt();
		Util::setSetting ("skewt_hpaMin", v);
		skewt->setTempPressLimits (skewt->getTempCMax(), v-10);
	}
	else if (send == cbSizeW) {
		double sz = cbSizeW->itemData (cbSizeW->currentIndex()).toDouble();
		Util::setSetting ("skewt_sizeW", sz);
		skewt->setSkewTSize (sz, skewt->height());
	}
	else if (send == cbSizeH) {
		double sz = cbSizeH->itemData (cbSizeH->currentIndex()).toDouble();
		Util::setSetting ("skewt_sizeH", sz);
		skewt->setSkewTSize (skewt->width(), sz);
	}
	else if (send == cbConvBase) {
		QString cbase = cbConvBase->itemData (cbConvBase->currentIndex()).toString();
		Util::setSetting ("skewt_convectiveBase", cbase);
		skewt->setConvectiveBase (cbase);
	}
	else if (send == chkShowConv) {
		Util::setSetting ("skewt_showConvectiveCurves", chkShowConv->isChecked());
		skewt->resetGraphic ();
		cbConvBase->setEnabled (chkShowConv->isChecked());
	}
	else if (send == acPrint) {
		QPrinter printer;
		printer.setOutputFormat (QPrinter::PdfFormat);
		printer.setResolution (150);

		QPrintDialog *dialog = new QPrintDialog(&printer, this);
		dialog->setWindowTitle (tr("Print Document"));
		
		if (dialog->exec() == QDialog::Accepted) 
		{
			QPainter painter;
			painter.begin(&printer);
			double xscale = printer.pageRect().width()/double(skewt->width());
			double yscale = printer.pageRect().height()/double(skewt->height());
			double scale = qMin(xscale, yscale);
			painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
								printer.paperRect().y() + printer.pageRect().height()/2);
			painter.scale(scale, scale);
			painter.translate(-skewt->width()/2, -skewt->height()/2);
			skewt->setPrinterRendering (true);
			skewt->render (&painter);
			skewt->setPrinterRendering (false);
		}
	}
	else if (send == acSaveImage) {
		QString filename = Util::getSetting("skewt_imageSaveFilename", "").toString();
		filename = QFileDialog::getSaveFileName (this,
					tr("Save JPEG image"),
					filename, 
					tr("Images (*.jpg *.jpeg)") );	
		if (filename != "") {
			if (   ! filename.endsWith(".jpg", Qt::CaseInsensitive) 
				&& ! filename.endsWith(".jpeg", Qt::CaseInsensitive) )
						filename += ".jpg";
			Util::setSetting("skewt_imageSaveFilename", filename);
			QImage image (skewt->size(), QImage::Format_RGB32);
			skewt->setPrinterRendering (true);
			skewt->render (&image);
			skewt->setPrinterRendering (false);
			image.save (filename, "JPEG", 96);
		}
	}
	unsetCursor ();
}







