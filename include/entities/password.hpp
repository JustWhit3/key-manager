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

// Widgets
#include <widgets/password_actions.hpp>
#include <widgets/password_toggle.hpp>

// Qt
#include <QString>
#include <QCheckBox>
#include <QLayout>

namespace kmanager::entity{

    //====================================================
    //     Password
    //====================================================
    /**
     * @brief Template class used to construct the password entity.
     * 
     */
    template <typename T>
    class Password {
    
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
            widget::PasswordToggle* password_toggle;
            widget::PasswordActions* actions;
    };
}

#endif