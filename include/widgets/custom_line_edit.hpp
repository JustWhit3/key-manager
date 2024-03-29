//====================================================
//     File data
//====================================================
/**
 * @file custom_line_edit.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-02
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef KEY_MANAGER_CUSTOM_LINE_EDIT_WIDGET
#define KEY_MANAGER_CUSTOM_LINE_EDIT_WIDGET

//====================================================
//     Headers
//====================================================

// Qt
#include <QEnterEvent>
#include <QLineEdit>
#include <QString>

namespace kmanager::widget {

    //====================================================
    //     CustomQLineEdit
    //====================================================
    class CustomQLineEdit : public QLineEdit {
        public:

            // Constructors / destructor
            explicit CustomQLineEdit(const QString& contents, QWidget* parent = nullptr);
            ~CustomQLineEdit();

            // Variables
            CustomQLineEdit* first_widget;
            CustomQLineEdit* second_widget;
            QString old_label;

        private:

            // Methods
            void enterEvent(QEnterEvent* event) override;
            void leaveEvent(QEvent* event) override;
            void keyPressEvent(QKeyEvent* event) override;

            // Constants
            static const QString default_settings;
            static const QString hover_settings;
    };
}  // namespace kmanager::widget

#endif