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

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>

// Qt
#include <QStateMachine>
#include <QSharedPointer>
#include <QPushButton>

namespace kmanager::state{

    //====================================================
    //     PasswordManagerState
    //====================================================
    /**
     * @brief Class used to construct the password manager state of the app.
     * 
     */
    class PasswordManagerState: public BaseState{
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordManagerState( MenuState* host, QState *parent = nullptr );
            ~PasswordManagerState();

            // Variables (widgets)
            QSharedPointer<QPushButton> test;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            MenuState* host;
    };
}

#endif