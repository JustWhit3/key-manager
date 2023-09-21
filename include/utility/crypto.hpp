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
#include <cstdint>
#include <string>
#include <string_view>

namespace kmanager::utility {

    //====================================================
    //     Headers
    //====================================================
    /**
     * @brief Basic class used to manage encryption and decryption of a string.
     *
     */
    class Crypto {
        public:

            // Constructors / destructor
            explicit Crypto(std::string_view message, std::string_view key);
            explicit Crypto(std::string_view message);
            ~Crypto();

            // Methods
            std::string encrypt();
            std::string decrypt();
            void clear();

            // Getters
            std::string getMessage() const;
            std::string getKey() const;

            // Setters
            void setMessage(std::string_view message);
            void setKey(std::string_view key);

        private:

            // Methods
            std::string generateRandomKey(int64_t length);

            // Members
            std::string message;
            std::string key;
    };
}  // namespace kmanager::utility

#endif