//====================================================
//     File data
//====================================================
/**
 * @file generic.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-07-20
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_GENERIC_UTILITY
#define KEY_MANAGER_GENERIC_UTILITY

//====================================================
//     Headers
//====================================================

// Qt
#include <QString>

namespace kmanager::utility{

    //====================================================
    //     Functions
    //====================================================
    extern QString copyToSystem( const QString& fileNameToCopy );
}

#endif