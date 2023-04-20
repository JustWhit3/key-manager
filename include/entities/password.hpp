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

            //====================================================
            //     Operator <
            //====================================================
            /**
             * @brief Operator overload to compare Password objects.
             * 
             * @param other The Password object to be compared with.
             * @return true If current Password object is smaller than the one used for comparison.
             * @return false Otherwise.
             */
            bool operator < ( const Password& other ) const {
                return std::make_tuple( password_str, platform, username, note ) < 
                       std::make_tuple( other.password_str, other.platform, other.username, other.note );
            }

            //====================================================
            //     Operator ==
            //====================================================
            /**
             * @brief Operator overload to compare Password objects.
             * 
             * @param other The Password object to be compared with.
             * @return true If current Password object is qual to the one used for comparison.
             * @return false Otherwise.
             */
            bool operator == ( const Password& other ) const {
                return std::make_tuple( password_str, platform, username, note ) == 
                       std::make_tuple( other.password_str, other.platform, other.username, other.note );
            }

            // Attributes
            T password_str;
            T platform;
            T username;
            T note;
            QWidget* password_toggle;
    };
}

#endif