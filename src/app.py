#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Thr Oct 27 21:40:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# GUI modules
import sv_ttk

# Windows
from GUI.Windows.root import root

#############################################################
#    Main function
#############################################################
def main(): 
    
    # Creating the root window
    root_window = root()
    
    # Setting the theme
    sv_ttk.set_theme( "light" )
    
    # Running the root window
    root_window.mainloop()

if __name__ == "__main__":
    main()