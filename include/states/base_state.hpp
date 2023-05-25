//====================================================
//     File data
//====================================================
/**
 * @file base_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_BASE_STATE
#define KEY_MANAGER_BASE_STATE

//====================================================
//     Headers
//====================================================

// Qt
#include <QState>

// STD
#include <sstream>
#include <cstdlib>
#include <string>

namespace kmanager::state{

    //====================================================
    //     BaseState
    //====================================================
    /**
     * @brief Class used to construct the base state of the app.
     * 
     */
    class BaseState: public QState{
    
        //====================================================
        //     protected
        //====================================================
        protected:

            // Constructors / destructor
            explicit BaseState( QState *parent = nullptr );
            virtual ~BaseState();

            // Methods
            virtual void addWidgets() = 0;
            virtual void assignProperties() = 0;

            // Variables
            std::ostringstream key_file;

            // Constants
            const std::string username{ std::getenv( "USERNAME" ) };
    };
}

#endif