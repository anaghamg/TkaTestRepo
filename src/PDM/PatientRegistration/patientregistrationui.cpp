/*
    File Name       : patientregistrationui.cpp
    Project Name    : VTPS
    Created         : 12-03-2024
    Description     : Source file for GUI implementation for
                      patient registration
    Author(s)       : Anagha M. Gandha
    Version Number  : v0.1
*/

#include "patientregistrationui.h"

PatientRegistrationUI::PatientRegistrationUI(QWidget *parent) : QWidget(parent)
{
    qDebug()<<"*********Start of PatientRegistrationUI ctor";

    //---------- Label ---------//
    QLabel *lblPatID = new QLabel("Patient ID");
    QLabel *lblPatName = new QLabel;//("Name *");
    lblPatName->setText("Name   <span style='color:red;'>  *</span>");
    QLabel *lblPatGender = new QLabel;//("Gender *");
    lblPatGender->setText("Gender  <span style='color:red;'>  *</span>");
    QLabel *lblPatAge = new QLabel("Age");
    lblPatAge->setText("Age   <span style='color:red;'>   *</span>");
    QLabel *lblpatDOB = new QLabel("Date of Birth");
    QLabel *lblPatAddress = new QLabel("Address");
    QLabel *lblRefPhysician = new QLabel("Referring Physician");
    QLabel *lblPatAadhar = new QLabel("Aadhaar");

    QVBoxLayout* lblLayout = new QVBoxLayout;
    lblLayout->addWidget(lblPatName);
    lblLayout->addWidget(lblPatGender);
    lblLayout->addWidget(lblPatAge);
    lblLayout->addWidget(lblpatDOB);
    lblLayout->addWidget(lblPatID);
    lblLayout->addWidget(lblPatAddress);
    lblLayout->addWidget(lblRefPhysician);
    lblLayout->addWidget(lblPatAadhar);

    QWidget *lblWidget = new QWidget;
    lblWidget->setLayout(lblLayout);

    //---------- LineEdit ---------//

    m_qplineEditPatID = new QLineEdit;
    m_qplineEditPatID->setClearButtonEnabled(true);
    m_qplineEditPatID->setPlaceholderText("6 digit PatientID");
//    qDebug()<<"patID length"<<m_qplineEditPatID->text().length();
    // Create a QIntValidator to accept only integers
    validator = new QIntValidator;
    validator->setRange(999000, 999999);
    m_qplineEditPatID->setValidator(validator);

    m_qplineEditPatName = new QLineEdit;
    m_qplineEditPatName->setClearButtonEnabled(true);
    m_qplineEditPatName->setPlaceholderText("Enter patient name");

    m_qpcboxGender = new QComboBox;
    m_qpcboxGender->addItem(tr("Select"));
    m_qpcboxGender->addItem(tr("Male"));
    m_qpcboxGender->addItem(tr("Female"));
    m_qpcboxGender->addItem(tr("Others"));

    //added on 11-07-2024 //not tested
//    QPalette p = m_qpcboxGender->palette();
//    p.setColor(QPalette::HighlightedText, QColor(Qt::red));
//    p.setColor(QPalette::Highlight, QColor(Qt::green));
    //m_qpcboxGender->setPalette(p);

    m_qpwDob= new QCalendarWidget;
    m_qpwDob->setFirstDayOfWeek(Qt::Sunday);


    //works
//    QTableView *view = m_qpwDob->findChild<QTableView*>("qt_calendar_calendarview");
//    if (view)
//    {
//        QPalette pal = view->palette();
//        pal.setColor(QPalette::Base, Qt::red);
//        pal.setColor(QPalette::AlternateBase, Qt::green);
//        view->setPalette(pal);
//    }

    //   widgetDob->setDateRange(QDate(1900,01,01), QDate::currentDate());
    m_qpwDob->setMinimumDate(QDate(1900,01,01));
    m_qpwDob->setMaximumDate(QDate::currentDate());
    m_qpwDob->setHidden(true);
    m_qpwDob->setVisible(false);
    m_qpwDob->showSelectedDate();
    m_qpwDob->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_qpwDob->setCursor(Qt::PointingHandCursor);
    m_qpwDob->clicked(QDate::currentDate());
    QPushButton*  btnPatDOB = new QPushButton();
    btnPatDOB->setIcon(QIcon(":/res/icons/calendar.png"));
    connect(btnPatDOB, &QPushButton::clicked,m_qpwDob, &QCalendarWidget::show);

    m_qplineEditPatDob = new QLineEdit;
    m_qplineEditPatDob->setPlaceholderText("DOB");
    QHBoxLayout *dobLayout = new QHBoxLayout;
    dobLayout->addWidget(m_qplineEditPatDob,60);
    dobLayout->addWidget(btnPatDOB,40);  //calender popup appears

    m_qplineEditPatAge = new QLineEdit;
    m_qplineEditPatAge->setClearButtonEnabled(true);
    m_qplineEditPatAge->setPlaceholderText("Age");

    QIntValidator * ageValidator = new QIntValidator;
    ageValidator->setRange(0, 120);
    m_qplineEditPatAge->setValidator(ageValidator);

    m_qplineEditPatAddress = new QLineEdit;
    m_qplineEditPatAddress->setClearButtonEnabled(true);
    m_qplineEditPatAddress->setPlaceholderText("Address");
    m_qplineEditRefPhysician = new QLineEdit;
    m_qplineEditRefPhysician->setClearButtonEnabled(true);
    m_qplineEditRefPhysician->setPlaceholderText("Referring Physician");

    m_qplineEditPatAadhar = new QLineEdit;
    m_qplineEditPatAadhar->setClearButtonEnabled(true);
    m_qplineEditPatAadhar->setValidator(new QRegExpValidator(QRegExp("[0-9]*"), m_qplineEditPatAadhar));
    m_qplineEditPatAadhar->setPlaceholderText("12 digit aadhaar number");
    m_qplineEditPatAadhar->setMaxLength(12);

    QVBoxLayout* lineLayout = new QVBoxLayout();
    lineLayout->addWidget(m_qplineEditPatName);
    lineLayout->addWidget(m_qpcboxGender);
    lineLayout->addWidget(m_qplineEditPatAge);
    lineLayout->addLayout(dobLayout);
    lineLayout->addWidget(m_qplineEditPatID);
    lineLayout->addWidget(m_qplineEditPatAddress);
    lineLayout->addWidget(m_qplineEditRefPhysician);
    lineLayout->addWidget(m_qplineEditPatAadhar);

    QWidget* lineEditWidget = new QWidget;
    lineEditWidget->setLayout(lineLayout);

    QHBoxLayout* topLayout = new QHBoxLayout;
    topLayout->addStretch(15);
    topLayout->addWidget(lblWidget);
    topLayout->addWidget(lineEditWidget);
    topLayout->addStretch(15);
    QWidget* topWidget = new QWidget;
    topWidget->setLayout(topLayout);

    //---------- Buttons ---------//
    m_qpbSave= new QPushButton("SAVE");
    m_qpbClear = new QPushButton("CLEAR");
    m_qpbUpdate = new QPushButton("UPDATE");
    m_qpbUpdate->setDisabled(true);

    m_qpbSave->setObjectName("patsaveclearupdate");
    m_qpbClear->setObjectName("patsaveclearupdate");
    m_qpbUpdate->setObjectName("patsaveclearupdate");
    m_qpbSave->setCheckable(true);
    m_qpbClear->setCheckable(true);
    m_qpbUpdate->setCheckable(true);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(m_qpbSave);
    btnLayout->addWidget(m_qpbClear);
    btnLayout->addWidget(m_qpbUpdate);
    btnLayout->setAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
    QWidget* btnWidget = new QWidget;
    btnWidget->setLayout(btnLayout);

    m_qpbNewReg = new QPushButton("New Registration");
    m_qpbNewReg->setObjectName("newpatreg");
    m_qpbNewReg->setEnabled(true);
    m_qpbNewReg->setCheckable(true);

    QHBoxLayout* qhblNewReg = new QHBoxLayout;
    qhblNewReg->addWidget(m_qpbNewReg);
    QWidget* qwNewReg = new QWidget;
    qwNewReg->setLayout(qhblNewReg);

    m_qpbNext = new QPushButton("Next");
    m_qpbNext->setObjectName("backnextButton");

    QVBoxLayout* newbtnLayout = new QVBoxLayout();
    newbtnLayout->addWidget(btnWidget);
    newbtnLayout->addWidget(qwNewReg);
    newbtnLayout->addWidget(m_qpbNext);
    QWidget* newbtnWidget = new QWidget;
    newbtnWidget->setLayout(newbtnLayout);

    //------ Main Page Layout -----//
    m_qpMainLayout = new QVBoxLayout;
    m_qpMainLayout->addWidget(topWidget,40);
    m_qpMainLayout->addWidget(newbtnWidget,20); //
    m_qpMainLayout->addStretch(7);

    QFrame* frame_patientreg = new QFrame;
    frame_patientreg->setLayout(m_qpMainLayout);
    frame_patientreg->setObjectName("frame_patientreg");
    frame_patientreg->setFixedWidth(480);

    QVBoxLayout* qvblframepatreg = new QVBoxLayout;
    qvblframepatreg->addWidget(frame_patientreg);
    this->setLayout(qvblframepatreg);

    m_qplineEditPatDob->setReadOnly(true);

    connect(m_qpbSave, &QPushButton::clicked,
            this, &PatientRegistrationUI::saveToDB);

    connect(m_qpbClear, &QPushButton::clicked,
            this, &PatientRegistrationUI::ClearAllFields);

    connect(m_qpwDob, &QCalendarWidget::selectionChanged,
            this, &PatientRegistrationUI::CalculateAge);

    connect(m_qplineEditPatAge, &QLineEdit::editingFinished,
            this, &PatientRegistrationUI::SetDobFromAge);

    //added on 21-06-2024
    connect(m_qplineEditPatName, &QLineEdit::textChanged, this, &PatientRegistrationUI::validateInput);

    connect(m_qplineEditRefPhysician, &QLineEdit::textChanged, this, &PatientRegistrationUI::validateInputPhysician);

    //added on 11-07-2024
    connect(m_qplineEditPatAge, &QLineEdit::textEdited, this, &PatientRegistrationUI::validateAge);
//    connect(m_qplineEditPatAge, &QLineEdit::textChanged, this, &PatientRegistrationUI::validateAge);

    connect(m_qplineEditPatAddress, &QLineEdit::textChanged, this, &PatientRegistrationUI::validateAddress);

    connect(m_qpbUpdate, &QPushButton::clicked,
            this, &PatientRegistrationUI::UpdateFromLineEdit);

    //new reg
    connect(m_qpbNewReg, &QPushButton::clicked,
            this, &PatientRegistrationUI::NewRegistration);

    qDebug()<<"*********End of PatientRegistration ctor";

}

