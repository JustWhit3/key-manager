//====================================================
//     File data
//====================================================
/**
 * @file login_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_LOGIN_STATE
#define KEY_MANAGER_LOGIN_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QStateMachine>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>

// STD
#include <sstream>
#include <string>

namespace kmanager::state{

    //====================================================
    //     LoginState
    //====================================================
    /**
     * @brief Class used to construct the login state of the app.
     * 
     */
    class LoginState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit LoginState( QWidget* host, QState *parent = nullptr );
            ~LoginState();

            // Variables (widgets)
            QSharedPointer<QLineEdit> enter_password;
            QSharedPointer<QCheckBox> checkbox;
            QSharedPointer<QLabel> enter_password_label;
            QSharedPointer<QLabel> error_label;

            // Variables (other)
            QWidget* host;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            std::ostringstream login_key_file;

            // Constants
            const uint32_t width{ 270 };
            const uint32_t height{ 70 };

        //====================================================
        //     private slots
        //====================================================
        private slots:
            void changeToggleState();
            void login();

        //====================================================
        //     signals
        //====================================================
        signals:
            void login_successful( bool checked = false );
    };
}

#endif