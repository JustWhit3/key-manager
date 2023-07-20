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

// Windows
#include <windows/base_window.hpp>

// States
#include <states/menu_state.hpp>
#include <states/password_manager_state.hpp>
#include <states/login_state.hpp>
#include <states/set_password_state.hpp>
#include <states/password_generator_state.hpp>

// Qt
#include <QWidget>
#include <QStateMachine>
#include <QObject>
#include <QSharedPointer>
#include <QPropertyAnimation>
#include <QEventTransition>
#include <QString>
#include <QFile>

namespace kmanager::window{

    //====================================================
    //     MainWindow
    //====================================================
    /**
     * @brief Class used to construct the main window of the app.
     * 
     */
    class MainWindow: public BaseWindow{

        // Macro for Qt
        Q_OBJECT

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

            // Methods
            void keyPressEvent( QKeyEvent *event ) override;
            void setWindowProperties() override;
            void initStateMachine() override;
            void closeEvent( QCloseEvent* event ) override;
            void buttonsPressedActions();
            void setAnimation() override;

            // Variables (states)
            QSharedPointer<QStateMachine> state_machine;
            QSharedPointer<state::MenuState> menu_state;
            QSharedPointer<state::PasswordManagerState> p_manager_state;
            QSharedPointer<state::LoginState> login_state;
            QSharedPointer<state::SetPasswordState> set_password_state;
            QSharedPointer<state::PasswordGeneratorState> p_generator_state;
            QSharedPointer<QPropertyAnimation> a_MenuState_PasswordManagerState;
            QSharedPointer<QPropertyAnimation> a_MenuState_PasswordGeneratorState;
            QSharedPointer<QPropertyAnimation> a_MenuState_Exit;
            QString login_key_file_path;
            QFile login_key_file;

        //====================================================
        //     Private slots
        //====================================================
        private slots:
        
            // Methods
            void MenuState_PasswordManagerState();
            void PasswordManagerState_MenuState();
            void LoginState_MenuState();
            void SetPasswordState_MenuState();
            void PasswordGeneratorState_MenuState();
    };
}

#endif