//====================================================
//     File data
//====================================================
/**
 * @file set_password_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-17
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_SET_PASSWORD_STATE
#define KEY_MANAGER_SET_PASSWORD_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QState>
#include <QLineEdit>
#include <QCheckBox>
#include <QLabel>
#include <QSharedPointer>
#include <QObject>
#include <QPushButton>
#include <QString>

// STD
#include <sstream>
#include <cstdint>

namespace kmanager::state{

    //====================================================
    //     SetPasswordState
    //====================================================
    /**
     * @brief Class used to construct the set password state of the app.
     * 
     */
    class SetPasswordState: public BaseState{

        // Macro for Qt
        Q_OBJECT
    
        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors / destructor
            explicit SetPasswordState( QWidget* host, QState *parent = nullptr );
            ~SetPasswordState();

            // Variables (widgets)
            QSharedPointer<QLineEdit> enter_password_first;
            QSharedPointer<QLineEdit> enter_password_second;
            QSharedPointer<QLabel> enter_password_label;
            QSharedPointer<QLabel> error_label;
            QSharedPointer<QLabel> rectangle;
            QSharedPointer<QLabel> background_rectangle;
            QSharedPointer<QLabel> user_img_label;
            QSharedPointer<QCheckBox> checkbox_first;
            QSharedPointer<QCheckBox> checkbox_second;
            QSharedPointer<QPushButton> confirm_button;

            // Variables (other)
            QWidget* host;
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Constants
            const uint32_t width{ 270 };
            const uint32_t height{ 70 };
            static const QString checkbox_first_style;
            static const QString checkbox_second_style;

        //====================================================
        //     private slots
        //====================================================
        private slots:
            void changeToggleState_first();
            void changeToggleState_second();
            void savePassword();

        //====================================================
        //     signals
        //====================================================
        signals:
            void save_password_successful( bool checked = true );
    };
}

#endif