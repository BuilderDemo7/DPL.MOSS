# Driver: Parallel Lines MOSS
MOSS or **M**od **O**riented **S**cripting **S**ystem is a plugin that integrates Lua in Driver: Parallel Lines (2007),
 with this mod you can script your own Lua scripts to modify behaviours in the game such as exploding cars, giving infinite health,
 create helicopters, teleport to random locations, etc.
 
Lua is a dynamic programming language which was chosen because it's fast, lightweight and simple to use,
 when you make changes to your script while the game runs and then restart the game, the new changes of that script will be applied unlike plugins written in C++.
 
# Installation
You can download it from the (releases)[https://github.com/BuilderDemo7/DPL.MOSS/releases] section of this repository, all you have to do is extract all the files inside the .zip file into
 the same directory as your DriverParallelLines.exe file (main directory of the game)
 
# Developing Mods
Quick step by step tutorial on how to develop mods with MOSS:

## Setup
Create a folder called 'moss_scripts' in the main directory of the game, that's where you should place your Lua scripts to be loaded in the game

## Scripting and Documentation
Of course you need basic skills with Lua and the documentation of all functions for making mods which you can see by clicking (here)[https://raw.githubusercontent.com/BuilderDemo7/DPL.MOSS/refs/heads/master/function_list.txt]
 or you can (download)[https://github.com/BuilderDemo7/DPL.MOSS/blob/master/function_list.txt] the functions list from this repository.

## Samples
*TO BE ADDED ...*

# Building
You will need Visual Studio 2017 (v141) or greater to build, no multi-platform project files were made so far (such as CMake or GCC).