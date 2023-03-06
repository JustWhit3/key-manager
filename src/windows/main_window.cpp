//====================================================
//     File data
//====================================================
/**
 * @file main_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-06
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Qt
#include <windows/main_window.hpp>

namespace kmanager::window{

    //====================================================
    //     MainWindow (default constructor)
    //====================================================
    /**
     * @brief Construct a new MainWindow object.
     * 
     * @param parent The parent widget (if there is one);
     */
    MainWindow::MainWindow( QWidget *parent ): QWidget( parent ){

        // Set basic window properties
        this -> setWindowTitle( "Key Manager" );
        this -> setWindowState( Qt::WindowMaximized );
        this -> windowHandle() -> setScreen( qApp -> screens()[0] );
        this -> setWindowIcon( QIcon( "img/icons/app_icon.png" ) );
    }

    //====================================================
    //     MainWindow (destructor)
    //====================================================
    /**
     * @brief Destruct a new MainWindow object.
     * 
     */
    MainWindow::~MainWindow(){

    }

    //====================================================
    //     keyPressEvent
    //====================================================
    /**
     * @brief Method used to set key commands for the window.
     * 
     */
    void MainWindow::keyPressEvent( QKeyEvent *event ){
        switch( event -> key() ){

            // ESC
            case Qt::Key_Escape:
                if( this -> isFullScreen() ) this -> showMaximized();
                else this -> close();
                break;
            
            // F11
            case Qt::Key_F11:
                this -> showFullScreen();
                break;

            // Default
            default:
                break;
        }
    }
}