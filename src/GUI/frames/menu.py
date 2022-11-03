#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 1 15:29:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    Modules
#############################################################

# Standard modules
from PIL import ImageTk, Image

# GUI modules
import tkinter as tk
from tkinter import ttk

# Frames
from GUI.frames.settings import settings
from GUI.frames.password_creator import password_creator
from GUI.frames.password_manager import password_manager

# Utility
from utility.graphics import change_frame

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
        
        # Variables
        self.button_width = 18
        
        # Creating components
        self.__create_images()
        self.__create_widgets()
        self.__create_commands()

    #############################################################
    #    __create_images
    #############################################################
    def __create_images( self ):
        """
        Method used to create images.
        """

        # Logo image
        self.logo_img = ImageTk.PhotoImage( Image.open( "../img/images/logo.png" ).resize( ( 350, 200 ) ) )
        self.logo_label = tk.Label( self, image = self.logo_img )
        self.logo_label.place( anchor = "center", relx = 0.5, rely = 0.35 )
        
        # Circle
        #self.circle_img = ImageTk.PhotoImage( Image.open( "../img/images/circle.png" ).resize( ( 350, 300 ) ) )
        #self.circle_label = tk.Label( self, image = self.circle_img )
        #self.circle_label.place( anchor = "center", relx = 0.5, rely = 0.35 )
        #self.circle_label.config( highlightthickness = 0, bd = 0, bg = "white", fg = "white" )
        
    #############################################################
    #    __create_widgets
    #############################################################
    def __create_widgets( self ):
        """
        Method used to create basic frame widgets.
        """
        
        # Password generator button
        switch_creator = lambda: change_frame( self, password_creator )
        self.passwd_gen_button = ttk.Button( self, text = "Password generator", command = switch_creator )
        self.passwd_gen_button.config( cursor = "hand2", width = self.button_width )
        self.passwd_gen_button.place( anchor = "center", relx = 0.5, rely = 0.55 )
        
        # Password manager button
        switch_manager = lambda: change_frame( self, password_manager )
        self.passwd_man_button = ttk.Button( self, text = "Password manager", command = switch_manager )
        self.passwd_man_button.config( cursor = "hand2", width = self.button_width )
        self.passwd_man_button.place( anchor = "center", relx = 0.5, rely = 0.6 )

        # Settings button
        switch_settings = lambda: change_frame( self, settings )
        self.settings_button = ttk.Button( self, text = "Settings", command = switch_settings )
        self.settings_button.config( cursor = "hand2", width = self.button_width )
        self.settings_button.place( anchor = "center", relx = 0.5, rely = 0.65 )

    #############################################################
    #    __create_commands
    #############################################################
    def __create_commands( self ):
        """
        Method used to create basic keyboard commands.
        """

        # Cursor commands
        self.passwd_gen_button.focus_set()
        self.passwd_gen_button.bind( "<Down>", lambda e: self.passwd_man_button.focus_set() )
        self.passwd_man_button.bind( "<Up>", lambda e: self.passwd_gen_button.focus_set() )
        self.passwd_man_button.bind( "<Down>", lambda e: self.settings_button.focus_set() )
        self.settings_button.bind( "<Up>", lambda e: self.passwd_man_button.focus_set() )
        
        # Enter commands
        self.settings_button.bind( "<Return>", lambda e: change_frame( self, settings ) )
        self.passwd_gen_button.bind( "<Return>", lambda e: change_frame( self, password_creator ) )
        self.passwd_man_button.bind( "<Return>", lambda e: change_frame( self, password_manager ) )