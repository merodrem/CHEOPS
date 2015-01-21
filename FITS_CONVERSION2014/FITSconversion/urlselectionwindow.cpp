#include "urlselectionwindow.h"

UrlSelectionWindow::UrlSelectionWindow(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Select an url to download");
    this->resize(INIT_W, INIT_H);

    choice1 = new QRadioButton;
    choice1->setChecked(true);
    choice2 = new QRadioButton;

    imgUrl = new QLineEdit(choice1);
    QLineEdit *websiteFetch = new QLineEdit("NOT YET IMPLEMENTED", choice2);
    websiteFetch->setReadOnly(true);
    QLabel* label1 = new QLabel("Enter the path to the *.IMG to download:",choice1);
    QLabel* label2 = new QLabel("Try to fetch and download all *.IMG from this URL:", choice2);
    QPushButton *ok = new QPushButton("OK");
    QPushButton *cancel = new QPushButton("CANCEL");

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(choice1, 0, 0);
    mainLayout->addWidget(choice2, 1, 0);
    mainLayout->addWidget(label1,0,1);
    mainLayout->addWidget(label2,1,1);
    mainLayout->addWidget(imgUrl,0,2,1,2);
    mainLayout->addWidget(websiteFetch,1,2,1,2);
    mainLayout->addWidget(ok, 2, 1);
    mainLayout->addWidget(cancel, 2, 2);

    this->setLayout(mainLayout);

    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(ok, SIGNAL(clicked()), this, SLOT(setUrlList()));

}

void UrlSelectionWindow::setUrlList()
{
    if(choice1->isChecked())
    {
        urls.append(imgUrl->text());
    }
    this->accept();
    this->close();
    emit getUrls(urls);
}



