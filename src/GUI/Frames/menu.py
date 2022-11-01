#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Npv 1 15:29:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# Standard modules
from PIL import ImageTk, Image

# GUI modules
from tkinter import ttk

#############################################################
#    menu
#############################################################
class menu( ttk.Frame ):
    """
    Class used to create the Menu frame.
    
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
        
        # Creating widgets
        self.__create_widgets()
        
    #############################################################
    #    __create_widgets
    #############################################################
    def __create_widgets( self ):
        """
        Method used to create basic frame widgets.
        """
        
        # Logo image
        self.logo_img = ImageTk.PhotoImage( Image.open( "../img/images/logo.png" ).resize( ( 350, 200 ) ) )
        self.logo_label = ttk.Label( self, image = self.logo_img )
        self.logo_label.place( anchor = "center", relx = 0.5, rely = 0.5 )
        
        # 