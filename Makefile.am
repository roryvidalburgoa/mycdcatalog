####### kdevelop will overwrite this part!!! (begin)##########

SUBDIRS = mycdcatalog po doc 

EXTRA_DIST = mycdcatalog.kdevprj AUTHORS COPYING ChangeLog INSTALL README TODO mycdcatalog.lsm mycdcatalog.spec mycdcatalog.doxygen configure.in.in mycdcatalog.xpm 

####### kdevelop will overwrite this part!!! (end)############
# not a GNU package. You can remove this line, if 
# have all needed files, that a GNU package needs
AUTOMAKE_OPTIONS = foreign 

$(top_srcdir)/configure.in: configure.in.in $(top_srcdir)/subdirs
	cd $(top_srcdir) && $(MAKE) -f admin/Makefile.common configure.in ;

$(top_srcdir)/subdirs:
	cd $(top_srcdir) && $(MAKE) -f admin/Makefile.common subdirs

$(top_srcdir)/acinclude.m4: $(top_srcdir)/admin/acinclude.m4.in $(top_srcdir)/admin/libtool.m4.in
	@cd $(top_srcdir) && cat admin/acinclude.m4.in admin/libtool.m4.in > acinclude.m4

MAINTAINERCLEANFILES = subdirs configure.in acinclude.m4 configure.files 

package-messages:
	$(MAKE) -f admin/Makefile.common package-messages
	$(MAKE) -C po merge

EXTRA_DIST = mycdcatalog.kdevprj AUTHORS COPYING ChangeLog INSTALL README TODO mycdcatalog.lsm mycdcatalog.spec admin

dist-hook:
	cd $(top_distdir) && perl admin/am_edit -padmin
	cd $(top_distdir) && $(MAKE) -f admin/Makefile.common subdirs