void PatientRegistrationUI::ClearAllFields()
{
   qDebug()<<"Clear all data ";


   //m_bClearedDetails = true;
//   qDebug()<<"Bool clear 1"<<m_bClearedDetails;


   m_qplineEditPatID->clear();
   m_qplineEditPatName->clear();
   m_qpcboxGender->setCurrentText("Select");
   m_qplineEditPatAge->clear();
   m_qplineEditPatAddress->clear();
   m_qplineEditRefPhysician->clear();
   m_qplineEditPatDob->clear();
   m_qplineEditPatAadhar->clear();

//   m_bClearedDetails = true;
//   qDebug()<<"Bool clear 2"<<m_bClearedDetails;



}


//get patient details from gui and emit as qstringlist.
//This will be updated in the DB
void PatientRegistrationUI::SetPatientDetails(/*const*/ QStringList &qstrList)
{
    m_dbstrlist = qstrList;
    qDebug()<<"SetPatientDetails in patreg "<<m_dbstrlist;
    //    QMessageBox::information(this, "Saved", "Details saved successfully.");
    //QMessageBox::information(this, "Deleted|", "Entry deleted.");

    m_qpbSave->setDisabled(true);
    m_qpbClear->setDisabled(true);

    ClearAllFields(); //
    //EnableLineEdit(true);

    m_qplineEditPatID->setEnabled(false);
    m_qplineEditPatName->setEnabled(false);
    m_qpcboxGender->setEnabled(false);
    m_qplineEditPatAge->setEnabled(false);
    m_qpwDob->setEnabled(false);
    m_qplineEditPatAddress->setEnabled(false);
    m_qplineEditRefPhysician->setEnabled(false);
    m_qplineEditPatDob->setEnabled(false);
    m_qplineEditPatAadhar->setEnabled(false);

    m_qplineEditPatID->update();
    m_qplineEditPatName->update();
    m_qpcboxGender->update();
    m_qplineEditPatAge->update();
    m_qpwDob->update();
    m_qplineEditPatAddress->update();
    m_qplineEditRefPhysician->update();
    m_qplineEditPatDob->update();
    m_qplineEditPatAadhar->update();






    m_qpbNewReg->show();
    m_qpbNewReg->setEnabled(true);

    emit SendPatientDetails(m_dbstrlist);
    qDebug()<<"emitted strlist";
}

