#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 1 15:06:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# Standard modules
import sys, os

# GUI modules
import tkinter as tk
from turtle import window_height

# Frames
from GUI.Frames.menu import menu

#############################################################
#    root
#############################################################
class root( tk.Tk ):
    """
    Main window of the app.
    
    Args:
        tk.Tk (tkinter): main tkinter class.
    """
    
    #############################################################
    #    __init__
    #############################################################
    def __init__( self ):
        """
        Main constructor of the class
        """
        
        # Calling mother class constructor
        super().__init__()
        
        # Resizing the window
        self.window_width = 1000
        self.window_height = 800
        screen_width = self.winfo_screenwidth()
        screen_height = self.winfo_screenheight()
        center_x = int( screen_width / 2 - self.window_width / 2 )
        center_y = int( screen_height / 2 - self.window_height / 2 )
        self.geometry( f"{self.window_width}x{self.window_height}+{center_x}+{center_y}" )
        
        # Basic settings
        self.title( "Key Manager" )

        # Icon settings
        path_to_icon = os.getcwd() + "/../img/icons/logo"
        if "nt" == os.name:
            self.iconbitmap( path_to_icon + ".ico")
        else:
            self.iconbitmap( "@" + path_to_icon + ".xbm" )
        
        # Enabling keyboard commands
        self.bind( "<Control-z>", sys.exit )
        self.bind( "<Control-c>", sys.exit )
        self.bind( "<Control-x>", sys.exit )

        # Creating widgets
        self.__create_widgets()

    #############################################################
    #    __create_widgets
    #############################################################
    def __create_widgets( self ):
        """
        Method used to create frames.
        """
        
        # Creating frames
        self.menu = menu( self, self.window_width, self.window_height )