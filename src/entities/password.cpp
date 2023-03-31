//====================================================
//     File data
//====================================================
/**
 * @file password.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Entities
#include <entities/password.hpp>

namespace kmanager::entity{

    //====================================================
    //     Password (default constructor)
    //====================================================
    /**
     * @brief Construct a new Password object.
     * 
     */
    Password::Password():
        password_str( "" ),
        username( "" ),
        platform( "" ),
        note( "" ){
            
    }

    //====================================================
    //     Password (destructor)
    //====================================================
    /**
     * @brief Destruct a new Password object.
     * 
     */
    Password::~Password(){
    
    }

    //====================================================
    //     clear
    //====================================================
    /**
     * @brief Clear all the class attributes
     * 
     */
    void Password::clear(){
        this -> password_str.clear();
        this -> username.clear();
        this -> note.clear();
        this -> platform.clear();
    }
}