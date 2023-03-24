//====================================================
//     File data
//====================================================
/**
 * @file base_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_BASE_WINDOW
#define KEY_MANAGER_BASE_WINDOW

//====================================================
//     Headers
//====================================================

// Qt
#include <QtWidgets>

namespace kmanager::window{

    //====================================================
    //     BaseWindow
    //====================================================
    /**
     * @brief Class used to construct the base window of the app.
     * 
     */
    class BaseWindow: public QWidget{
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Constructors / destructor
            explicit BaseWindow( QWidget *parent = nullptr );
            virtual ~BaseWindow();

            // Pure methods
            virtual void setWindowProperties() = 0;
            virtual void initStateMachine() = 0;
    };
}

#endif