//====================================================
//     File data
//====================================================
/**
 * @file custom_label.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-15
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <widgets/custom_label.hpp>

// Qt
#include <QLabel>

namespace kmanager::widgets{

    //====================================================
    //     CustomLabel (default constructor)
    //====================================================
    /**
     * @brief Construct a new CustomLabel object.
     * 
     * @param parent The parent state (if there is one).
     */
    CustomLabel::CustomLabel( QWidget *parent ): 
        QLabel( parent ){
        
        // Set basic button properties
        this -> setLabelProperties();
    }

    //====================================================
    //     CustomLabel (destructor)
    //====================================================
    /**
     * @brief Destruct a CustomLabel object.
     * 
     */
    CustomLabel::~CustomLabel(){

    }

    //====================================================
    //     setLabelProperties
    //====================================================
    /**
     * @brief Set basic button properties which are common among each button instance.
     * 
     */
    void CustomLabel::setLabelProperties(){
        this -> setVisible( false );
    }
}