void PatientRegistrationUI::SetDBPatientID(QString id)
{
    qDebug()<<"SetDBPatientID";
    dbpatientID = id;
}

QStringList PatientRegistrationUI::GetPatientDetails() /*const*/
{
    qDebug()<<"GetPatientDetails in patreg"<<m_dbstrlist;
    return m_dbstrlist;
}

void PatientRegistrationUI::saveToDB()
{
   qDebug()<<"SaveToDB";
   QString strPatId= m_qplineEditPatID->text();
   QString strPatName= m_qplineEditPatName->text();
   QString strPatGender= m_qpcboxGender->currentText();
   if(strPatGender=="Select")
   {
        QMessageBox::warning(this, "Warning", "Please select gender.");
   }

   QString strPatientage = m_qplineEditPatAge->text();

   QString strPatDob= selectedDob.toString("dd-MM-yyyy");
   m_qpstrPatDob    = selectedDob.toString("dd-MM-yyyy");
   m_qplineEditPatDob->setText(selectedDob.toString("dd-MM-yyyy"));
   qDebug()<<"Selected DOB : "<<m_qpstrPatDob;//<<strPatDob; //<<selectedDob;

   QString strPatAddr= m_qplineEditPatAddress->text();
   QString strPhysician= m_qplineEditRefPhysician->text();
//   QString strPatUID= m_qplineEditPatUID->text();

   if(strPatId.length() <6 || strPatId.length() > 6)
   {
        QMessageBox::warning(this, "Warning", "Please enter valid 6 digit PatientID.");
   }

   QString strPatAadhar = m_qplineEditPatAadhar->text();

   qstrlstPatDetails.append(strPatId);
   qstrlstPatDetails.append(strPatName);
   qstrlstPatDetails.append(strPatGender);

   m_qpstrPatAge = m_qplineEditPatAge->text();
   qstrlstPatDetails.append(m_qpstrPatAge);

   //set date
   qDebug()<<"SetDobFromAge 1 ";
   int currentyear1= QDate::currentDate().year();
   int age1 = m_qpstrPatAge.toInt();

   qDebug()<<"Age entered by user1 :"<<age1<<" , Current year1"<<currentyear1;
   QDate calculatedDob1 = QDate(currentyear1 - age1, 1, 1);

   qDebug()<<"Calculated Dob1 "<<calculatedDob1;

   m_qplineEditPatDob->setText(calculatedDob1.toString("dd-MM-yyyy"));
   qDebug()<<"Display dob1 "<<m_qplineEditPatDob->text();
   m_qplineEditPatDob->update();

   QString qstrDob1 = m_qplineEditPatDob->text();
   qstrlstPatDetails.append(qstrDob1); //
   qstrlstPatDetails.append(strPatAddr);
   qstrlstPatDetails.append(strPhysician);
   qstrlstPatDetails.append(strPatAadhar);

   //QString dtTime = currentDateTime.toString("dd-MM-yyyy HH::mm::ss");
   //qstrlist.append(dtTime);

   qDebug()<<"Stringlist values in saveDB in PatientRegistrationUI :"<<qstrlstPatDetails;

   SetPatientDetails(qstrlstPatDetails);

   //clear stringlist
   qstrlstPatDetails.clear(); //
}

