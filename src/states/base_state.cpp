//====================================================
//     File data
//====================================================
/**
 * @file base_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/base_state.hpp>

// Qt
#include <QStateMachine>

namespace kmanager::state{

    //====================================================
    //     BaseState (default constructor)
    //====================================================
    /**
     * @brief Construct a new BaseState object.
     * 
     * @param parent The parent state (if there is one).
     */
    BaseState::BaseState( QState *parent ): 
        QState( parent ){

        // Define the key file
        #ifdef _WIN32
            this -> key_file << "C:\\Users\\" 
                                 << this -> username 
                                 << "\\.key-manager_files\\.key";
        #else
            this -> key_file << "/home/" 
                                 << this -> username 
                                 << "/.key-manager_files/.key";
        #endif
    }

    //====================================================
    //     BaseState (destructor)
    //====================================================
    /**
     * @brief Destruct a new BaseState object.
     * 
     */
    BaseState::~BaseState(){
    
    }
}