//====================================================
//     File data
//====================================================
/**
 * @file custom_button.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-10
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <widgets/custom_button.hpp>

// Qt
#include <QPushButton>

namespace kmanager::widgets{

    //====================================================
    //     CustomButton (default constructor)
    //====================================================
    /**
     * @brief Construct a new CustomButton object.
     * 
     * @param text The text appearing on the button.
     * @param parent The parent state (if there is one).
     */
    CustomButton::CustomButton( const QString &text, QWidget *parent ): 
        QPushButton( text, parent ),
        parent( parent ){
        
        // Set basic button properties
        this -> setButtonProperties();
    }

    //====================================================
    //     CustomButton (destructor)
    //====================================================
    /**
     * @brief Destruct a CustomButton object.
     * 
     */
    CustomButton::~CustomButton(){

    }

    //====================================================
    //     setButtonProperties
    //====================================================
    /**
     * @brief Set basic button properties which are common among each button instance.
     * 
     */
    void CustomButton::setButtonProperties(){
        this -> setVisible( false );
        this -> setStyleSheet( "font-size: 20px" );
    }

    //====================================================
    //     centering
    //====================================================
    /**
     * @brief Center the button with respect to a given widgets which hosts the button itself.
     * 
     */
    void CustomButton::centering(){
        this -> move(
            this -> parent -> mapToGlobal( this -> parent -> geometry().center() ).x() - 
                this -> mapToGlobal( this -> geometry().center() ).x(),
            this -> parent -> mapToGlobal( this -> parent -> geometry().center() ).y() - 
                this -> mapToGlobal( this -> geometry().center() ).y()
        );
    }
}