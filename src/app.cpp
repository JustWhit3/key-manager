//====================================================
//     File data
//====================================================
/**
 * @file app.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-06
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/main_window.hpp>

// Qt
#include <QApplication>
#include <QFile>
#include <QString>
#include <QIODeviceBase>
#include <QByteArray>

//====================================================
//     Main
//====================================================
int main( int argc, char **argv ){

    // Create the app
    QApplication app( argc, argv );

    // Set the app theme
    QFile theme_file( "themes/Obit.qss" );
    theme_file.open( QFile::ReadOnly );
    QString theme = QLatin1String( theme_file.readAll() );
    app.setStyleSheet( theme );

    // Run the main window
    auto MainWindow{ kmanager::window::MainWindow() };
    MainWindow.show();

    // Run main loop
    return app.exec();
}