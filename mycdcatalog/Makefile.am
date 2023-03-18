####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = mycdcatalog

## INCLUDES were found outside kdevelop specific part

mycdcatalog_SOURCES = mp3lyrics.cpp mp3apic.cpp mp3popm.cpp mp3geob.cpp pdfhandler.cpp mp3handler.cpp mp3_id3.cpp mp3_header.cpp filehandlerfactory.cpp filehandler.cpp waitthread.cpp volume.cpp traverser.cpp sqlmanager.cpp showerror.cpp session.cpp resultsview.cpp results.cpp restart.cpp mounter.cpp initializer.cpp initform.cpp filetype.cpp file.cpp dirfile.cpp directory.cpp closer.cpp cfgmanager.cpp cfg.cpp cdreader.cpp SResView.ui SInitForm.ui main.cpp 
mycdcatalog_LDADD   = ./filetype/libfiletype.a -lsqlplus -lqt-mt -lid3 $(LIB_KFILE) $(LIB_KDEUI) $(LIBSOCKET)

SUBDIRS = filetype 

EXTRA_DIST = main.cpp mycdcatalog.desktop lo32-app-mycdcatalog.png lo16-app-mycdcatalog.png SInitForm.ui SResView.ui cdreader.cpp cfg.cpp cfg.h cfgmanager.cpp cfgmanager.h closer.cpp closer.h directory.cpp directory.h dirfile.cpp dirfile.h file.cpp file.h filetype.cpp filetype.h initform.cpp initform.h initializer.cpp initializer.h mounter.cpp mounter.h restart.cpp restart.h results.cpp results.h resultsview.cpp resultsview.h session.cpp session.h showerror.cpp showerror.h sqlmanager.cpp sqlmanager.h traverser.cpp traverser.h volume.cpp volume.h waitthread.cpp waitthread.h mycdcatalog.sql filehandler.cpp filehandler.h filehandlerfactory.cpp filehandlerfactory.h mp3_header.cpp mp3_header.h mp3_id3.cpp mp3_id3.h mp3handler.cpp mp3handler.h pdfhandler.cpp pdfhandler.h mp3geob.cpp mp3geob.h mp3popm.cpp mp3popm.h mp3apic.cpp mp3apic.h mp3lyrics.cpp mp3lyrics.h mp3handler.sql cdreader.h 

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/mycdcatalog.desktop $(kde_appsdir)/Applications/mycdcatalog.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-mycdcatalog.png $(kde_icondir)/locolor/32x32/apps/mycdcatalog.png
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-mycdcatalog.png $(kde_icondir)/locolor/16x16/apps/mycdcatalog.png

uninstall-local:
	-rm -f $(kde_appsdir)/Applications/mycdcatalog.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/mycdcatalog.png
	-rm -f $(kde_icondir)/locolor/16x16/apps/mycdcatalog.png

####### kdevelop will overwrite this part!!! (end)############
# These paths are KDE specific. Use them:
# kde_appsdir         Where your application's menu entry (.desktop) should go to.
# kde_icondir         Where your icon should go to - better use KDE_ICON.
# kde_sounddir        Where your sounds should go to.
# kde_htmldir         Where your docs should go to. (contains lang subdirs)
# kde_datadir         Where you install application data. (Use a subdir)
# kde_locale          Where translation files should go to. (contains lang subdirs)
# kde_cgidir          Where cgi-bin executables should go to.
# kde_confdir         Where config files should go to (system-wide ones with default values).
# kde_mimedir         Where mimetypes .desktop files should go to.
# kde_servicesdir     Where services .desktop files should go to.
# kde_servicetypesdir Where servicetypes .desktop files should go to.
# kde_toolbardir      Where general toolbar icons should go to (deprecated, use KDE_ICON).
# kde_wallpaperdir    Where general wallpapers should go to.
# kde_templatesdir    Where templates for the "New" menu (Konqueror/KDesktop) should go to.
# kde_bindir          Where executables should go to. Use bin_PROGRAMS or bin_SCRIPTS.
# kde_libdir          Where shared libraries should go to. Use lib_LTLIBRARIES.
# kde_moduledir       Where modules (e.g. parts) should go to. Use kde_module_LTLIBRARIES.
# kde_styledir        Where Qt/KDE widget styles should go to (new in KDE 3).
# kde_designerdir     Where Qt Designer plugins should go to (new in KDE 3).

# set the include path for X, qt and KDE
#INCLUDES= `mysql_config --cflags` -I/usr/local/include $(all_includes)
INCLUDES= -I/usr/local/include $(all_includes)

MAGIC	 = @datadir@/magic
#MAGIC = /usr/share/magic

CXXFLAGS= -DMAGIC='"$(MAGIC)"' -fexceptions -g

METASOURCES = AUTO

# the library search path. 
#mycdcatalog_LDFLAGS = `mysql_config --libs` -L@libdir@/ $(all_libraries) $(KDE_RPATH)
mycdcatalog_LDFLAGS = -L@libdir@/ $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE´s XML GUI builing
#rcdir = $(kde_datadir)/mycdcatalog
#rc_DATA = mycdcatalogui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/mycdcatalog.pot; \
	fi

