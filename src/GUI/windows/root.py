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

# Frames
from GUI.frames.menu import menu
from GUI.frames.settings import settings
from GUI.frames.password_creator import password_creator
from GUI.frames.password_manager import password_manager

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
        self.window_width = 1200
        self.window_height = 900
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
        
        # Creating frames
        self.password_creator = password_creator( self, self.window_width, self.window_height )
        self.password_manager = password_manager( self, self.window_width, self.window_height )
        self.settings = settings( self, self.window_width, self.window_height )
        self.menu = menu( self, self.window_width, self.window_height )
        
    #############################################################
    #    __create_widgets
    #############################################################
    def __create_commands( self ):
        """
        Method used to create commands.
        """

        # Enabling keyboard commands
        self.bind( "<Control-z>", sys.exit )
        self.bind( "<Control-c>", sys.exit )
        self.bind( "<Control-x>", sys.exit )