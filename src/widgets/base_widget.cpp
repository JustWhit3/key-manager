//====================================================
//     File data
//====================================================
/**
 * @file base_widget.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-05-01
 * @copyright Copyright (c) 2022 Gianluca Bianco under the GPL v3.0 license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <widgets/base_widget.hpp>

// Qt
#include <QWidget>

namespace kmanager::widget {

    //====================================================
    //     BaseWidget (default constructor)
    //====================================================
    /**
     * @brief Construct a new BaseWidget object.
     *
     * @param parent The parent widget (if there is one).
     */
    BaseWidget::BaseWidget(QWidget *parent) : QWidget(parent) {}

    //====================================================
    //     BaseWidget (destructor)
    //====================================================
    /**
     * @brief Destruct a new BaseWidget object.
     *
     */
    BaseWidget::~BaseWidget() {}
}  // namespace kmanager::widget