#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './SInitForm.ui'
**
** Created: Thu Jul 11 18:34:59 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "SInitForm.h"

#include <qvariant.h>
#include <klineedit.h>
#include <knuminput.h>
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qgroupbox.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

static const char* const img0_SInitForm[] = { 
"16 16 135 2",
"Qt c None",
"#0 c #424714",
"#v c #4d682b",
"#R c #4e5826",
"#G c #4e6329",
"#g c #4f5932",
"#8 c #575945",
"#Z c #575f16",
"#V c #576138",
"#j c #5a712b",
"#9 c #5b5d4b",
"#7 c #5d5e4c",
"#1 c #5e6249",
"#W c #646a34",
"#Y c #656d1c",
"#X c #6a6f20",
"#L c #6b7d2d",
".8 c #6c8029",
".5 c #6e7e43",
"#z c #6e863d",
"#6 c #707266",
"#A c #709122",
"#w c #727a65",
".4 c #72902c",
"#k c #737c64",
".X c #73872f",
"#u c #75943f",
"#H c #767d6c",
"#i c #768c47",
"#K c #788358",
"a. c #797a70",
"#e c #79a413",
".U c #7a8951",
".T c #7a8d4e",
".M c #7b8753",
"#Q c #7b8930",
".6 c #7b8952",
".7 c #7d8e47",
".9 c #7e8568",
"#f c #7f9f25",
".3 c #7fa619",
".V c #808b54",
"#h c #809153",
".L c #818d59",
"#o c #83a32b",
".W c #849344",
"#F c #879e3f",
".S c #8bae35",
"#p c #8bb514",
"#d c #8bb713",
".Y c #8c9279",
".K c #8c9560",
".J c #8c9a5d",
"#q c #8cb319",
"#S c #8d9086",
".A c #8f9578",
"#c c #8fb125",
".2 c #8fbc15",
".I c #91a160",
".1 c #92b627",
"#s c #93a74c",
"#t c #97af51",
"#U c #999c8e",
".B c #999d8d",
".Q c #99c032",
".R c #99cb1e",
".z c #9aa379",
"#5 c #9b9d96",
"#P c #a0af31",
".p c #a1a499",
".o c #a2a392",
"#r c #a3b946",
"#n c #a4a79a",
"#b c #a4a896",
".N c #a5a79e",
".0 c #a6ab99",
".y c #a7ae75",
".F c #a8bd68",
".H c #a8c356",
"#y c #aaada5",
".q c #acaea8",
"#O c #acb831",
"#B c #acbf3d",
".n c #aeac94",
"#E c #aec34b",
".P c #afb3a3",
"a# c #b0b0ad",
".G c #b0da4b",
".m c #b1b49d",
"#M c #b2b155",
".u c #b3b8a4",
"#2 c #b4b5b2",
"#N c #b8b947",
"ac c #b9b9b8",
".l c #babcb3",
".v c #bacc81",
"ab c #bbbbbb",
"#J c #bbbcb9",
"ad c #bebebd",
".E c #bec0ba",
"#l c #bfbfbf",
"#x c #c0c1c0",
"#. c #c2c3c2",
".C c #c4c4c3",
".r c #c5c5c4",
"#I c #c5c6c5",
"#D c #c6d550",
".f c #c7c7c7",
"#4 c #c8c8c7",
".e c #c9c9c9",
".Z c #cacaca",
".x c #cbc77a",
"ae c #cbcbcb",
".g c #cccccc",
"#C c #ced75b",
".k c #cfcfce",
".w c #cfdc7b",
".d c #d0d0d0",
"#T c #d1d1d1",
".t c #d2d3d2",
"aa c #d4d4d4",
"#a c #d5d5d5",
".O c #d6d6d6",
".h c #d7d7d7",
".c c #dbdbdb",
".s c #dedede",
".D c #e2e2e2",
"#3 c #e3e3e3",
".i c #e4e4e4",
".j c #e5e5e5",
"#m c #e6e6e6",
"## c #e7e7e7",
".b c #e8e8e8",
".a c #e9e9e9",
".# c #eaeaea",
"QtQtQtQtQtQtQtQtQtQtQtQtQtQtQtQt",
"QtQtQtQtQtQtQt.#.aQtQtQtQtQtQtQt",
"QtQtQtQt.b.c.d.e.f.g.h.iQtQtQtQt",
"QtQtQt.j.k.l.m.n.o.p.q.r.sQtQtQt",
"QtQtQt.t.u.v.w.x.y.z.A.B.C.iQtQt",
"QtQt.D.E.F.G.H.I.J.K.L.M.N.OQtQt",
"QtQt.c.P.Q.R.S.T.U.V.W.X.Y.ZQtQt",
"QtQt.O.0.1.2.3.4.5.6.7.8.9#.##Qt",
"QtQt#a#b#c#d#e#f#g#h#i#j#k#l#mQt",
"QtQt.O#n#o#p#q#r#s#t#u#v#w#x#mQt",
"QtQt.c#y#z#A#B#C#D#E#F#G#H#I.bQt",
"QtQt.D#J#K#L#M#N#O#P#Q#R#S#TQtQt",
"QtQtQt.d#U#V#W#X#Y#Z#0#1#2.sQtQt",
"QtQtQt#3#4#5#6#7#8#9a.a##aQtQtQt",
"QtQtQtQt.jaa.rabacadae.c.#QtQtQt",
"QtQtQtQtQtQt.b#3.D.j.#QtQtQtQtQt"};


