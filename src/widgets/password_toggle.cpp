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
#include <widgets/base_widget.hpp>
#include <widgets/password_toggle.hpp>

// Qt
#include <QWidget>
#include <QEvent>
#include <QEnterEvent>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
#include <QObject>

namespace kmanager::widget{

    //====================================================
    //     PasswordToggle (constructor)
    //====================================================
    /**
     * @brief Construct a new Password Toggle object.
     * 
     * @param parent 
     */
    PasswordToggle::PasswordToggle( bool styled, QWidget* parent ):
        styled( styled ),
        BaseWidget( parent ){
                    
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

        // Setup layout
        this -> layout = new QGridLayout( this );
        this -> layout -> addWidget( password_label, 0, 0 );
        this -> layout -> setContentsMargins( 0, 0, 0, 0 );
        this -> setLayout( layout );

        // Setup checkbox
        this -> checkbox = new QCheckBox( this );
        if( this -> styled == true ){
            this -> checkbox -> setStyleSheet( 
                "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
                "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
                "QCheckBox::indicator { width: 25px; height: 25px; }"
            );
            this -> checkbox -> setFixedSize( 25, 25 );
            this -> checkbox -> move( 220.f, 6.f );
        }
        else{
            this -> checkbox -> setStyleSheet( 
                "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
                "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
                "QCheckBox::indicator { width: 35px; height: 35px; background-color: #38394e; }"
            );
            this -> checkbox -> setFixedSize( 35, 35 );
            this -> checkbox -> move( 340.f, 7.f );
        }

        QObject::connect( 
             this -> checkbox, 
             SIGNAL( clicked() ), 
             this, 
             SLOT( changeToggleState() ) 
        );
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

    //====================================================
    //     enterEvent
    //====================================================
    /**
     * @brief Override the enterEvent widget function.
     * 
     * @param event Event triggered when mouse enter the widget.
     */
    void PasswordToggle::enterEvent( QEnterEvent* event ){
        if( styled == true ){
            this -> setStyleSheet( this -> hover_settings );
        }
        event -> accept();
    }

    //====================================================
    //     enterEvent
    //====================================================
    /**
     * @brief Override the leaveEvent widget function.
     * 
     * @param event Event triggered when mouse leave the widget.
     */
    void PasswordToggle::leaveEvent( QEvent* event ){
        if( styled == true ){
            this -> setStyleSheet( this -> default_settings );
        }
        event -> accept();
    }
}