#!/bin/bash

# Variables
declare -a source_files=(

  # App files
  "app.cpp"

  # States
  "states/base_state.cpp"
  "states/menu_state.cpp"
  "states/password_manager_state.cpp"
  "states/password_generator_state.cpp"
  "states/add_password_state.cpp"
  "states/login_state.cpp"
  "states/set_password_state.cpp"
  "states/password_info_state.cpp"

  # Utility
  "utility/crypto.cpp"

  # Widgets
  "widgets/base_widget.cpp"
  "widgets/custom_line_edit.cpp"
  "widgets/password_actions.cpp"
  "widgets/password_toggle.cpp"

  # Windows
  "windows/base_window.cpp"
  "windows/main_window.cpp"
  "windows/add_password_window.cpp"
)

# Source code check
echo ""
echo "======================================================"
echo "     IWYU Checks"
echo "======================================================"
echo ""
for source in "${source_files[@]}"; do
  include-what-you-use \
    -std=c++20 \
    -I/usr/lib/llvm-14/lib/clang/14.0.0/include \
    -Iinclude \
    -I/usr/local/Qt-6.4.2/include/ \
    -I/usr/local/Qt-6.4.2/include/QtCore \
    -I/usr/local/Qt-6.4.2/include/QtWidgets \
    -I/usr/local/Qt-6.4.2/include/QtStateMachine \
    -I/usr/local/Qt-6.4.2/include/QtGui \
    -fPIC \
    src/"$source"

  echo ""
  echo "--------------------------------------------------"
  echo ""
done
