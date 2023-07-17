//====================================================
//     File data
//====================================================
/**
 * @file base_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/base_window.hpp>

// Qt
#include <QWidget>

namespace kmanager::window{

    //====================================================
    //     BaseWindow (default constructor)
    //====================================================
    /**
     * @brief Construct a new BaseWindow object.
     * 
     * @param parent The parent widget (if there is one).
     */
    BaseWindow::BaseWindow( QWidget *parent ): 
        QWidget( parent ){

    }

    //====================================================
    //     BaseWindow (destructor)
    //====================================================
    /**
     * @brief Destruct a new BaseWindow object.
     * 
     */
    BaseWindow::~BaseWindow(){

    }

    //====================================================
    //     setAnimation
    //====================================================
    /**
     * @brief Set animations of the window.
     * 
     */
    void BaseWindow::setAnimation(){

    }
}