//added on 21-06-2024
void PatientRegistrationUI:: validateInput(const QString &text)
{
   //QRegularExpression regex("^[a-zA-Z ]*$");
    QRegularExpression regex("^[a-zA-Z ]{0,100}$"); //added //characer length limit

    if (!regex.match(text).hasMatch()) {
        QMessageBox::warning(this, "Warning", "Please enter a valid name.");
        QString validText;
        for (const QChar &ch1 : m_qplineEditPatName->text())
        {
            if (ch1.isLetter() || ch1 == ' ')
            {
                validText.append(ch1);
            }
            else
            {
                break;  // Stop appending if an invalid character is found
            }
        }
        m_qplineEditPatName->setText(validText);
    }
}

//added on 24-06-2024
void PatientRegistrationUI::validateInputPhysician(const QString &text)
{
    //    QRegularExpression regexRefPhy("^[a-zA-Z .]*$"); //character+singlespace+period
    QRegularExpression regexRefPhy("^[a-zA-Z .]{0,100}$"); //character+singlespace+period+character length limit

    if (!regexRefPhy.match(m_qplineEditRefPhysician->text()).hasMatch())
    {
        QMessageBox::warning(this, "Warning", "Please enter a valid name for Referring Physician.");
        QString validTextRefPhy;
          for (const QChar &ch1 : m_qplineEditRefPhysician->text())
          {
              if (ch1.isLetter() || ch1 == ' ')
              {
                  validTextRefPhy.append(ch1);
              }
              else
              {
                  break;  // Stop appending if an invalid character is found
              }
          }
          m_qplineEditRefPhysician->setText(validTextRefPhy);
    }
}

