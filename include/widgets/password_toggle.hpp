//====================================================
//     File data
//====================================================
/**
 * @file password_toggle.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-04-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_PASSWORD_TOGGLE_WIDGET
#define KEY_MANAGER_PASSWORD_TOGGLE_WIDGET

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/base_widget.hpp>

// Qt
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSharedPointer>
#include <QWidget>

namespace kmanager::widget {

    //====================================================
    //     PasswordToggle
    //====================================================
    /**
     * @brief Class used to construct a password toggle widget.
     *
     */
    class PasswordToggle : public BaseWidget {
            Q_OBJECT

        public:

            // Constructors / destructor
            explicit PasswordToggle(bool styled = true, QWidget* parent = nullptr);
            ~PasswordToggle();

            // Methods
            void initWidgetProperties() override;

            // Variables
            QLineEdit* password_label;

        private:

            // Methods
            void enterEvent(QEnterEvent* event) override;
            void leaveEvent(QEvent* event) override;

            // Variables
            QGridLayout* layout;
            QCheckBox* checkbox;
            bool styled;

            // Constants
            static const QString default_settings;
            static const QString hover_settings;
            static const QString checkbox_style_1;
            static const QString checkbox_style_2;

        private slots:

            // Methods
            void changeToggleState();
    };
}  // namespace kmanager::widget

#endif