#include <QtWidgets>
#include "mainwindow.h"


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

    QCommandLineParser commandLineParser;
    commandLineParser.addPositionalArgument(QStringLiteral("url"),
        QStringLiteral("The url to be loaded in the browser window."));
    commandLineParser.process(app);
    QStringList positionalArguments = commandLineParser.positionalArguments();

    QUrl url("http://www.google.by");
    MainWindow browser(url);
    browser.show();
    if (browser.hideParam) {browser.hide();}
    return app.exec();
}
