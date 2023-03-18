/****************************************************************************
** Form interface generated from reading ui file './SInitForm.ui'
**
** Created: Thu Jul 11 18:33:03 2002
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef SINITFORM_H
#define SINITFORM_H

#include <qvariant.h>
#include <qdialog.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class KIntNumInput;
class KLineEdit;
class QButtonGroup;
class QCheckBox;
class QGroupBox;
class QLabel;
class QPushButton;
class QRadioButton;

class SInitForm : public QDialog
{ 
    Q_OBJECT

public:
    SInitForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~SInitForm();

    QPushButton* StartButton;
    QPushButton* CloseButton;
    QGroupBox* OptionsLabels;
    QButtonGroup* RadioButtons;
    QRadioButton* Remote;
    QRadioButton* Local;
    KLineEdit* LE_Password;
    KLineEdit* LE_Device;
    KLineEdit* LE_Username;
    KLineEdit* LE_Socket;
    KIntNumInput* LE_Port;
    KLineEdit* LE_Database;
    QLabel* MntPoint;
    QLabel* Username;
    QLabel* Password;
    KLineEdit* LE_Server;
    QLabel* Server;
    QLabel* Port;
    QLabel* Device;
    QLabel* LocalSocket;
    KLineEdit* LE_MntPoint;
    QLabel* Database;
    QCheckBox* Eject;


public slots:
    virtual void closer_slot();
    virtual void local_slot();
    virtual void read_slot();
    virtual void remote_slot();

protected:
    QHBoxLayout* ButtonsLayout;
    QGridLayout* Layout5;
};

#endif // SINITFORM_H
