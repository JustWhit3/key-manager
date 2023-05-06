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

// Qt
#include <QWidget>
#include <QApplication>
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
                saveMySettings( false ){
        
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

        // Save button
        this -> save_password = QSharedPointer<QPushButton>( new QPushButton() );
        this -> save_password -> setIcon( QApplication::style() -> standardIcon( QStyle::SP_DialogSaveButton ) );
        this -> save_password -> setIconSize( this -> icon_size );
        this -> save_password -> setToolTip( "Save" );

        // Setup layout
        this -> layout = QSharedPointer<QHBoxLayout>( new QHBoxLayout( this ) );
        this -> layout -> setSpacing( 10.f );
        this -> layout -> addWidget( this -> delete_password.get() );
        this -> layout -> addWidget( this -> save_password.get() );
        this -> layout -> setContentsMargins( 0, 0, 0, 0 );
        this -> setLayout( layout.get() );

        // Widget properties
        this -> setFixedWidth( 252 );
    }
}