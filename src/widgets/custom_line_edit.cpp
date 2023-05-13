//====================================================
//     File data
//====================================================
/**
 * @file custom_line_edit.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-02
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/custom_line_edit.hpp>

namespace kmanager::widget{

    //====================================================
    //     CustomQLineEdit (constructor)
    //====================================================
    /**
     * @brief Construct a new CustomQLineEdit object.
     * 
     * @param parent Parent widget.
     */
    CustomQLineEdit::CustomQLineEdit( const QString& contents, QWidget *parent ): 
        QLineEdit( contents, parent ),
        old_label( "" ){

        // Init base properties
        this -> setAlignment( Qt::AlignBottom | Qt::AlignCenter );
        this -> setStyleSheet( this -> default_settings );
    }

    //====================================================
    //     CustomQLineEdit (destructor)
    //====================================================
    /**
     * @brief Destroy the CustomQLineEdit object.
     * 
     */
    CustomQLineEdit::~CustomQLineEdit(){

    }

    //====================================================
    //     enter
    //====================================================
    /**
     * @brief Function used when mouse or cursor enter the widget area.
     * 
     */
    void CustomQLineEdit::enter(){
        this -> setStyleSheet( this -> hover_settings );
        this -> first_widget -> setStyleSheet( this -> hover_settings );
        this -> second_widget -> setStyleSheet( this -> hover_settings );
    }

    //====================================================
    //     leave
    //====================================================
    /**
     * @brief Function used when mouse or cursor leave the widget area.
     * 
     */
    void CustomQLineEdit::leave(){
        this -> setStyleSheet( this -> default_settings );
        this -> first_widget -> setStyleSheet( this -> default_settings );
        this -> second_widget -> setStyleSheet( this -> default_settings );
    }

    //====================================================
    //     enterEvent
    //====================================================
    /**
     * @brief Override the enterEvent widget function.
     * 
     * @param event Event triggered when mouse enter the widget.
     */
    void CustomQLineEdit::enterEvent( QEnterEvent* event ){
        this -> enter();
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
    void CustomQLineEdit::leaveEvent( QEvent* event ){
        this -> leave();
        event -> accept();
    }

    //====================================================
    //     keyPressEvent
    //====================================================
    /**
     * @brief Override the keyPressEvent widget function for the arrows movements.
     * 
     * @param event Event triggered when a key is pressed.
     */
    void CustomQLineEdit::keyPressEvent( QKeyEvent *event ){
        switch( event -> key() ){

            // Right
            case Qt::Key_Right:
                this -> first_widget -> setFocus();
                break;

            // Left
            case Qt::Key_Left:
                this -> second_widget -> setFocus();
                break;

            // Default
            default:
                QLineEdit::keyPressEvent( event );
        }
    }
}