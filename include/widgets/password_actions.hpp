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
#include <widgets/custom_line_edit.hpp>

// Qt
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSharedPointer>
#include <QIcon>
#include <QSize>
#include <QString>

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

            // Variables
            QSharedPointer<QPushButton> delete_password;
            QSharedPointer<QPushButton> save_password;
            bool deleteMe;
            bool saveMySettings;
            CustomQLineEdit* first_widget;
            CustomQLineEdit* second_widget;
            CustomQLineEdit* third_widget;

        //====================================================
        //     private
        //====================================================
        private:

            // Variables
            void enterEvent( QEnterEvent* event ) override;
            void leaveEvent( QEvent* event ) override;

            // Variables
            QSharedPointer<QHBoxLayout> layout;

            // Constants
            const QSize icon_size = QSize( 23.f, 23.f );
            const QString default_settings{ 
                "background-color: rgba( 255, 255, 255, 0% ); padding: 8%;" 
            };
            const QString hover_settings{ 
                "background-color: rgba( 255, 255, 255, 0% ); padding: 8%; border-color: rgb(255, 255, 255);" 
            };

        //====================================================
        //     private slots
        //====================================================
        private slots:

            // Methods
            void setDeleteTrue();
            void setSaveMySettingsTrue();
    };
}

#endif