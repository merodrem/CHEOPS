#include "downloader.h"

Downloader::Downloader(QUrl url, QObject *parent):
    QObject(parent)
{
    QNetworkRequest request(url);
    webCtrl = new QNetworkAccessManager(this);
    download = webCtrl->get(request);
}

QNetworkReply* Downloader::getReply() const
{
    return download;
}

QNetworkAccessManager* Downloader::getManager() const
{
    return webCtrl;
}

void Downloader::storeData()
{

    QString line = QString(download->readLine());


    while (line != "END\r\n")
    {
        QStringList temp = line.split(" = ");
        headers[temp.at(0)] = temp.at(1);
      //  std::cout << temp.at(0).toStdString() << "||" << temp.at(1).toStdString() << std::endl;
        line = QString(download->readLine());

    }

    int blockSize = headers["LINE_SAMPLES"].toInt();


    while (download->size() > (blockSize*(headers["LINES"].toInt())))
    {
            download->read(1);
    }

    long nbElements = headers["LINE_SAMPLES"].toInt() * headers["LINES"].toInt();
    payload = std::valarray<int>(nbElements);

    for ( int i = 0 ; i < nbElements ; ++i)
    {
            payload[i] = download->read(1).at(0);
    }


}

void Downloader::convert(QString filename)
{

    long naxis    =   2;
    long naxes[2] = { headers["LINE_SAMPLES"].toInt(), headers["LINES"].toInt() };


    // declare auto-pointer to FITS at function scope. Ensures no resources
    // leaked if something fails in dynamic allocation.
    std::auto_ptr<FITS> pFits(0);



    pFits.reset( new FITS(filename.toStdString() , BYTE_IMG , naxis , naxes ) );


    PHDU &hdu = pFits->pHDU();

    QMessageBox::information(0, "Conversion completed", "Conversion to FITS successful");

    long  fpixel(1);
    hdu.write(fpixel,payload.size(),payload);




}
