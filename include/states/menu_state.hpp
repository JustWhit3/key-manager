//====================================================
//     File data
//====================================================
/**
 * @file menu_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-09
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_MENU_STATE
#define KEY_MANAGER_MENU_STATE

//====================================================
//     Headers
//====================================================

// States
#include <states/base_state.hpp>

// Qt
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QSharedPointer>
#include <QStateMachine>
#include <QString>

// STD
#include <cstdint>

namespace kmanager::state {

    //====================================================
    //     MenuState
    //====================================================
    /**
     * @brief Class used to construct the menu state of the app.
     *
     */
    class MenuState : public BaseState {
        public:

            // Constructors / destructor
            explicit MenuState(QWidget* host, QState* parent = nullptr);
            ~MenuState();

            // Variables (widgets)
            QSharedPointer<QPushButton> p_manager_button;
            QSharedPointer<QPushButton> p_generator_button;
            QSharedPointer<QPushButton> exit_button;
            QSharedPointer<QPushButton> change_password_button;
            QSharedPointer<QLabel> version;
            QSharedPointer<QLabel> logo_img_label;
            QSharedPointer<QLabel> side_rectangle;

            // Variables (other)
            QWidget* host;

        private:

            // Methods
            void addWidgets() override;
            void assignProperties() override;

            // Variables
            QIcon change_password_icon;

            // Constants
            static const QString button_style;
            static const uint32_t button_width{220};
            static const uint32_t button_height{70};
    };
}  // namespace kmanager::state

#endif