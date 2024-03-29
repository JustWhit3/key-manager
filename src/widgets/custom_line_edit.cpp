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

// QT
#include <QEvent>
#include <QLineEdit>
#include <QString>

namespace kmanager::widget {

    //====================================================
    //     Variables
    //====================================================
    const QString CustomQLineEdit::default_settings{
        "background-color: rgba( 255, 255, 255, 0% ); padding: 8%; font-size: 18px;"};
    const QString CustomQLineEdit::hover_settings{
        "background-color: rgba( 255, 255, 255, 0% ); padding: 8%; border-color: rgb(255, 255, 255); font-size: 18px;"};

    //====================================================
    //     CustomQLineEdit (constructor)
    //====================================================
    /**
     * @brief Construct a new CustomQLineEdit object.
     *
     * @param parent Parent widget.
     */
    CustomQLineEdit::CustomQLineEdit(const QString& contents, QWidget* parent)
        : QLineEdit(contents, parent), first_widget(nullptr), second_widget(nullptr), old_label("") {
        // Init base properties
        this->setAlignment(Qt::AlignBottom | Qt::AlignCenter);
        this->setStyleSheet(this->default_settings);
        this->setContextMenuPolicy(Qt::NoContextMenu);
    }

    //====================================================
    //     CustomQLineEdit (destructor)
    //====================================================
    /**
     * @brief Destroy the CustomQLineEdit object.
     *
     */
    CustomQLineEdit::~CustomQLineEdit() {}

    //====================================================
    //     enterEvent
    //====================================================
    /**
     * @brief Override the enterEvent widget function.
     *
     * @param event Event triggered when mouse enter the widget.
     */
    void CustomQLineEdit::enterEvent(QEnterEvent* event) {
        this->setStyleSheet(this->hover_settings);
        this->first_widget->setStyleSheet(this->hover_settings);
        this->second_widget->setStyleSheet(this->hover_settings);
        event->accept();
    }

    //====================================================
    //     leaveEvent
    //====================================================
    /**
     * @brief Override the leaveEvent widget function.
     *
     * @param event Event triggered when mouse leave the widget.
     */
    void CustomQLineEdit::leaveEvent(QEvent* event) {
        this->setStyleSheet(this->default_settings);
        this->first_widget->setStyleSheet(this->default_settings);
        this->second_widget->setStyleSheet(this->default_settings);
        event->accept();
    }

    //====================================================
    //     keyPressEvent
    //====================================================
    /**
     * @brief Override the keyPressEvent widget function for the arrows movements.
     *
     * @param event Event triggered when a key is pressed.
     */
    void CustomQLineEdit::keyPressEvent(QKeyEvent* event) {
        switch (event->key()) {
            // Right
            case Qt::Key_Right:
                this->first_widget->setFocus();
                break;

            // Left
            case Qt::Key_Left:
                this->second_widget->setFocus();
                break;

            // Default
            default:
                QLineEdit::keyPressEvent(event);
        }
    }
}  // namespace kmanager::widget