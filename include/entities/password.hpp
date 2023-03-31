//====================================================
//     File data
//====================================================
/**
 * @file password.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_ENTITY
#define KEY_MANAGER_PASSWORD_ENTITY

//====================================================
//     Headers
//====================================================

// Qt
#include <QString>

namespace kmanager::entity{

    //====================================================
    //     Password
    //====================================================
    /**
     * @brief Class used to construct the password entity.
     * 
     */
    class Password{
    
        //====================================================
        //     public
        //====================================================
        public:

            // Constructors / destructor
            Password();
            virtual ~Password();

            // Methods
            void clear();

            // Attributes
            QString password_str;
            QString platform;
            QString username;
            QString note;
    };
}

#endif