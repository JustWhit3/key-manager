//====================================================
//     File data
//====================================================
/**
 * @file password_actions.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-01
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/base_widget.hpp>
#include <widgets/password_actions.hpp>
#include <widgets/custom_line_edit.hpp>

// Qt
#include <QWidget>
#include <QApplication>
#include <QStyle>
#include <QSharedPointer>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QStyle>

namespace kmanager::widget{

    //====================================================
    //     PasswordActions (constructor)
    //====================================================
    /**
     * @brief Construct a new Password Actions object.
     * 
     * @param parent 
     */
    PasswordActions::PasswordActions( QWidget* parent ):
                BaseWidget( parent ),
                deleteMe( false ),
                saveMySettings( false ),
                seeMyInfo( false ),
                first_widget( nullptr ),
                second_widget( nullptr ),
                third_widget( nullptr ){
        
        // Initialize widget properties
        this -> initWidgetProperties();
    }

    //====================================================
    //     PasswordActions (destructor)
    //====================================================
    /**
     * @brief Destruct a new Password Actions object.
     * 
     */
    PasswordActions::~PasswordActions(){

    }

    //====================================================
    //     setDeleteTrue
    //====================================================
    /**
     * @brief Set deleteMe variable to true.
     * 
     */
    void PasswordActions::setDeleteTrue(){
        this -> deleteMe = true;
    }

    //====================================================
    //     setSaveMySettingsTrue
    //====================================================
    /**
     * @brief Set deleteMe variable to true.
     * 
     */
    void PasswordActions::setSaveMySettingsTrue(){
        this -> saveMySettings = true;
    }

    //====================================================
    //     seePasswordInformation
    //====================================================
    /**
     * @brief Display a new window with specific password information.
     * 
     */
    void PasswordActions::setInformationTrue(){
        this -> seeMyInfo = true;
    }

    //====================================================
    //     initWidgetProperties
    //====================================================
    /**
     * @brief Initialize basic widgets properties.
     * 
     */
    void PasswordActions::initWidgetProperties(){

        // Delete button
        this -> delete_password = QSharedPointer<QPushButton>( new QPushButton() );
        this -> delete_password -> setIcon( QApplication::style() -> standardIcon( QStyle::SP_TrashIcon ) );
        this -> delete_password -> setIconSize( this -> icon_size );
        this -> delete_password -> setToolTip( "Delete" );
        this -> delete_password -> setStyleSheet( "border-radius: 11px;" );

        // Save button
        this -> save_password = QSharedPointer<QPushButton>( new QPushButton() );
        this -> save_password -> setIcon( QApplication::style() -> standardIcon( QStyle::SP_DialogSaveButton ) );
        this -> save_password -> setIconSize( this -> icon_size );
        this -> save_password -> setToolTip( "Save" );
        this -> save_password -> setStyleSheet( "border-radius: 11px;" );

        // See password info
        this -> see_password_info = QSharedPointer<QPushButton>( new QPushButton() );
        this -> see_password_info -> setIcon( QApplication::style() -> standardIcon( QStyle::SP_FileDialogInfoView ) );
        this -> see_password_info -> setIconSize( this -> icon_size );
        this -> see_password_info -> setToolTip( "Information" );
        this -> see_password_info -> setStyleSheet( "border-radius: 11px;" );

        // Setup layout
        this -> layout = QSharedPointer<QHBoxLayout>( new QHBoxLayout( this ) );
        this -> layout -> setSpacing( 10.f );
        this -> layout -> addWidget( this -> delete_password.get() );
        this -> layout -> addWidget( this -> save_password.get() );
        this -> layout -> addWidget( this -> see_password_info.get() );
        this -> layout -> setContentsMargins( 0, 0, 0, 0 );
        this -> setLayout( layout.get() );

        // Widget properties
        this -> setFixedWidth( 252 );
    }

    //====================================================
    //     enterEvent
    //====================================================
    /**
     * @brief Override the enterEvent widget function.
     * 
     * @param event Event triggered when mouse enter the widget.
     */
    void PasswordActions::enterEvent( QEnterEvent* event ){
        this -> first_widget -> setStyleSheet( this -> hover_settings );
        this -> second_widget -> setStyleSheet( this -> hover_settings );
        this -> third_widget -> setStyleSheet( this -> hover_settings );
        event -> accept();
    }

    //====================================================
    //     leaveEvent
    //====================================================
    /**
     * @brief Override the leaveEvent widget function.
     * 
     * @param event Event triggered when mouse leave the widget.
     */
    void PasswordActions::leaveEvent( QEvent* event ){
        this -> first_widget -> setStyleSheet( this -> default_settings );
        this -> second_widget -> setStyleSheet( this -> default_settings );
        this -> third_widget -> setStyleSheet( this -> default_settings );
        event -> accept();
    }
}