#!/bin/env python
import matplotlib
import numpy as np
import argparse
# Purpose of this script is to take the data in ~/data and do some analysis and plot it, eventually
dataDir = "../data"

data = {
    "A0" : [],
    "A1" : [],
    "A2" : [],
    "A3" : [],
    "A4" : [],
    "A5" : [],
    "A6" : [],
    "A7" : [],
    "A8" : [],
    "A9" : []
}

with open("devttyACM0_2025_04_25.11.58.59.579.txt") as file:
    
