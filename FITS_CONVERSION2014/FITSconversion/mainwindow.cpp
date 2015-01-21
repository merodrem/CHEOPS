#include "mainwindow.h"

MainWindow::MainWindow()
{
    this->setWindowTitle("FITS downloader and converter");
    this->resize(750, 0);

    QMenu *menuFile = menuBar()->addMenu("&File");
    QMenu *menuAbout = menuBar()->addMenu("?");

    QToolBar *toolBar = addToolBar("toolBar");


    QAction *newURL = menuFile->addAction("download from url...");
    newURL->setIcon(QIcon("data/download.png"));

    QAction *leave = menuFile->addAction("Quit");
    leave->setIcon(QIcon("data/quit.png"));

    QAction *about = menuAbout->addAction("about this project");
    about->setIcon(QIcon("data/about.png"));

    QAction *help = menuAbout->addAction("Help");
    help->setIcon(QIcon("data/help.png"));


    toolBar->addAction(newURL);
    toolBar->addAction(leave);

    centralZone = new QWidget;
    scrollArea = new QScrollArea;
    centralLayout = new QVBoxLayout;
    centralZone->setLayout(centralLayout);

    QObject::connect(newURL, SIGNAL(triggered()), this, SLOT(selectURL(void)));
    QObject::connect(leave, SIGNAL(triggered()), qApp, SLOT(quit()));

}


void MainWindow::addFilePanel(const QList<QString> &url)
{
    QListIterator<QString> it(url);

    while(it.hasNext())
    {   

        FilePanel *panel = new FilePanel(it.next());
        panels.append(panel);


    }

    this->setMaximumHeight(QWIDGETSIZE_MAX);
    centralZone = new QWidget;
    scrollArea = new QScrollArea;
    centralLayout = new QVBoxLayout;
    centralZone->setLayout(centralLayout);

    QListIterator<FilePanel*> it2(panels);
    while(it2.hasNext())
        centralLayout->addWidget(it2.next());
        this->resize(this->width(),this->height()+PANEL_SIZE);




    scrollArea->setWidget(centralZone);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameStyle(QFrame::NoFrame);
    centralZone->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setCentralWidget(scrollArea);

    int maxH = 0;
    QDesktopWidget screen;
    if (this->height() < screen.availableGeometry(screen.primaryScreen()).height())
        maxH = this->height();
    else
        maxH = screen.availableGeometry(screen.primaryScreen()).height();
    this->setMaximumHeight(maxH);
}

void MainWindow::selectURL(void)
{
    UrlSelectionWindow *sw = new UrlSelectionWindow(this);
    sw->show();
    QObject::connect(sw, SIGNAL(getUrls(QList<QString>)), this, SLOT(addFilePanel(QList<QString>)));

}

