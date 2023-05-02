//====================================================
//     File data
//====================================================
/**
 * @file password_actions.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-01
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_ACTIONS_WIDGET
#define KEY_MANAGER_PASSWORD_ACTIONS_WIDGET

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/base_widget.hpp>

// Qt
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSharedPointer>
#include <QIcon>
#include <QSize>

namespace kmanager::widget{

    //====================================================
    //     PasswordActions
    //====================================================
    /**
     * @brief Class used to construct a password actions widget.
     * 
     */
    class PasswordActions: public BaseWidget{

        // Qt macros
        Q_OBJECT

        //====================================================
        //     public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordActions( QWidget* parent = nullptr );
            ~PasswordActions();

            // Methods
            void initWidgetProperties() override;

        //====================================================
        //     private
        //====================================================
        private:

            // Variables
            QSharedPointer<QHBoxLayout> layout;
            QSharedPointer<QPushButton> delete_password;
            QSharedPointer<QPushButton> save_password;

            // Constants
            const QSize icon_size = QSize( 23.f, 23.f );

        //====================================================
        //     private slots
        //====================================================
        private slots:

            // Methods
            // ...
    };
}

#endif