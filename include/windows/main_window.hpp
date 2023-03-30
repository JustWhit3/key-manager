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

// Qt
#include <QtWidgets>
#include <QStateMachine>
#include <QObject>

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
            void buttonsPressedActions();

            // Variables (states)
            QSharedPointer<QStateMachine> state_machine;
            QSharedPointer<state::MenuState> menu_state;
            QSharedPointer<state::PasswordManagerState> p_manager_state;

        //====================================================
        //     Private slots
        //====================================================
        private slots:
        
            // Methods
            void hidePasswordManagerWidgets();
            void hideMenuStateWidgets();
    };
}

#endif