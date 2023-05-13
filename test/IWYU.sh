#!/bin/bash

# Variables
declare -a source_files=(
  "app.cpp"
  "states/base_state.cpp"
  "states/menu_state.cpp"
  "states/password_manager_state.cpp"
  "states/add_password_state.cpp"
  "widgets/base_widget.cpp"
  "widgets/custom_line_edit.cpp"
  "widgets/password_actions.cpp"
  "widgets/password_toggle.cpp"
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
    src/"$source"

  echo ""
  echo "--------------------------------------------------"
  echo ""
done
