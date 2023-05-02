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

// Widgets
#include <widgets/base_widget.hpp>

// Qt
#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QSharedPointer>

namespace kmanager::widget{

    //====================================================
    //     PasswordToggle
    //====================================================
    /**
     * @brief Class used to construct a password toggle widget.
     * 
     */
    class PasswordToggle: public BaseWidget{

        // Qt macros
        Q_OBJECT

        //====================================================
        //     public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordToggle( QWidget* parent = nullptr );
            ~PasswordToggle();

            // Methods
            void initWidgetProperties() override;

            // Variables
            QLineEdit* password_label;
        
        //====================================================
        //     private
        //====================================================
        private:

            // Methods
            void enterEvent( QEnterEvent* event ) override;
            void leaveEvent( QEvent* event ) override;

            // Variables
            QGridLayout* layout;
            QCheckBox* checkbox;

            // Constants
            const QString default_settings{ 
                "background-color: rgba( 255, 255, 255, 0% );" 
            };
            const QString hover_settings{ 
                "background-color: rgba( 255, 255, 255, 0% ); border-color: rgb(255, 255, 255);" 
            };

        //====================================================
        //     private slots
        //====================================================
        private slots:

            // Methods
            void changeToggleState();
    };
}

#endif