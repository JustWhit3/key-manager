//====================================================
//     File data
//====================================================
/**
 * @file password_generator_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-28
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_GENERATOR_STATE
#define KEY_MANAGER_PASSWORD_GENERATOR_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/menu_state.hpp>

// Qt
#include <QObject>
#include <QSharedPointer>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QCheckBox>
#include <QString>
#include <QLineEdit>

// STD
#include <string>

namespace kmanager::state{

    //====================================================
    //     PasswordGeneratorState
    //====================================================
    /**
     * @brief Class used to construct the password generator state of the app.
     * 
     */
    class PasswordGeneratorState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit PasswordGeneratorState( MenuState* host, QState *parent = nullptr );
            ~PasswordGeneratorState();

            // Variables (widgets)
            QSharedPointer<QLabel> password_generator_label;
            QSharedPointer<QLabel> comment_label;
            QSharedPointer<QLabel> password_generator_output;
            QSharedPointer<QLabel> separator;
            QSharedPointer<QLabel> lowercase_label;
            QSharedPointer<QLabel> uppercase_label;
            QSharedPointer<QLabel> length_label;
            QSharedPointer<QLabel> symbols_label;
            QSharedPointer<QLabel> numbers_label;
            QSharedPointer<QLabel> ambiguous_characters_label;
            QSharedPointer<QLabel> copied;
            QSharedPointer<QLabel> rectangle;
            QSharedPointer<QPushButton> menu_button;
            QSharedPointer<QPushButton> generate_button;
            QSharedPointer<QPushButton> copy_button;
            QSharedPointer<QCheckBox> lowercase_checkbox;
            QSharedPointer<QCheckBox> uppercase_checkbox;
            QSharedPointer<QCheckBox> symbols_checkbox;
            QSharedPointer<QCheckBox> numbers_checkbox;
            QSharedPointer<QCheckBox> ambiguous_characters_checkbox;
            QSharedPointer<QLineEdit> length_line_edit;

            // Variables (other)
            MenuState* host;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            QIcon menu_icon;
            QIcon generate_icon;
            QIcon copy_icon;
            std::string chars_container;
            std::string output_password;

            // Constants
            QString checkbox_style =
                "QCheckBox::indicator { width: 25px; height: 25px; background-color: #38394e; }"
                "QCheckBox::indicator:checked { image: url(img/icons/done.png); background-color: #38394e; }";

        //====================================================
        //     Private slots
        //====================================================
        private slots:
            void copiedPassword();
            void generatePassword();
    };
}

#endif