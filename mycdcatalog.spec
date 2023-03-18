# This spec file was generated using Kpp
# If you find any problems with this spec file please report
# the error to ian geiser <geiseri@msoe.edu>
Summary:   Util for dump CDROM information from a CDROM source to a mysql database.
Name:      mycdcatalog
Version:   0.3
Release:   0.3
Copyright: GPL
Vendor:    Rory Vidal <roryvidal@yahoo.fr>
Url:       http://mycdcatalog.sourceforge.net

Packager:  Rory Vidal <roryvidal@yahoo.fr>
Group:     Applications
Source:    mycdcatalog-0.3.tar.gz
BuildRoot: building

%description
Util for dump CDROM informationfrom a CDROM source to a mysqldatabase.

%prep
%setup
CFLAGS="$RPM_OPT_FLAGS" CXXFLAGS="$RPM_OPT_FLAGS" ./configure \
                --build=i386-linux --host=i386-linux --target=i386-linux --enable-mt \
                $LOCALFLAGS
%build
# Setup for parallel builds
numprocs=`egrep -c ^cpu[0-9]+ /proc/stat || :`
if [ "$numprocs" = "0" ]; then
  numprocs=1
fi

make -j$numprocs

%install
make install-strip DESTDIR=$RPM_BUILD_ROOT

cd $RPM_BUILD_ROOT
find . -type d | sed '1,2d;s,^\.,\%attr(-\,root\,root) \%dir ,' > $RPM_BUILD_DIR/file.list.mycdcatalog
find . -type f | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.mycdcatalog
find . -type l | sed 's,^\.,\%attr(-\,root\,root) ,' >> $RPM_BUILD_DIR/file.list.mycdcatalog

%clean
rm -rf $RPM_BUILD_ROOT/*
rm -rf $RPM_BUILD_DIR/mycdcatalog
rm -rf ../file.list.mycdcatalog


%files -f ../file.list.mycdcatalog
