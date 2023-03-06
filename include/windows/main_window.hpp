//====================================================
//     File data
//====================================================
/**
 * @file main_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-06
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_MAIN_WINDOW
#define KEY_MANAGER_MAIN_WINDOW

//====================================================
//     Headers
//====================================================

// Qt
#include <QtWidgets/QtWidgets>

namespace kmanager::window{

    //====================================================
    //     MainWindow
    //====================================================
    /**
     * @brief Class used to construct the main window of the app.
     * 
     */
    class MainWindow: public QWidget{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit MainWindow( QWidget *parent = nullptr );
            ~MainWindow();
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Qt macro
            Q_OBJECT

            // Methods
            void keyPressEvent( QKeyEvent *event ) override;
    };
}

#endif