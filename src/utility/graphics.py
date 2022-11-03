#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Thr Nov 3 21:48:00 2022
Author: Gianluca Bianco
"""

#############################################################
#    change_frame
#############################################################
def change_frame( current_frame, new_frame ):
    """
    Function used to pass from a frame to another.

    Args:
        current_frame (tk.Frame / ttk.Frame): the current frame.
        new_frame (tj.Frame / ttk.Frame): the new frame
    """
    
    new_frame.tkraise( current_frame )
    current_frame.place_forget()