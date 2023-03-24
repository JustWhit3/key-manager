//====================================================
//     File data
//====================================================
/**
 * @file add_password_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/add_password_state.hpp>

// Qt
#include <QStateMachine>
#include <QLabel>
#include <QSize>

namespace kmanager::state{

    //====================================================
    //     AddPasswordState (default constructor)
    //====================================================
    /**
     * @brief Construct a new AddPasswordState object.
     * 
     * @param parent The parent state (if there is one).
     */
    AddPasswordState::AddPasswordState( QWidget *host, QState *parent ): 
        BaseState( parent ),
        host( host ){
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     AddPasswordState (destructor)
    //====================================================
    /**
     * @brief Destruct a new AddPasswordState object.
     * 
     */
    AddPasswordState::~AddPasswordState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void AddPasswordState::addWidgets(){

        // Create new password label
        this -> create_new_password_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> create_new_password_label -> setVisible( false );
        this -> create_new_password_label -> setText( "Create a new password:" );
        this -> create_new_password_label ->  setStyleSheet( "font-size: 30px" );
        this -> create_new_password_label -> move(
            this -> create_new_password_label -> geometry().x() + 30.f,
            this -> create_new_password_label -> geometry().y() + 30.f
        );

        // Platform / website label
        this -> platform_website_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> platform_website_label -> setVisible( false );
        this -> platform_website_label -> resize( 220, 50 );
        this -> platform_website_label -> setText( "Platform / website:" );
        this -> platform_website_label ->  setStyleSheet( widget_font_size );
        this -> platform_website_label -> move(
            this -> platform_website_label -> geometry().x() + 30.f,
            this -> platform_website_label -> geometry().y() + 100.f
        );

        // Platform / website textbox
        this -> platform_website_textbox = QSharedPointer<QLineEdit>(
            new QLineEdit( this -> host )
        );
        this -> platform_website_textbox -> setVisible( false );
        this -> platform_website_textbox -> resize( 
            this -> platform_website_label -> geometry().width() * 1.75f,
            this -> platform_website_label -> geometry().height()
        );
        this -> platform_website_textbox ->  setStyleSheet( widget_font_size );
        this -> platform_website_textbox -> move(
            this -> platform_website_label -> geometry().x() + 200.f,
            this -> platform_website_label -> geometry().y()
        );

        // Username label

        // Username textbox

        // Password label

        // Password textbox

        // Note label

        // Note textbox
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void AddPasswordState::assignProperties(){

        // Labels
        this -> assignProperty( this -> create_new_password_label.get(), "visible", true );
        this -> assignProperty( this -> platform_website_label.get(), "visible", true );

        // Textbox
        this -> assignProperty( this -> platform_website_textbox.get(), "visible", true );
    }
}