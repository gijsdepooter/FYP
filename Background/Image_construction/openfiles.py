#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul 15 14:20:43 2022

@author: gijsdepooter

Ultrasound Raw data visualising


"""

import numpy as np
import os 
import sys
import matplotlib.pyplot as plt
from matplotlib import colors



img1 = np.load("/Users/gijsdepooter/Desktop/UROP/RFArrays/B_80,0_0,0.npy","r")

plt.rcParams["figure.figsize"] = [5,15]

FileStats = os.stat("/Users/gijsdepooter/Desktop/UROP/RFArrays/B_80,0_0,0.npy")
print('Size of file is', FileStats.st_size,'bytes')

plt.imshow(img1, cmap='gray', extent=[-4.65, 4.65, 37.9, 0 ],norm=colors.NoNorm())





    
    