void PatientRegistrationUI::validateAge(const QString &text)
{
    qDebug()<<"validateAge";

    QString qstrAge = m_qplineEditPatAge->text();
    int iAge = qstrAge.toInt();
    qDebug()<<"Age"<<iAge;
    if(iAge > 120  || qstrAge != QString::number(iAge))
        // if (qstrAge.isEmpty() || iAge > 120 || qstrAge != QString::number(iAge))

    {
        qDebug()<<"Age o "<<iAge;
        QMessageBox::warning(this, "Warning", "Please enter a valid age.");
        m_qplineEditPatAge->clear();
    }
}

void PatientRegistrationUI::validateAddress(const QString &text)
{
    qDebug()<<"validateAddress";

    QRegularExpression regex("^[a-zA-Z0-9 ,\\-]{0,255}$");

     if (!regex.match(text).hasMatch()) {
         QMessageBox::warning(this, "Warning", "Please enter a valid address. Special characters like Period, Comma, Hyphen allowed.");
         QString validText;
         for (const QChar &ch1 : m_qplineEditPatAddress->text())
         {
             if (ch1.isLetter() || ch1 == ' ')
             {
                 validText.append(ch1);
             }
             else
             {
                 break;  // Stop appending if an invalid character is found
             }
         }
         m_qplineEditPatAddress->setText(validText);
     }
}

void PatientRegistrationUI::EnableNewReg()
{
    qDebug()<<"EnableNewReg";
    QMessageBox::information(this, "Updated", "Details Updated successfully.");

    m_qpbNewReg->show();
    m_qpbNewReg->setEnabled(true);

    ClearAllFields();
//    EnableLineEdit(true);

    m_qplineEditPatID->setEnabled(false);
    m_qplineEditPatName->setEnabled(false);
    m_qpcboxGender->setEnabled(false);
    m_qplineEditPatAge->setEnabled(false);
    m_qpwDob->setEnabled(false);
    m_qplineEditPatAddress->setEnabled(false);
    m_qplineEditRefPhysician->setEnabled(false);
    m_qplineEditPatDob->setEnabled(false);
    m_qplineEditPatAadhar->setEnabled(false);

    m_qplineEditPatID->update();
    m_qplineEditPatName->update();
    m_qpcboxGender->update();
    m_qplineEditPatAge->update();
    m_qpwDob->update();
    m_qplineEditPatAddress->update();
    m_qplineEditRefPhysician->update();
    m_qplineEditPatDob->update();
    m_qplineEditPatAadhar->update();
}

