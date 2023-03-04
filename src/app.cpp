#include <QtCore/QCoreApplication>
#include <QtWidgets/QtWidgets>

int main( int argc, char **argv ){
    QApplication a(argc, argv);
    QWidget window;

    window.resize(320,240);
    window.show();

    return a.exec();
}