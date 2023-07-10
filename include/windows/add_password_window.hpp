//====================================================
//     File data
//====================================================
/**
 * @file add_password_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_ADD_PASSWORD_WINDOW
#define KEY_MANAGER_ADD_PASSWORD_WINDOW

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/base_window.hpp>

// States
#include <states/add_password_state.hpp>
#include <states/password_info_state.hpp>

// Qt
#include <QSharedPointer>

// STD
#include <map>
#include <string>

namespace kmanager::window{

    //====================================================
    //     AddPasswordWindow
    //====================================================
    /**
     * @brief Class used to construct the main window of the app.
     * 
     */
    class AddPasswordWindow: public BaseWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit AddPasswordWindow( int16_t window_height, std::map<std::string, std::string> info_map = {}, QWidget *parent = nullptr );
            ~AddPasswordWindow();
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void keyPressEvent( QKeyEvent *event ) override;
            void setWindowProperties() override;
            void initStateMachine() override;

            // Variables (states)
            QSharedPointer<QStateMachine> state_machine;
            QSharedPointer<state::AddPasswordState> add_password_state;
            QSharedPointer<state::PasswordInfoState> password_info_state;
            int16_t window_height;
            std::map<std::string, std::string> info_map;
    };
}

#endif