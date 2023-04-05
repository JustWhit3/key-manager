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
     * @brief Template class used to construct the password entity.
     * 
     */
    template <typename T>
    class Password{
    
        //====================================================
        //     public
        //====================================================
        public:

            //====================================================
            //     Password (constructor)
            //====================================================
            /**
             * @brief Construct a new Password object.
             * 
             */
            Password(){

            }

            //====================================================
            //     Password (destructor)
            //====================================================
            /**
             * @brief Destroy the Password object.
             * 
             */
            virtual ~Password(){

            }

            // Attributes
            T password_str;
            T platform;
            T username;
            T note;
    };
}

#endif