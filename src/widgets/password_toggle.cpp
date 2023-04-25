//====================================================
//     File data
//====================================================
/**
 * @file password_toggle.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-04-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/password_toggle.hpp>

// Qt
#include <QWidget>

namespace kmanager::widget{

    //====================================================
    //     PasswordToggle (constructor)
    //====================================================
    /**
     * @brief Construct a new Password Toggle object.
     * 
     * @param parent 
     */
    PasswordToggle::PasswordToggle( QWidget* parent ):
                QWidget( parent ){

    }

    //====================================================
    //     PasswordToggle (destructor)
    //====================================================
    /**
     * @brief Destruct a new Password Toggle object.
     * 
     */
    PasswordToggle::~PasswordToggle(){

    }

    //====================================================
    //     initWidgetProperties
    //====================================================
    /**
     * @brief Initialize basic widgets properties.
     * 
     */
    void PasswordToggle::initWidgetProperties(){

        // Setup checkbox
        this -> checkbox = new QCheckBox();
        this -> checkbox -> setStyleSheet( 
            "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
            "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
            "QCheckBox::indicator { width: 25px; height: 25px; }"
        );

        QObject::connect( 
             this -> checkbox, 
             SIGNAL( clicked() ), 
             this, 
             SLOT( changeToggleState() ) 
        );

        // Setup layout
        this -> layout = new QHBoxLayout( this );
        this -> layout -> setSpacing( 5.f );
        this -> layout -> addWidget( checkbox );
        this -> layout -> addWidget( password_label );
        this -> setLayout( layout );
    }

    //====================================================
    //     changeToggleState
    //====================================================
    /**
     * @brief Slot used to change toggle state of password checkbox when clicked.
     * 
     */
    void PasswordToggle::changeToggleState(){
        this -> password_label -> setEchoMode(
            this -> checkbox->checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password 
        );
    }
}