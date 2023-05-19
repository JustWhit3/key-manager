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
#include <states/set_password_state.hpp>

// Utility
#include <utility/crypto.hpp>

// Qt
#include <QStateMachine>
#include <QLineEdit>
#include <QSharedPointer>
#include <QTimer>

// STD
#include <fstream>

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

        // Get login key path
        #ifdef _WIN32
            this -> login_key_file << "C:\\Users\\" 
                                 << this -> username 
                                 << "\\.key-manager_files\\.key";
        #else
            this -> login_key_file << "/home/" 
                                 << this -> username 
                                 << "/.key-manager_files/.key";
        #endif
    
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
                this -> enter_password_first -> mapToGlobal( this -> enter_password_first -> geometry().center() ).y() ) * 0.9f
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
                this -> enter_password_second -> mapToGlobal( this -> enter_password_second -> geometry().center() ).y() ) * 1.1f
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
                this -> checkbox_first -> mapToGlobal( this -> checkbox_first -> geometry().center() ).y() ) * 0.9f
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
                this -> checkbox_second -> mapToGlobal( this -> checkbox_second -> geometry().center() ).y() ) * 1.09f
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
                this -> enter_password_label -> mapToGlobal( this -> enter_password_label -> geometry().center() ).x() ) * 0.825f,
            this -> enter_password_first -> geometry().y() * 0.75f
        );
        this -> enter_password_label -> resize( this -> width + 50, this -> height );
        this -> enter_password_label -> setStyleSheet( "font-size: 30px" );

        // Error label
        this -> error_label = QSharedPointer<QLabel>(
            new QLabel( this -> host )
        );
        this -> error_label -> resize( this -> width + 200.f, this -> height / 2 );
        this -> error_label -> setVisible( false );
        this -> error_label -> setStyleSheet( "QLabel { color : rgb(183, 0, 0); font-size: 20px }" );
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
            this -> error_label -> setText( "One of the two password entries is empty!" );
            this -> error_label -> move(
                this -> enter_password_second -> geometry().x() - 55.f,
                this -> enter_password_second -> geometry().y() + 90.f
            );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }

        // Case in which the two passwords are different
        else if( this -> enter_password_first -> text() != this -> enter_password_second -> text() ){
            this -> error_label -> setVisible( true );
            this -> error_label -> setText( "The two passwords are different!" );
            this -> error_label -> move(
                this -> enter_password_second -> geometry().x() - 15.f,
                this -> enter_password_second -> geometry().y() + 90.f
            );
            QTimer::singleShot( 2000, this -> error_label.get(), &QLabel::hide );
        }

        // Successful case
        else{
            // Encrypt the password
            utility::Crypto crypto( this -> enter_password_first -> text().toStdString() );

            // Save encrypted password
            std::ofstream output( this -> login_key_file.str() );
            output << crypto.encrypt() << "\n";
            output << crypto.getKey() << "\n";
            output.close();
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
    }
}