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
#include <string>
#include <string_view>
#include <unistd.h>
#include <ctime>

namespace kmanager::utility{

    //====================================================
    //     Static constants
    //====================================================
    const char Crypto::alpha_num[] =
        "0123456789" 
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" 
        "abcdefghijklmnopqrstuvwxyz";

    //====================================================
    //     Crypto (parametric constructor)
    //====================================================
    /**
     * @brief Construct a new Crypto object, by using a default input key.
     * 
     */
    Crypto::Crypto( std::string_view message, std::string_view key ): 
        message( message ),
        key( key ){

    }

    //====================================================
    //     Crypto (parametric constructor)
    //====================================================
    /**
     * @brief Construct a new Crypto object, by using a random key of lenght 100.
     * 
     */
    Crypto::Crypto( std::string_view message ): 
        message( message ){

        // Generate random key
        this -> key = this -> generateRandomKey( 100 );

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
     * @brief Change value of the "message" variable.
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
     * @brief Change value of the "key" variable.
     * 
     * @param message The new value of the "key" variable.
     */
    void Crypto::setKey( std::string_view key ){
        this -> key = key;
    }

    //====================================================
    //     generateRandomKey
    //====================================================
    /**
     * @brief Generate a random alpha-numeric key of length "length".
     * 
     */
    std::string Crypto::generateRandomKey( int64_t length ){

        // Variables
        std::string result;
        result.reserve( length );

        // Change random seed
        srand( ( unsigned ) time( NULL ) * getpid() ); 

        // Generate random key
        for( int16_t i = 0; i < length; ++i ){
            result += this -> alpha_num[ rand() % ( sizeof( this -> alpha_num ) - 1 ) ];
        }

        return result;
    }
}