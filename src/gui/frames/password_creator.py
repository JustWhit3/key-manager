#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Thr Nov 3 21:55:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# GUI modules
from tkinter import ttk

#############################################################
#    password_creator
#############################################################
class password_creator( ttk.Frame ):
    """
    Class used to create the Password Creator frame.
    
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

    #############################################################
    #    __create_widgets
    #############################################################
    def __create_widgets( self ):
        """
        Method used to create frames.
        """
        
        pass