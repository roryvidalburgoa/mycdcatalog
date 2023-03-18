#include <klocale.h>
/****************************************************************************
** Form implementation generated from reading ui file './SResView.ui'
**
** Created: Thu Jul 11 18:34:54 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#include "SResView.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qprogressbar.h>
#include <qpushbutton.h>
#include <qtextview.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

#include "SResView.ui.h"
static const char* const img0_SResView[] = { 
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
 *  Constructs a SResView which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
SResView::SResView( QWidget* parent,  const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    QPixmap image0( ( const char** ) img0_SResView );
    if ( !name )
	setName( "SResView" );
    resize( 450, 320 ); 
    setMaximumSize( QSize( 450, 320 ) );
    setCaption( tr2i18n( "MyCDCatalog: Reading CDROM ..." ) );
    setIcon( image0 );
    setMouseTracking( FALSE );
    setSizeGripEnabled( FALSE );
    QToolTip::add( this, tr2i18n( "Author: Rory Vidal <roryvidal@yahoo.fr>" ) );
    QWhatsThis::add( this, tr2i18n( "Reading a CDROM Volume." ) );

    QWidget* privateLayoutWidget = new QWidget( this, "Layout8" );
    privateLayoutWidget->setGeometry( QRect( 0, 0, 450, 310 ) ); 
    Layout8 = new QVBoxLayout( privateLayoutWidget, 0, 6, "Layout8"); 

    VolumeData = new QTextView( privateLayoutWidget, "VolumeData" );
    VolumeData->setFrameShape( QTextView::StyledPanel );
    VolumeData->setFrameShadow( QTextView::Sunken );
    VolumeData->setTextFormat( QTextView::RichText );
    QToolTip::add( VolumeData, tr2i18n( "Volume's Information." ) );
    QWhatsThis::add( VolumeData, tr2i18n( "Volume's Information." ) );
    Layout8->addWidget( VolumeData );

    LineSeparator = new QFrame( privateLayoutWidget, "LineSeparator" );
    LineSeparator->setFrameShape( QFrame::HLine );
    LineSeparator->setFrameShadow( QFrame::Sunken );
    LineSeparator->setFrameShape( QFrame::HLine );
    Layout8->addWidget( LineSeparator );

    Layout7 = new QHBoxLayout( 0, 0, 6, "Layout7"); 
    QSpacerItem* spacer = new QSpacerItem( 16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    Layout7->addItem( spacer );

    currentDirFile = new QLabel( privateLayoutWidget, "currentDirFile" );
    currentDirFile->setFocusPolicy( QLabel::TabFocus );
    currentDirFile->setText( QString::null );
    currentDirFile->setTextFormat( QLabel::RichText );
    QToolTip::add( currentDirFile, tr2i18n( "Current File or Directory" ) );
    Layout7->addWidget( currentDirFile );
    QSpacerItem* spacer_2 = new QSpacerItem( 16, 20, QSizePolicy::Fixed, QSizePolicy::Minimum );
    Layout7->addItem( spacer_2 );
    Layout8->addLayout( Layout7 );

    Layout5 = new QHBoxLayout( 0, 0, 6, "Layout5"); 

    aProgressBar = new QProgressBar( privateLayoutWidget, "aProgressBar" );
    aProgressBar->setMaximumSize( QSize( 410, 32767 ) );
    aProgressBar->setCursor( QCursor( 0 ) );
    aProgressBar->setFocusPolicy( QProgressBar::TabFocus );
    aProgressBar->setCenterIndicator( TRUE );
    aProgressBar->setIndicatorFollowsStyle( TRUE );
    QToolTip::add( aProgressBar, tr2i18n( "Progress" ) );
    Layout5->addWidget( aProgressBar );

    rate = new QLabel( privateLayoutWidget, "rate" );
    rate->setMaximumSize( QSize( 100, 32767 ) );
    rate->setText( QString::null );
    Layout5->addWidget( rate );
    Layout8->addLayout( Layout5 );

    Layout2 = new QHBoxLayout( 0, 0, 6, "Layout2"); 
    QSpacerItem* spacer_3 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout2->addItem( spacer_3 );

    Stop = new QPushButton( privateLayoutWidget, "Stop" );
    Stop->setText( tr2i18n( "&Stop" ) );
    QToolTip::add( Stop, tr2i18n( "Stop" ) );
    Layout2->addWidget( Stop );
    QSpacerItem* spacer_4 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout2->addItem( spacer_4 );

    Cancel = new QPushButton( privateLayoutWidget, "Cancel" );
    Cancel->setText( tr2i18n( "&Cancel" ) );
    Cancel->setAccel( 276824131 );
    QToolTip::add( Cancel, tr2i18n( "Cancel" ) );
    Layout2->addWidget( Cancel );
    QSpacerItem* spacer_5 = new QSpacerItem( 20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    Layout2->addItem( spacer_5 );
    Layout8->addLayout( Layout2 );

    // signals and slots connections
    connect( Stop, SIGNAL( clicked() ), this, SLOT( stop_resume_slot() ) );
    connect( Cancel, SIGNAL( clicked() ), this, SLOT( cancel_slot() ) );

    // tab order
    setTabOrder( aProgressBar, Stop );
    setTabOrder( Stop, Cancel );
}

/*  
 *  Destroys the object and frees any allocated resources
 */
SResView::~SResView()
{
    // no need to delete child widgets, Qt does it all for us
}

#include "SResView.moc"
