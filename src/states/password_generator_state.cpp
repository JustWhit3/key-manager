//====================================================
//     File data
//====================================================
/**
 * @file password_generator_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-28
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/menu_state.hpp>
#include <states/password_generator_state.hpp>

// Qt
#include <QSharedPointer>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>

namespace kmanager::state{

    //====================================================
    //     password_generator_state (default constructor)
    //====================================================
    /**
     * @brief Construct a new PasswordGeneratorState object.
     * 
     * @param host The state hosting the password generator.
     * @param parent The parent state (if there is one).
     */
    PasswordGeneratorState::PasswordGeneratorState( MenuState *host, QState *parent ): 
        BaseState( parent ),
        host( host ){
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     PasswordGeneratorState (destructor)
    //====================================================
    /**
     * @brief Destruct a new PasswordGeneratorState object.
     * 
     */
    PasswordGeneratorState::~PasswordGeneratorState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void PasswordGeneratorState::addWidgets(){

        // Password generator label
        this -> password_generator_label = QSharedPointer<QLabel>( 
            new QLabel( this -> host -> host ) 
        );
        this -> password_generator_label -> setVisible( false );
        this -> password_generator_label -> resize( 300, 70 );
        this -> password_generator_label -> setStyleSheet( "font-size: 30px"  );
        this -> password_generator_label -> move(
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).x() - 
                this -> password_generator_label -> mapToGlobal( this -> password_generator_label -> geometry().center() ).x(),
            ( this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() - 
                this -> password_generator_label -> mapToGlobal( this -> password_generator_label -> geometry().center() ).y() ) * 0.8f
        );
        this -> password_generator_label -> setText( "Password Generator" );

        // Menu button
        this -> menu_button = QSharedPointer<QPushButton>( new QPushButton( "", this -> host -> host ) );
        this -> menu_button -> setVisible( false );
        this -> menu_button -> resize( 100.f, 100.f );
        this -> menu_button -> setStyleSheet( "font-size: 20px;");
        this -> menu_button -> move( 0.f, 1.f );
        this -> menu_icon.addFile( "img/icons/home_icon.png" );
        this -> menu_button -> setIcon( this -> menu_icon );
        this -> menu_button -> setIconSize( QSize( 50.f, 50.f ) );

        // Password generator output
        this -> password_generator_output = QSharedPointer<QLabel>( 
            new QLabel( this -> host -> host ) 
        );
        this -> password_generator_output -> setVisible( false );
        this -> password_generator_output -> resize( 500, 70 );
        this -> password_generator_output -> setStyleSheet( 
            "background-color: #38394e;"
            "color: #c1c1c1;"
            "font-size: 20px;"
	        "border-style: solid;"
	        "border-width: 1px;"
	        "border-color: #4a4c68;"
        );
        this -> password_generator_output -> move(
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).x() - 
                this -> password_generator_output -> mapToGlobal( this -> password_generator_output -> geometry().center() ).x(),
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() - 
                this -> password_generator_output -> mapToGlobal( this -> password_generator_output -> geometry().center() ).y()
        );

        // Generate button
        this -> generate_button = QSharedPointer<QPushButton>( new QPushButton( "", this -> host -> host ) );
        this -> generate_button -> setVisible( false );
        this -> generate_button -> resize( 70.f, 70.f );
        this -> generate_button -> setStyleSheet( "font-size: 20px;");
        this -> generate_icon.addFile( "img/icons/refresh_icon.png" );
        this -> generate_button -> setIcon( this -> generate_icon );
        this -> generate_button -> setIconSize( QSize( 35.f, 35.f ) );
        this -> generate_button -> move(
            this -> password_generator_output -> geometry().center().x() + 180.f,
            this -> password_generator_output -> geometry().center().y() - 34.f
        );

        // Separator line
        this -> separator = QSharedPointer<QLabel>( 
            new QLabel( this -> host -> host ) 
        );
        this -> separator -> setVisible( false );
        this -> separator -> resize( 1, 100 );
        this -> separator -> setStyleSheet( 
            "background-color: #38394e;"
            "color: #c1c1c1;"
            "padding: 8%;"
            "font-size: 20px;"
	        "border-style: solid;"
	        "border-width: 1px;"
	        "border-color: #4a4c68;"
        );
        this -> separator -> move(
            this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).x() - 
                this -> separator -> mapToGlobal( this -> separator -> geometry().center() ).x(),
            ( this -> host -> host -> mapToGlobal( this -> host -> host -> geometry().center() ).y() - 
                this -> separator -> mapToGlobal( this -> separator -> geometry().center() ).y() ) + 130.f
        );

        // Length checkbox
        this -> length_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> length_checkbox -> setVisible( false );
        this -> length_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> length_checkbox -> setFixedSize( 25, 25 );
        this -> length_checkbox -> move(
            this -> separator -> geometry().center().x() - 35.f,
            this -> separator -> geometry().center().y() - 45.f
        );

        // Upper case checkbox
        this -> uppercase_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> uppercase_checkbox -> setVisible( false );
        this -> uppercase_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> uppercase_checkbox -> setFixedSize( 25, 25 );
        this -> uppercase_checkbox -> move(
            this -> separator -> geometry().center().x() - 35.f,
            this -> separator -> geometry().center().y() - 12.f
        );

        // Lower case checkbox
        this -> lowercase_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> lowercase_checkbox -> setVisible( false );
        this -> lowercase_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> lowercase_checkbox -> setFixedSize( 25, 25 );
        this -> lowercase_checkbox -> move(
            this -> separator -> geometry().center().x() - 35.f,
            this -> separator -> geometry().center().y() + 21.f
        );

        // Symbols checkbox
        this -> symbols_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> symbols_checkbox -> setVisible( false );
        this -> symbols_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> symbols_checkbox -> setFixedSize( 25, 25 );
        this -> symbols_checkbox -> move(
            this -> separator -> geometry().center().x() + 250.f,
            this -> separator -> geometry().center().y() - 45.f
        );

        // Numbers checkbox
        this -> numbers_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> numbers_checkbox -> setVisible( false );
        this -> numbers_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> numbers_checkbox -> setFixedSize( 25, 25 );
        this -> numbers_checkbox -> move(
            this -> separator -> geometry().center().x() + 250.f,
            this -> separator -> geometry().center().y() - 12.f
        );

        // Ambiguous characters checkbox
        this -> ambiguous_characters_checkbox = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host -> host ) 
        );
        this -> ambiguous_characters_checkbox -> setVisible( false );
        this -> ambiguous_characters_checkbox -> setStyleSheet( this -> checkbox_style );
        this -> ambiguous_characters_checkbox -> setFixedSize( 25, 25 );
        this -> ambiguous_characters_checkbox -> move(
            this -> separator -> geometry().center().x() + 250.f,
            this -> separator -> geometry().center().y() + 21.f
        );
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void PasswordGeneratorState::assignProperties(){

        // QLabel
        this -> assignProperty( this -> password_generator_label.get(), "visible", true );
        this -> assignProperty( this -> password_generator_output.get(), "visible", true );
        this -> assignProperty( this -> separator.get(), "visible", true );

        // QPushButton
        this -> assignProperty( this -> menu_button.get(), "visible", true );
        this -> assignProperty( this -> generate_button.get(), "visible", true );

        // QCheckBox
        this -> assignProperty( this -> lowercase_checkbox.get(), "visible", true );
        this -> assignProperty( this -> uppercase_checkbox.get(), "visible", true );
        this -> assignProperty( this -> symbols_checkbox.get(), "visible", true );
        this -> assignProperty( this -> length_checkbox.get(), "visible", true );
        this -> assignProperty( this -> ambiguous_characters_checkbox.get(), "visible", true );
        this -> assignProperty( this -> numbers_checkbox.get(), "visible", true );
    }
}