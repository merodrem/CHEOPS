#include "filepanel.h"
#include <iostream>


FilePanel::FilePanel(const QString &address, QWidget *parent):
    QWidget(parent)
{
    this->resize(750, 150);
    url = address;
    downloader = new Downloader(url);
    fitsConvert = new QPushButton("convert to FITS");
    fitsConvert->setEnabled(false);
    progressbar = new QProgressBar();
    QGridLayout* layout = new QGridLayout;
    QLabel* title = new QLabel(address, this);
    QObject::connect(downloader->getReply(), SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateBar(qint64, qint64)));
    QObject::connect(downloader->getManager(), SIGNAL(finished(QNetworkReply*)), this, SLOT(downloaded()));





    layout->addWidget(title, 0, 0, 1, 2,Qt::AlignBottom);
    layout->addWidget(fitsConvert,1,0 );
    layout->addWidget(progressbar,1,1 );
    this->setLayout(layout);

}

void FilePanel::updateBar(qint64 downloaded, qint64 total)
{
    progressbar->setValue((100*downloaded)/total);
}

void FilePanel::downloaded()
{
    fitsConvert->setEnabled(true);
    downloader->storeData();
    QObject::connect(fitsConvert, SIGNAL(clicked()),this, SLOT(convertButtonClicked()));
}

void FilePanel::convertButtonClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "select a destination", "", "Images( *.fits *.fit)");

    if (QFile::exists(filename))
            QFile::remove(filename);
    downloader->convert(filename);
}


/*

 */
