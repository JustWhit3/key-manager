//====================================================
//     File data
//====================================================
/**
 * @file menu_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_MENU_STATE
#define KEY_MANAGER_MENU_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Widgets
#include <widgets/custom_button.hpp>

// Qt
#include <QStateMachine>
#include <QSharedPointer>

namespace kmanager::state{

    //====================================================
    //     MenuState
    //====================================================
    /**
     * @brief Class used to construct the menu state of the app.
     * 
     */
    class MenuState: public BaseState{
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit MenuState( QWidget* host, QState *parent = nullptr );
            ~MenuState();

            // Variables (widgets)
            QSharedPointer<widgets::CustomButton> p_manager_button;

            // Variables (other)
            QWidget* host;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;
    };
}

#endif