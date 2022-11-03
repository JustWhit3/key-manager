#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Thr Nov 3 20:22:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# GUI modules
from tkinter import ttk

#############################################################
#    options
#############################################################
class settings( ttk.Frame ):
    """
    Class used to create the Options frame.
    
    Args:
        ttk (tkinter.Frame): inherits from tkinter.Frame class.
    """
    
    #############################################################
    #    __init__
    #############################################################
    def __init__( self, window, width, height ):
        """
        Main constructor of the class.

        Args:
            window (tk.Tk): window in which the frame lies.
            width (int): width of the frame.
            height (int): height of the frame.
        """
        
        # Initializing with constructor
        super().__init__( window )

        # Frame settings
        self[ "width" ] = width
        self[ "height" ] = height
        self.place( anchor = "center", relx = 0.5, rely = 0.5 )

        # Variables
        self.button_width = 18

        # Creating widgets
        self.__create_widgets()
        self.__create_commands()

    #############################################################
    #    __create_widgets
    #############################################################
    def __create_widgets( self ):
        """
        Method used to create frames.
        """
        
        # Change theme button
        self.change_theme_button = ttk.Button( self, text = "Change theme", command = None )
        self.change_theme_button.config( cursor = "hand2", width = self.button_width )
        self.change_theme_button.place( anchor = "center", relx = 0.5, rely = 0.55 )

    #############################################################
    #    __create_commands
    #############################################################
    def __create_commands( self ):
        """
        Method used to create basic keyboard commands.
        """

        # Cursor commands
        self.change_theme_button.focus_set()