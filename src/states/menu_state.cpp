//====================================================
//     File data
//====================================================
/**
 * @file menu_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>
#include <states/menu_state.hpp>

// Qt
#include <QState>
#include <QLabel>
#include <QSize>
#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QSharedPointer>
#include <QIcon>
#include <QPixmap>
#include <QString>
#include <QFile>

namespace kmanager::state{


    //====================================================
    //     Initialize constants
    //====================================================
    const QString MenuState::button_style{ 
        "font-size: 20px;"
	    "border-radius: 11px;"
    };

    //====================================================
    //     MenuState (default constructor)
    //====================================================
    /**
     * @brief Construct a new MenuState object.
     * 
     * @param parent The parent state (if there is one).
     */
    MenuState::MenuState( QWidget *host, QState *parent ): 
        BaseState( parent ),
        host( host ){
    
        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     MenuState (destructor)
    //====================================================
    /**
     * @brief Destruct a new MenuState object.
     * 
     */
    MenuState::~MenuState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void MenuState::addWidgets(){

        // Password manager button
        this -> p_manager_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Password manager", this -> host ) 
        );
        this -> p_manager_button -> setVisible( false );
        this -> p_manager_button -> resize( this -> button_width, this -> button_height );
        this -> p_manager_button -> setStyleSheet( this -> button_style );
        this -> p_manager_button -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> p_manager_button -> mapToGlobal( this -> p_manager_button -> geometry().center() ).x() ) * 1.45f,
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> p_manager_button -> mapToGlobal( this -> p_manager_button -> geometry().center() ).y() ) * 0.9f
        );

        // Password generator button
        this -> p_generator_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Password generator", this -> host ) 
        );
        this -> p_generator_button -> setVisible( false );
        this -> p_generator_button -> resize( this -> button_width, this -> button_height );
        this -> p_generator_button -> setStyleSheet( this -> button_style );
        this -> p_generator_button -> move(
            this -> p_manager_button -> geometry().x(),
            this -> p_manager_button -> geometry().y() + 80.f
        );

        // Exit button
        this -> exit_button = QSharedPointer<QPushButton>( 
            new QPushButton( "Exit", this -> host ) 
        );
        this -> exit_button -> setVisible( false );
        this -> exit_button -> resize( this -> button_width, this -> button_height );
        this -> exit_button -> setStyleSheet( this -> button_style );
        this -> exit_button -> move(
            this -> p_generator_button -> geometry().x(),
            this -> p_generator_button -> geometry().y() + 80.f
        );

        QObject::connect( 
            this -> exit_button.get(), 
            SIGNAL( clicked() ), 
            this -> host, 
            SLOT( close() ) 
        );

        // Change password button
        this -> change_password_button = QSharedPointer<QPushButton>( 
            new QPushButton( "", this -> host ) 
        );
        this -> change_password_button -> setVisible( false );
        this -> change_password_button -> setStyleSheet( 
            "QPushButton{ background-color: rgba(255, 255, 255, 0); border-radius: 11px; }"
            "QPushButton::hover { background-color: rgba(255, 255, 255, 50); }"
            "QPushButton::pressed { background-color: rgba(255, 255, 255, 70); }"
        );
        this -> change_password_button -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() * 1.84f,
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() + 315.f
        );
        this -> change_password_icon.addFile( "img/icons/user.png" );
        this -> change_password_button -> setIcon( this -> change_password_icon );
        this -> change_password_button -> setIconSize( QSize( this -> button_height, this -> button_height ) );

        // Image logo label
        this -> logo_img_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> logo_img_label -> setVisible( false );
        this -> logo_img_label -> setPixmap( QPixmap( "img/images/logo_app.png" ) );
        this -> logo_img_label -> move(
            this -> p_manager_button -> geometry().x() * 0.86f,
            this -> p_manager_button -> geometry().y() * 0.2f
        );

        // Side rectangle decoration
        this -> side_rectangle = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> side_rectangle -> setVisible( false );
        this -> side_rectangle -> resize( 
            this -> host -> geometry().width() * 0.35f, 
            this -> host -> geometry().height()
        );
        this -> side_rectangle -> setStyleSheet( 
            "background-color: rgba( 32, 32, 32, 80% );"
	        "border-style: solid;"
	        "border-width: 2px;"
	        "border-color: #4a4c68;"
            "font-size: 20px;"
        );
        QFile file( "html/metadata.html" );
        file.open( QFile::ReadOnly );
        this -> side_rectangle -> setText( QLatin1String( file.readAll() ) );
        this -> side_rectangle -> setAlignment( Qt::AlignTop );
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void MenuState::assignProperties(){

        // Buttons
        this -> assignProperty( this -> p_manager_button.get(), "visible", true );
        this -> assignProperty( this -> p_generator_button.get(), "visible", true );
        this -> assignProperty( this -> exit_button.get(), "visible", true );
        this -> assignProperty( this -> change_password_button.get(), "visible", true );

        // Labels
        this -> assignProperty( this -> logo_img_label.get(), "visible", true );
        this -> assignProperty( this -> side_rectangle.get(), "visible", true );
    }
}