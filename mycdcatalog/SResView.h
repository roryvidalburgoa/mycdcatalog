/****************************************************************************
** Form interface generated from reading ui file './SResView.ui'
**
** Created: Thu Jul 11 18:33:03 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef SRESVIEW_H
#define SRESVIEW_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QFrame;
class QLabel;
class QProgressBar;
class QPushButton;
class QTextView;

class SResView : public QDialog
{ 
    Q_OBJECT

public:
    SResView( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SResView();

    QTextView* VolumeData;
    QFrame* LineSeparator;
    QLabel* currentDirFile;
    QProgressBar* aProgressBar;
    QLabel* rate;
    QPushButton* Stop;
    QPushButton* Cancel;


public slots:
    virtual void cancel_slot();
    virtual void stop_resume_slot();

protected:
    QVBoxLayout* Layout8;
    QHBoxLayout* Layout7;
    QHBoxLayout* Layout5;
    QHBoxLayout* Layout2;
};

#endif // SRESVIEW_H