void PatientRegistrationUI::UpdateFromLineEdit()
{
     qDebug()<<"UpdateFromLineEdit";

     //update in db
     qstrlstUpdatePatientDetails.append(m_qplineEditPatID->text());
     qstrlstUpdatePatientDetails.append(m_qplineEditPatName->text());
     qstrlstUpdatePatientDetails.append(m_qpcboxGender->currentText());//
     qstrlstUpdatePatientDetails.append(m_qplineEditPatAge->text());
     qstrlstUpdatePatientDetails.append(m_qplineEditPatDob->text());
     qstrlstUpdatePatientDetails.append(m_qplineEditPatAddress->text());
     qstrlstUpdatePatientDetails.append(m_qplineEditRefPhysician->text());
     qstrlstUpdatePatientDetails.append(m_qplineEditPatAadhar->text());
     qDebug()<<"UpdateFromLineEdit 1";

     //update db ; update corresponding to patient id in table
     qDebug()<<"UpdateFromLineEdit dbpatientID"<<dbpatientID;

     qDebug()<<"UpdateFromLineEdit"<<qstrlstUpdatePatientDetails.at(0)<<qstrlstUpdatePatientDetails.at(6);

     emit  UpdatePatientDetails(dbpatientID,
                                qstrlstUpdatePatientDetails);


     m_qpbClear->setDisabled(true);
     m_qpbUpdate->setDisabled(true);



     qstrlstUpdatePatientDetails.clear();
     dbpatientID.clear();


//     if(m_bClearedDetails == true)
//     {
//         emit SignalClearEntry();
//     }

//     m_bClearedDetails = false;

     qDebug()<<"---------End of UpdateFromLineEdit";


}

void PatientRegistrationUI::NewRegistration()
{
    qDebug()<<"NewRegistration";

//    ClearAllFields();

    m_qpbSave->setEnabled(true);
    m_qpbClear->setEnabled(true);
    m_qpbUpdate->setEnabled(false);

    m_qplineEditPatID->setReadOnly(false);

    m_qplineEditPatID->setEnabled(true);
    m_qplineEditPatName->setEnabled(true);
    m_qpcboxGender->setEnabled(true);
    m_qplineEditPatAge->setEnabled(true);
    m_qpwDob->setEnabled(true);
    m_qplineEditPatAddress->setEnabled(true);
    m_qplineEditRefPhysician->setEnabled(true);
    m_qplineEditPatDob->setEnabled(true);
    m_qplineEditPatAadhar->setEnabled(true);

    m_qplineEditPatID->update();
    m_qplineEditPatName->update();
    m_qpcboxGender->update();
    m_qplineEditPatAge->update();
    m_qpwDob->update();
    m_qplineEditPatAddress->update();
    m_qplineEditRefPhysician->update();
    m_qplineEditPatDob->update();
    m_qplineEditPatAadhar->update();
}

void PatientRegistrationUI::CalculateAge()
{
   qDebug()<<"calculateAge";
   QDate currentDate = QDate::currentDate();
   selectedDob = m_qpwDob->selectedDate();
   int age = currentDate.year() - selectedDob.year();
   qDebug()<<"Age"<<age<<selectedDob.toString("dd-MM-yyyy");


//modified 05-08-2024

//   int months = currentDate.month() - selectedDob.month();

//       if (months < 12)
//       {
//           m_qplineEditPatAge->setText(QString::number(months) + " months");
//           qDebug()<<m_qplineEditPatAge->text();
//       }
//       else
//       {
//           int years = months / 12;
//           int remainingMonths = months % 12;
//           m_qplineEditPatAge->setText(QString::number(years) + " years " + QString::number(remainingMonths) + " months");
//           qDebug()<<m_qplineEditPatAge->text();

//       }



   m_qpstrPatAge= QString::number(age);
   m_qplineEditPatAge->setText(m_qpstrPatAge);
   m_qplineEditPatDob->setText(selectedDob.toString("dd-MM-yyyy"));

   qDebug()<<"CloseCalendarWdgt ";
   m_qpwDob->close();
}

