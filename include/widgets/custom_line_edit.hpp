//====================================================
//     File data
//====================================================
/**
 * @file custom_line_edit.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-02
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_CUSTOM_LINE_EDIT_WIDGET
#define KEY_MANAGER_CUSTOM_LINE_EDIT_WIDGET

//====================================================
//     Headers
//====================================================

// Qt
#include <QLineEdit>
#include <QEnterEvent>
#include <QString>

namespace kmanager::widget{

    //====================================================
    //     CustomQLineEdit
    //====================================================
    class CustomQLineEdit: public QLineEdit{

        //====================================================
        //     Public
        //====================================================
        public: 
        
            // Constructors / destructor
            explicit CustomQLineEdit( QWidget *parent = nullptr );
            ~CustomQLineEdit();

            // Variables
            CustomQLineEdit* first_widget;
            CustomQLineEdit* second_widget;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void enter();
            void leave();
            void enterEvent( QEnterEvent* event ) override;
            void leaveEvent( QEvent* event ) override;

            // Constants
            const QString default_settings{ 
                "background-color: rgba( 255, 255, 255, 0% ); padding: 8%;" 
            };
            const QString hover_settings{ 
                "background-color: rgba( 255, 255, 255, 0% ); padding: 8%; border-color: rgb(255, 255, 255);" 
            };
    };
}

#endif