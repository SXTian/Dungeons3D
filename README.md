Dungeons3D
==========
In case you are wondering about the name: I know I want to eventually turn this into a Dungeon Crawl game. I know I want it to be in 3D.

##Overview

####Motivation
I love making game engines, but I've never made a decent engine from scratch all by myself.  Here we go!

####Progress so far
I started with a boilerplate implementation of a pretty simple messaging system - IEventMessage.cpp/h, MessagingSystem.cpp/h

I then introduced a Systems Interface, and started implementation of the Graphics System - GraphicsSystem.cpp/h

So Far, the graphics system has shaders, .3DS model loading (as well as my own homebrew mesh format for testing purposes), camera and perspective transformations, support for different views, and abstracts away all that nasty OpenGL code.  Everything is laid out in a pretty straightforward OO design.

I also have a Win32API system that gets keyboard input and feeds it to my graphics system via the messaging system.

You can expect to see some lighting implementations coming soon!!
