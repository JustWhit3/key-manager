//====================================================
//     File data
//====================================================
/**
 * @file set_password_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-17
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <states/base_state.hpp>
#include <states/set_password_state.hpp>

// Utility
#include <utility/crypto.hpp>

// Qt
#include <QState>
#include <QLineEdit>
#include <QSharedPointer>
#include <QTimer>
#include <QCheckBox>
#include <QLabel>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QWidget>
#include <QPixmap>
#include <QSize>

// STD
#include <fstream>
#include <string>
#include <string_view>

namespace kmanager::state{

    //====================================================
    //     SetPasswordState (default constructor)
    //====================================================
    /**
     * @brief Construct a new SetPasswordState object.
     * 
     * @param parent The parent state (if there is one).
     */
    SetPasswordState::SetPasswordState( QWidget *host, QState *parent ): 
        BaseState( parent ),
        host( host ){

        // Create widgets
        this -> addWidgets();

        // Assign properties
        this -> assignProperties();
    }

    //====================================================
    //     SetPasswordState (destructor)
    //====================================================
    /**
     * @brief Destruct a new SetPasswordState object.
     * 
     */
    SetPasswordState::~SetPasswordState(){
    
    }

    //====================================================
    //     addWidgets
    //====================================================
    /**
     * @brief Add widgets to the current state.
     * 
     */
    void SetPasswordState::addWidgets(){

        // Background rectangle decoration
        this -> background_rectangle = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> background_rectangle -> setVisible( false );
        this -> background_rectangle -> resize( 
            this -> host -> geometry().width(), 
            this -> host -> geometry().height() * 0.57f
        );
        this -> background_rectangle -> setStyleSheet( 
            "background-color: rgba( 255, 156, 43, 80% );"
        );
        this -> background_rectangle -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> background_rectangle -> mapToGlobal( this -> background_rectangle -> geometry().center() ).x(),
            0
        );

        // Rectangle decoration
        this -> rectangle = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> rectangle -> setVisible( false );
        this -> rectangle -> resize( 400, 600 );
        this -> rectangle -> setStyleSheet( 
            "background-color: rgba( 35, 36, 48, 100% );"
            "color: #c1c1c1;"
	        "border-style: solid;"
	        "border-width: 5px;"
	        "border-color: #4a4c68;"
            "border-radius: 50%"
        );
        this -> rectangle -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> rectangle -> mapToGlobal( this -> rectangle -> geometry().center() ).x(),
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> rectangle -> mapToGlobal( this -> rectangle -> geometry().center() ).y()
        );

        // Enter first password line edit
        this -> enter_password_first = QSharedPointer<QLineEdit>( 
            new QLineEdit( this -> host ) 
        );
        this -> enter_password_first -> setVisible( false );
        this -> enter_password_first -> resize( this -> width, this -> height );
        this -> enter_password_first -> setStyleSheet( "font-size: 20px"  );
        this -> enter_password_first -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> enter_password_first -> mapToGlobal( this -> enter_password_first -> geometry().center() ).x(),
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> enter_password_first -> mapToGlobal( this -> enter_password_first -> geometry().center() ).y() ) * 1.1f
        );
        this -> enter_password_first -> setPlaceholderText( "Enter password..." );
        this -> enter_password_first -> setEchoMode( QLineEdit::Password );
        this -> enter_password_first -> setContextMenuPolicy( Qt::NoContextMenu );

        QObject::connect( 
             this -> enter_password_first.get(), 
             SIGNAL( returnPressed() ), 
             this, 
             SLOT( savePassword() ) 
        );

        QObject::connect( 
             this -> enter_password_first.get(), 
             SIGNAL( returnPressed() ), 
             this, 
             SLOT( savePassword() ) 
        );

        // Enter second password line edit
        this -> enter_password_second = QSharedPointer<QLineEdit>( 
            new QLineEdit( this -> host ) 
        );
        this -> enter_password_second -> setVisible( false );
        this -> enter_password_second -> resize( this -> width, this -> height );
        this -> enter_password_second -> setStyleSheet( "font-size: 20px"  );
        this -> enter_password_second -> move(
            this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> enter_password_second -> mapToGlobal( this -> enter_password_second -> geometry().center() ).x(),
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> enter_password_second -> mapToGlobal( this -> enter_password_second -> geometry().center() ).y() ) * 1.3f
        );
        this -> enter_password_second -> setPlaceholderText( "Enter again..." );
        this -> enter_password_second -> setEchoMode( QLineEdit::Password );
        this -> enter_password_second -> setContextMenuPolicy( Qt::NoContextMenu );

        QObject::connect( 
             this -> enter_password_second.get(), 
             SIGNAL( returnPressed() ), 
             this, 
             SLOT( savePassword() ) 
        );

        // Setup first checkbox
        this -> checkbox_first = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host ) 
        );
        this -> checkbox_first -> setVisible( false );
        this -> checkbox_first -> setStyleSheet( 
            "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
            "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
            "QCheckBox::indicator { width: 35px; height: 35px; background-color: #38394e; }"
            
        );
        this -> checkbox_first -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> checkbox_first -> mapToGlobal( this -> checkbox_first -> geometry().center() ).x() ) * 1.29f,
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> checkbox_first -> mapToGlobal( this -> checkbox_first -> geometry().center() ).y() ) * 1.1f
        );
        this -> checkbox_first -> setFixedSize( 35, 35 );

        QObject::connect( 
             this -> checkbox_first.get(), 
             SIGNAL( clicked() ), 
             this, 
             SLOT( changeToggleState_first() ) 
        );

        // Setup second checkbox
        this -> checkbox_second = QSharedPointer<QCheckBox>( 
            new QCheckBox( this -> host ) 
        );
        this -> checkbox_second -> setVisible( false );
        this -> checkbox_second -> setStyleSheet( 
            "QCheckBox::indicator:unchecked { image: url(img/icons/hide.png); }" 
            "QCheckBox::indicator:checked { image: url(img/icons/eye.png); }"
            "QCheckBox::indicator { width: 35px; height: 35px; background-color: #38394e; }"
            
        );
        this -> checkbox_second -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> checkbox_second -> mapToGlobal( this -> checkbox_second -> geometry().center() ).x() ) * 1.29f,
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).y() - 
                this -> checkbox_second -> mapToGlobal( this -> checkbox_second -> geometry().center() ).y() ) * 1.29f
        );
        this -> checkbox_second -> setFixedSize( 35, 35 );

        QObject::connect( 
             this -> checkbox_second.get(), 
             SIGNAL( clicked() ), 
             this, 
             SLOT( changeToggleState_second() ) 
        );

        // Insert a new password label
        this -> enter_password_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> enter_password_label -> setVisible( false );
        this -> enter_password_label -> setText( "Set a new password:" );
        this -> enter_password_label -> move(
            ( this -> host -> mapToGlobal( this -> host -> geometry().center() ).x() - 
                this -> enter_password_label -> mapToGlobal( this -> enter_password_label -> geometry().center() ).x() ) * 0.865f,
            this -> enter_password_first -> geometry().y() * 0.87f
        );
        this -> enter_password_label -> setStyleSheet( 
            "QLabel { background-color: rgba( 255, 255, 255, 0% ); font-size: 25px }" 
        );

        // Error label
        this -> error_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> error_label -> resize( this -> width + 50.f, this -> height / 2 );
        this -> error_label -> setVisible( false );
        this -> error_label -> setStyleSheet( "QLabel { color : rgb(183, 0, 0); font-size: 20px }" );

        // User image label
        this -> user_img_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> user_img_label -> setVisible( false );
        this -> user_img_label -> setPixmap( QPixmap( "img/icons/user.png" ) );
        this -> user_img_label -> move(
            this -> enter_password_second -> geometry().x() + 33.f,
            this -> enter_password_label -> geometry().y() * 0.4f
        );
        this -> user_img_label -> setStyleSheet( "QLabel { background-color: rgba( 255, 255, 255, 0% ) }"  );

        // Confirm button
        this -> confirm_button = QSharedPointer<QPushButton>( 
            new QPushButton( "", this -> host ) 
        );
        this -> confirm_button -> setVisible( false );
        this -> confirm_button -> setStyleSheet( 
            "font-size: 20px;"
            "border-radius: 11px;"
        );
        this -> confirm_button -> move(
            this -> enter_password_second -> geometry().x(),
            this -> enter_password_second -> geometry().y() * 1.18f
        );
        this -> confirm_button -> setFixedSize( 
            QSize( 
                this -> enter_password_first -> geometry().width() , 
                this -> enter_password_second -> geometry().height() 
            ) 
        );
        this -> confirm_button -> setText( "Confirm" );

        QObject::connect( 
             this -> confirm_button.get(), 
             SIGNAL( clicked() ), 
             this, 
             SLOT( savePassword() ) 
        );
    }

    //====================================================
    //     changeToggleState_first
    //====================================================
    /**
     * @brief Slot used to change toggle state of first password checkbox when clicked.
     * 
     */
    void SetPasswordState::changeToggleState_first(){
        this -> enter_password_first -> setEchoMode(
            this -> checkbox_first -> checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password 
        );
    }

    //====================================================
    //     changeToggleState_second
    //====================================================
    /**
     * @brief Slot used to change toggle state of second password checkbox when clicked.
     * 
     */
    void SetPasswordState::changeToggleState_second(){
        this -> enter_password_second -> setEchoMode(
            this -> checkbox_second -> checkState() == Qt::Checked ? QLineEdit::Normal : QLineEdit::Password 
        );
    }

    //====================================================
    //     savePassword
    //====================================================
    /**
     * @brief Slot used to save the new password for future login steps.
     * 
     */
    void SetPasswordState::savePassword(){

        // Case in which one of the two is empty
        if( this -> enter_password_first -> text() == "" || this -> enter_password_second -> text() == "" ){
            this -> error_label -> setVisible( true );
            this -> error_label -> setText( "One of the two entries is empty!" );
            this -> error_label -> move(
                this -> enter_password_second -> geometry().x() - 10.f,
                this -> enter_password_second -> geometry().y() + 170.f
            );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }

        // Case in which the two passwords are different
        else if( this -> enter_password_first -> text() != this -> enter_password_second -> text() ){
            this -> error_label -> setVisible( true );
            this -> error_label -> setText( "The two entries are different!" );
            this -> error_label -> move(
                this -> enter_password_second -> geometry().x(),
                this -> enter_password_second -> geometry().y() + 170.f
            );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }

        // Successful case
        else{
            utility::Crypto crypto( this -> enter_password_first -> text().toStdString() );
            this -> settings.setValue( "Password", QString::fromStdString( crypto.encrypt() ) );
            this -> settings.setValue( "Key", QString::fromStdString( crypto.getKey() ) );
            emit this -> save_password_successful( true );
        }
    }

    //====================================================
    //     assignProperties
    //====================================================
    /**
     * @brief Assign properties to the current state.
     * 
     */
    void SetPasswordState::assignProperties(){

        // QLineEdit
        this -> assignProperty( this -> enter_password_first.get(), "visible", true );
        this -> assignProperty( this -> enter_password_second.get(), "visible", true );

        // QCheckBox
        this -> assignProperty( this -> checkbox_first.get(), "visible", true );
        this -> assignProperty( this -> checkbox_second.get(), "visible", true );

        // QLabel
        this -> assignProperty( this -> enter_password_label.get(), "visible", true );
        this -> assignProperty( this -> rectangle.get(), "visible", true );
        this -> assignProperty( this -> background_rectangle.get(), "visible", true );
        this -> assignProperty( this -> user_img_label.get(), "visible", true );

        // QPushButton
        this -> assignProperty( this -> confirm_button.get(), "visible", true );
    }
}