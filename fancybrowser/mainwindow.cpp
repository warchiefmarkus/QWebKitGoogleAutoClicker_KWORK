#include <QtWidgets>
#include <QtNetwork>
#include <QtWebKitWidgets>
#include "mainwindow.h"
#include <QTime>

void delay( int millisecondsToWait )
{
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}

MainWindow::MainWindow(const QUrl& url)
{
    settings = new QSettings(QDir::currentPath()+"/"+"settings.ini",QSettings::IniFormat);
    settings->setIniCodec("Windows-1251");
    request = settings->value("Settings/request").toString();

    qDebug() << QDir::currentPath()+"/"+"settings.ini" << settings->value("Settings/hide").toString();

    if(settings->value("Settings/hide").toString()=="true"){
        hideParam = true;
    }

    progress = 0;
    QNetworkProxyFactory::setUseSystemConfiguration(true);

    view = new QWebView(this);

    view->load(url);
    connect(view, SIGNAL(loadFinished(bool)), SLOT(adjustLocation()));
    connect(view, SIGNAL(titleChanged(QString)), SLOT(adjustTitle()));
    connect(view, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(view, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    locationEdit = new QLineEdit(this);
    locationEdit->setSizePolicy(QSizePolicy::Expanding, locationEdit->sizePolicy().verticalPolicy());
    connect(locationEdit, SIGNAL(returnPressed()), SLOT(changeLocation()));

    QToolBar *toolBar = addToolBar(tr("Navigation"));
    toolBar->addAction(view->pageAction(QWebPage::Back));
    toolBar->addAction(view->pageAction(QWebPage::Forward));
    toolBar->addAction(view->pageAction(QWebPage::Reload));
    toolBar->addAction(view->pageAction(QWebPage::Stop));
    toolBar->addWidget(locationEdit);

    setCentralWidget(view);
    setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow::adjustLocation()
{
    locationEdit->setText(view->url().toString());
}

void MainWindow::changeLocation()
{
    QUrl url = QUrl::fromUserInput(locationEdit->text());
    view->load(url);
    view->setFocus();
}

void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100)
        setWindowTitle(view->title());
    else
        setWindowTitle(QString("%1 (%2%)").arg(view->title()).arg(progress));
}

void MainWindow::setProgress(int p)
{
    progress = p;
    adjustTitle();
}

// LOADING FINISH
void MainWindow::finishLoading(bool)
{
    progress = 100;
    adjustTitle();
    // GOOGLE
    if (view->url().toString()=="http://www.google.by/"){
        qDebug() << " GOOGLE.BY ";

        QWebElement pass = view->page()->mainFrame()->documentElement().findFirst("input[name=q]");
        pass.setAttribute("value", request);
        view->page()->mainFrame()->evaluateJavaScript( "document.forms[0].submit();" );
    }
    // SEARCH RESULTS
     if (view->url().toString().contains("http://www.google.by/search")){
         qDebug() << " GOOGLE.BY/SEARCH ";
         view->page()->mainFrame()->evaluateJavaScript("window.scrollTo(0, document.body.scrollHeight);");
         delay(10000); // CHANGE SEC
         view->page()->mainFrame()->evaluateJavaScript("window.scrollTo(0, 0);");
         QWebElementCollection paragraphs = view->page()->mainFrame()->documentElement().findAll("div.g");
         qDebug() << paragraphs.at(2).findFirst("a").attribute("href");

         for (int i=0; i<paragraphs.toList().size(); i++){
             qDebug() << paragraphs.at(i).findFirst("a").attribute("href");
             if (paragraphs.at(i).findFirst("a").attribute("href").contains("kaminak.by")){
                 qDebug() << " CONTAINS " << (i+1);
                 paragraphs.at(i).findFirst("a").evaluateJavaScript("this.click();");// GO TO KAMINAK
                 return;
             }
        }
         // ELSE NEXT GOOGLE PAGE
        QWebElement button = view->page()->mainFrame()->documentElement().findFirst("#nav").findFirst("tr").findAll("td").last().findFirst("a");
        button.evaluateJavaScript("this.click();");
     }
     if (view->url().toString().contains("http://kaminak.by")){
         if(view->url().toString().contains("http://kaminak.by/category/aktsii/")){
             view->page()->mainFrame()->evaluateJavaScript("window.scrollTo(0, document.body.scrollHeight);");
             delay(120000);
             QCoreApplication::exit(0);
         }else{
             qDebug() << " KAMINAK.BY ";
             view->page()->mainFrame()->evaluateJavaScript("window.scrollTo(0, document.body.scrollHeight);");
             delay(60000);
             view->page()->mainFrame()->evaluateJavaScript("window.scrollTo(0, 0);");
             view->page()->mainFrame()->documentElement().findAll("a").at(10).evaluateJavaScript("this.click();");

         }
     }
}