/* 
 *  Constructs a SInitForm which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SInitForm::SInitForm( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QPixmap image0( ( const char** ) img0_SInitForm );
    if ( !name )
	setName( "SInitForm" );
    resize( 400, 360 ); 
    setMaximumSize( QSize( 400, 360 ) );
    setCaption( tr2i18n( "MyCDCatalog: Options", "Options Form" ) );
    setIcon( image0 );
    setFocusPolicy( QDialog::TabFocus );
    QWhatsThis::add( this, tr2i18n( "Options before read a CDROM volume and store its information into a MySQL Database.", "Options" ) );

    QWidget* privateLayoutWidget = new QWidget( this, "ButtonsLayout" );
    privateLayoutWidget->setGeometry( QRect( 0, 330, 390, 30 ) ); 
    ButtonsLayout = new QHBoxLayout( privateLayoutWidget, 0, 6, "ButtonsLayout"); 
    QSpacerItem* spacer = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ButtonsLayout->addItem( spacer );

    StartButton = new QPushButton( privateLayoutWidget, "StartButton" );
    StartButton->setText( tr2i18n( "&Read CDROM" ) );
    ButtonsLayout->addWidget( StartButton );
    QSpacerItem* spacer_2 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ButtonsLayout->addItem( spacer_2 );

    CloseButton = new QPushButton( privateLayoutWidget, "CloseButton" );
    CloseButton->setText( tr2i18n( "&Close Application" ) );
    ButtonsLayout->addWidget( CloseButton );
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    ButtonsLayout->addItem( spacer_3 );

    OptionsLabels = new QGroupBox( this, "OptionsLabels" );
    OptionsLabels->setGeometry( QRect( 20, 0, 360, 330 ) ); 
    OptionsLabels->setTitle( tr2i18n( "Options" ) );
    QToolTip::add( OptionsLabels, tr2i18n( "MyCDCatalog options" ) );
    QWhatsThis::add( OptionsLabels, tr2i18n( "MyCDCatalog options" ) );

    RadioButtons = new QButtonGroup( OptionsLabels, "RadioButtons" );
    RadioButtons->setGeometry( QRect( 10, 260, 340, 40 ) ); 
    RadioButtons->setTitle( QString::null );

    Remote = new QRadioButton( RadioButtons, "Remote" );
    Remote->setGeometry( QRect( 70, 10, 70, 19 ) ); 
    Remote->setText( tr2i18n( "R&emote" ) );
    Remote->setChecked( TRUE );

    Local = new QRadioButton( RadioButtons, "Local" );
    Local->setGeometry( QRect( 220, 10, 60, 19 ) ); 
    Local->setText( tr2i18n( "&Local" ) );

    QWidget* privateLayoutWidget_2 = new QWidget( OptionsLabels, "Layout5" );
    privateLayoutWidget_2->setGeometry( QRect( 10, 20, 340, 230 ) ); 
    Layout5 = new QGridLayout( privateLayoutWidget_2, 1, 1, 0, 6, "Layout5"); 

    LE_Password = new KLineEdit( privateLayoutWidget_2, "LE_Password" );
    LE_Password->setEchoMode( KLineEdit::Password );

    Layout5->addWidget( LE_Password, 3, 1 );

    LE_Device = new KLineEdit( privateLayoutWidget_2, "LE_Device" );
    QToolTip::add( LE_Device, QString::null );

    Layout5->addWidget( LE_Device, 0, 1 );

    LE_Username = new KLineEdit( privateLayoutWidget_2, "LE_Username" );

    Layout5->addWidget( LE_Username, 2, 1 );

    LE_Socket = new KLineEdit( privateLayoutWidget_2, "LE_Socket" );
    LE_Socket->setEnabled( FALSE );
    LE_Socket->setText( tr2i18n( "/var/lib/mysql/mysql.sock" ) );

    Layout5->addWidget( LE_Socket, 6, 1 );

    LE_Port = new KIntNumInput( privateLayoutWidget_2, "LE_Port" );
    LE_Port->setValue( 3306 );

    Layout5->addWidget( LE_Port, 5, 1 );

    LE_Database = new KLineEdit( privateLayoutWidget_2, "LE_Database" );

    Layout5->addWidget( LE_Database, 7, 1 );

    MntPoint = new QLabel( privateLayoutWidget_2, "MntPoint" );
    MntPoint->setText( tr2i18n( "Mount Point :" ) );

    Layout5->addWidget( MntPoint, 1, 0 );

    Username = new QLabel( privateLayoutWidget_2, "Username" );
    Username->setText( tr2i18n( "Username :" ) );

    Layout5->addWidget( Username, 2, 0 );

    Password = new QLabel( privateLayoutWidget_2, "Password" );
    Password->setText( tr2i18n( "Password :" ) );

    Layout5->addWidget( Password, 3, 0 );

    LE_Server = new KLineEdit( privateLayoutWidget_2, "LE_Server" );

    Layout5->addWidget( LE_Server, 4, 1 );

    Server = new QLabel( privateLayoutWidget_2, "Server" );
    Server->setText( tr2i18n( "Server :" ) );

    Layout5->addWidget( Server, 4, 0 );

    Port = new QLabel( privateLayoutWidget_2, "Port" );
    Port->setText( tr2i18n( "Port :" ) );

    Layout5->addWidget( Port, 5, 0 );

    Device = new QLabel( privateLayoutWidget_2, "Device" );
    Device->setText( tr2i18n( "Device :" ) );

    Layout5->addWidget( Device, 0, 0 );

    LocalSocket = new QLabel( privateLayoutWidget_2, "LocalSocket" );
    LocalSocket->setText( tr2i18n( "Local Socket :" ) );

    Layout5->addWidget( LocalSocket, 6, 0 );

    LE_MntPoint = new KLineEdit( privateLayoutWidget_2, "LE_MntPoint" );

    Layout5->addWidget( LE_MntPoint, 1, 1 );

    Database = new QLabel( privateLayoutWidget_2, "Database" );
    Database->setText( tr2i18n( "Database :" ) );

    Layout5->addWidget( Database, 7, 0 );

    Eject = new QCheckBox( OptionsLabels, "Eject" );
    Eject->setGeometry( QRect( 70, 300, 250, 16 ) ); 
    Eject->setText( tr2i18n( "E&ject CDROM at the process end" ) );

    // signals and slots connections
    connect( StartButton, SIGNAL( clicked() ), this, SLOT( read_slot() ) );
    connect( Remote, SIGNAL( clicked() ), this, SLOT( remote_slot() ) );
    connect( Local, SIGNAL( clicked() ), this, SLOT( local_slot() ) );
    connect( CloseButton, SIGNAL( clicked() ), this, SLOT( closer_slot() ) );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
SInitForm::~SInitForm()
{
    // no need to delete child widgets, Qt does it all for us
}

void SInitForm::closer_slot()
{
    qWarning( "SInitForm::closer_slot(): Not implemented yet!" );
}

void SInitForm::local_slot()
{
    qWarning( "SInitForm::local_slot(): Not implemented yet!" );
}

void SInitForm::read_slot()
{
    qWarning( "SInitForm::read_slot(): Not implemented yet!" );
}

void SInitForm::remote_slot()
{
    qWarning( "SInitForm::remote_slot(): Not implemented yet!" );
}

#include "SInitForm.moc"
