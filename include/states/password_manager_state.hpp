//====================================================
//     File data
//====================================================
/**
 * @file password_manager_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_MANAGER_STATE
#define KEY_MANAGER_PASSWORD_MANAGER_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/add_password_window.hpp>

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>

// Qt
#include <QSharedPointer>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

namespace kmanager::state{

    //====================================================
    //     PasswordManagerState
    //====================================================
    /**
     * @brief Class used to construct the password manager state of the app.
     * 
     */
    class PasswordManagerState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordManagerState( MenuState* host, QState *parent = nullptr );
            ~PasswordManagerState();

            // Variables (widgets)
            QSharedPointer<QLabel> password_platform;
            QSharedPointer<QLabel> password_key;
            QSharedPointer<QLabel> password_username;
            QSharedPointer<QLabel> password_note;
            QSharedPointer<QPushButton> find_button;
            QSharedPointer<QPushButton> add_password_button;
            QSharedPointer<QPushButton> menu_button;
            QSharedPointer<QLineEdit> find_input;
            QSharedPointer<window::AddPasswordWindow> add_password_window;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            MenuState* host;
            QIcon add_password_icon;
            QIcon menu_icon;

            // Constants
            const int16_t label_width = this -> host -> host -> width() * 0.25f;
            const int16_t label_height = 50.f;
            const QString label_settings = "background-color : #4682b4; color: white; padding: 8%; font-size: 20px";

        //====================================================
        //     Private slots
        //====================================================
        private slots:

            // Methods
            void addPassword();
    };
}

#endif