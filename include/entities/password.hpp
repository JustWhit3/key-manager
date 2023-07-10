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

// STD
#include <map>
#include <string>

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

            //====================================================
            //     retrieveInfo
            //====================================================
            /**
             * @brief Retrieve basic information about the password. Useful in order to pass information without requiring to pass the entire object.
             * 
             * @return const std::map<std::string, std::string> the vector of password information.
             */
            const std::map<std::string, std::string> retrieveInfo() const {
                return {
                    { "password", this -> password_str -> text().toStdString() },
                    { "platform", this -> platform -> text().toStdString() } ,
                    { "username", this -> username -> text().toStdString() }
                };
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