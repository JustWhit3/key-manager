//====================================================
//     File data
//====================================================
/**
 * @file password_toggle.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-04-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_TOGGLE_WIDGET
#define KEY_MANAGER_PASSWORD_TOGGLE_WIDGET

//====================================================
//     Headers
//====================================================

// Qt
#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>

namespace kmanager::widget{

    //====================================================
    //     PasswordToggleWidget
    //====================================================
    /**
     * @brief Class used to construct a password toggle widget.
     * 
     */
    class PasswordToggle: public QWidget{

        // Qt macros
        Q_OBJECT

        //====================================================
        //     public
        //====================================================
        public:

            // Constructors / destructor
            PasswordToggle( QWidget* parent = nullptr );
            ~PasswordToggle();

            // Methods
            void initWidgetProperties();

            // Variables
            QLineEdit* password_label;
        
        //====================================================
        //     private
        //====================================================
        private:

            // Variables
            QHBoxLayout* layout;
            QCheckBox* checkbox;

        //====================================================
        //     private slots
        //====================================================
        private slots:

            // Methods
            void changeToggleState();
    };
}

#endif