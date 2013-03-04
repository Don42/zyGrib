QTBIN=/usr/bin
#QTBIN=/opt/qt/qt/bin
#QTBIN=/usr/local/Trolltech/Qt-4.7.0/bin

INSTALLDIR=$(HOME)/zyGrib

MACQTBIN=/opt/local/bin

all: zyGrib

SRC= src/*.h src/*.cpp src/*/*.h src/*/*.cpp

mac: $(SRC)
	rm -f  ./zyGrib
	rm -fr ./zyGrib.app
	rm -f  src/Makefile
	cd src; $(MACQTBIN)/qmake; make -j5

clean:
	rm -f  zyGrib
	rm -fr zyGrib.app
	rm -f  src/zyGrib
	rm -f  src/release/zyGrib.exe
	cd src;	$(QTBIN)/qmake; make clean

zyGrib: $(SRC)
	@ echo
	rm -f ./zyGrib
	cd src; $(QTBIN)/qmake; make -j5
	@ echo "-----------------------------------"
	@ echo "#!/bin/bash" >> ./zyGrib
	@ echo "cd `pwd`" >> ./zyGrib
	@ echo 'src/zyGrib $$*' >> ./zyGrib
	@ chmod 755 ./zyGrib

install: zyGrib
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/bin
	cp -a data $(INSTALLDIR)
	cp -a grib $(INSTALLDIR)
	rm -f ./zyGrib
	rm -f $(INSTALLDIR)/bin/zyGrib
	cp  -a src/zyGrib $(INSTALLDIR)/bin
	echo "#!/bin/bash" >> ./zyGrib
	echo "cd $(INSTALLDIR)" >> ./zyGrib
	echo 'bin/zyGrib $$*' >> ./zyGrib
	chmod 755 ./zyGrib
	cp -af zyGrib $(INSTALLDIR)


