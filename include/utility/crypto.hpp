//====================================================
//     File data
//====================================================
/**
 * @file crypto.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-13
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_CRYPTO_UTILITY
#define KEY_MANAGER_CRYPTO_UTILITY

//====================================================
//     Headers
//====================================================

// STD
#include <string>
#include <string_view>
#include <cstdint>

namespace kmanager::utility{

    //====================================================
    //     Headers
    //====================================================
    /**
     * @brief Basic class used to manage encryption and decryption of a string.
     * 
     */
    class Crypto{

        //====================================================
        //     public
        //====================================================
        public:

            // Constructors / destructor
            Crypto( std::string_view message, std::string_view key );
            Crypto( std::string_view message );
            ~Crypto();

            // Methods
            std::string encrypt();
            std::string decrypt();
            void clear();

            // Getters
            std::string_view getMessage() const;
            std::string_view getKey() const;

            // Setters
            void setMessage( std::string_view message );
            void setKey( std::string_view key );

        //====================================================
        //     private
        //====================================================
        private:

            // Methods
            std::string generateRandomKey( int64_t length );

            // Members
            std::string message;
            std::string key;
    };
}

#endif