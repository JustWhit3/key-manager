//====================================================
//     File data
//====================================================
/**
 * @file custom_label.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_CUSTOM_LABEL
#define KEY_MANAGER_CUSTOM_LABEL

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QLabel>
#include <QFont>

namespace kmanager::widgets{

    //====================================================
    //     CustomLabel
    //====================================================
    /**
     * @brief Class used to construct the custom label of the app.
     * 
     */
    class CustomLabel: public QLabel{
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit CustomLabel( QWidget *parent = nullptr );
            ~CustomLabel();
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Setters
            void setLabelProperties();
    };
}

#endif