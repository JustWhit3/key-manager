//====================================================
//     File data
//====================================================
/**
 * @file base_widget.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-01
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_BASE_WIDGET
#define KEY_MANAGER_BASE_WIDGET

//====================================================
//     Headers
//====================================================

// Qt
#include <QWidget>

namespace kmanager::widget{

    //====================================================
    //     BaseWidget
    //====================================================
    /**
     * @brief Class used to construct the base state of the app.
     * 
     */
    class BaseWidget: public QWidget{
    
        //====================================================
        //     protected
        //====================================================
        protected:

            // Constructors / destructor
            explicit BaseWidget( QWidget *parent = nullptr );
            virtual ~BaseWidget();

            // Methods
            virtual void initWidgetProperties() = 0;
    };
}

#endif