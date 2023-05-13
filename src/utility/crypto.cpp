//====================================================
//     File data
//====================================================
/**
 * @file crypto.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-13
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Utility
#include <utility/crypto.hpp>

// STD
#include <string_view>

namespace kmanager::utility{

    //====================================================
    //     Crypto (default constructor)
    //====================================================
    /**
     * @brief Construct a new Crypto object.
     * 
     */
    Crypto::Crypto( std::string_view message, std::string_view key ): 
        message( message ),
        key( key ){

    }

    //====================================================
    //     Crypto (default constructor)
    //====================================================
    /**
     * @brief Destroy the Crypto object.
     * 
     */
    Crypto::~Crypto(){

    }

    //====================================================
    //     encrypt
    //====================================================
    /**
     * @brief Encrypt the "message" string using the "key" string.
     * 
     */
    std::string Crypto::encrypt(){

        // Case for empty key
        if( ! this -> key.size() ){
            return this -> message;
        }
            
        // Other cases
        for ( std::string::size_type i = 0; i < this -> message.size(); ++i ){
            this -> message[i] ^= this -> key[ i % this -> key.size() ];
        }
        return this -> message;
    }

    //====================================================
    //     encrypt
    //====================================================
    /**
     * @brief Decrypt the encrypted "message" string using the "key" string.
     * 
     */
    std::string Crypto::decrypt(){
        return this -> encrypt();
    }

    //====================================================
    //     clear
    //====================================================
    /**
     * @brief Clear the "message" and "key" strings.
     * 
     */
    void Crypto::clear(){
        this -> message.clear();
        this -> key.clear();
    }

    //====================================================
    //     getMessage
    //====================================================
    /**
     * @brief Return value of "message" variable.
     * 
     */
    std::string_view Crypto::getMessage() const {
        return this -> message;
    }    

    //====================================================
    //     getKey
    //====================================================
    /**
     * @brief Return value of "key" variable.
     * 
     */
    std::string_view Crypto::getKey() const {
        return this -> key;
    }

    //====================================================
    //     setMessage
    //====================================================
    /**
     * @brief CHange value of the "message" variable.
     * 
     * @param message The new value of the "message" variable.
     */
    void Crypto::setMessage( std::string_view message ){
        this -> message = message;
    }

    //====================================================
    //     setKey
    //====================================================
    /**
     * @brief CHange value of the "key" variable.
     * 
     * @param message The new value of the "key" variable.
     */
    void Crypto::setKey( std::string_view key ){
        this -> key = key;
    }
}