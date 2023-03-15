//====================================================
//     File data
//====================================================
/**
 * @file custom_button.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-10
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_CUSTOM_BUTTON
#define KEY_MANAGER_CUSTOM_BUTTON

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QPushButton>
#include <QString>
#include <QFont>

namespace kmanager::widgets{

    //====================================================
    //     CustomButton
    //====================================================
    /**
     * @brief Class used to construct the custom button of the app.
     * 
     */
    class CustomButton: public QPushButton{
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit CustomButton( const QString &text, QWidget *parent = nullptr );
            ~CustomButton();

            // Methods
            void centering();
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Setters
            void setButtonProperties();

            // Variables
            QWidget *parent;
    };
}

#endif