void PatientRegistrationUI::SetDobFromAge(/*QString qstrAge*/)
{
    qDebug()<<"SetDobFromAge ";
    int currentyear = QDate::currentDate().year();    
    int age = m_qplineEditPatAge->text().toInt();
//    int age =m_qpstrPatAge.toInt();
//            m_qplineEditPatAge->text().toInt();

    qDebug()<<"Age entered by user :"<<age<<" , Current year"<<currentyear;
    QDate calculatedDob = QDate(currentyear - age, 1, 1);
    qDebug()<<"Calculated Dob "<<calculatedDob;
    m_qplineEditPatDob->setText(calculatedDob.toString("dd-MM-yyyy"));
    qDebug()<<"Display dob "<<m_qplineEditPatDob->text();
    m_qplineEditPatDob->update();

    //uncommented
//    QString qstrDob = m_qplineEditPatDob->text();
    m_qpstrPatDob = m_qplineEditPatDob->text();

 //   m_qpstrPatDob = m_qpwDob->selectedDate().toString("dd-MM-yyyy");
//            calculatedDob.toString("dd-MM-yyyy");


    qDebug()<<"Dob obtained from SetDobFromAge "<<m_qpstrPatDob;

}

void PatientRegistrationUI::EditPatientForm(QStringList qstrPatientReg)
{
    qDebug()<<"EditPatientForm in pat reg";

    m_qpbSave->setDisabled(true);
    m_qpbUpdate->setDisabled(false);
    m_qplineEditPatID->setReadOnly(true);
    m_qpbClear->setDisabled(false);


    ////////////////////
//    m_qplineEditPatID->setReadOnly(false); //

    m_qplineEditPatID->setEnabled(true);
    m_qplineEditPatName->setEnabled(true);
    m_qpcboxGender->setEnabled(true);
    m_qplineEditPatAge->setEnabled(true);
    m_qpwDob->setEnabled(true);
    m_qplineEditPatAddress->setEnabled(true);
    m_qplineEditRefPhysician->setEnabled(true);
    m_qplineEditPatDob->setEnabled(true);
    m_qplineEditPatAadhar->setEnabled(true);

    /////////////////////

    m_dbstrlistEdit = qstrPatientReg;
    qDebug()<<"str list"<<m_dbstrlistEdit;


    QString qstrdbpatientID = m_dbstrlistEdit.at(0);
    qDebug()<<"Details to be updated for ID :"<<qstrdbpatientID;

    SetDBPatientID(qstrdbpatientID);

    m_qplineEditPatID->setText(m_dbstrlistEdit.at(0));
    m_qplineEditPatName->setText(m_dbstrlistEdit.at(1));
    m_qpcboxGender->setCurrentText(m_dbstrlistEdit.at(2));
    m_qplineEditPatAge->setText(m_dbstrlistEdit.at(3));
    m_qplineEditPatDob->setText(m_dbstrlistEdit.at(4));
    m_qplineEditPatAddress->setText(m_dbstrlistEdit.at(5));
    m_qplineEditRefPhysician->setText(m_dbstrlistEdit.at(6));
    m_qplineEditPatAadhar->setText(m_dbstrlistEdit.at(7));
    qDebug()<<"EditPatientForm in pat reg 1";

    m_qplineEditPatID->update();
    m_qplineEditPatName->update();
    m_qpcboxGender->update();
    m_qplineEditPatAge->update();
    m_qplineEditPatDob->update();
    m_qplineEditPatAddress->update();
    m_qplineEditRefPhysician->update();
    m_qplineEditPatAadhar->update();

    m_dbstrlistEdit.clear();

    qDebug()<<"EditPatientForm in pat reg 2";
}
