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
#include <QtWidgets/QApplication>

//====================================================
//     Main
//====================================================
int main( int argc, char **argv ){

    // Create the app
    QApplication app( argc, argv );

    // Run the main window
    auto MainWindow{ kmanager::window::MainWindow() };
    MainWindow.show();

    // Run main loop
    return app.exec();
}