# Dumbkid

A sick ncurses program you can use to simulate talking to a kid.

![image](https://user-images.githubusercontent.com/76543296/181163781-8cea89cd-affe-4515-bbbe-c2a9e17d6c27.png)

It doesn't use multiple ncurses windows, which, looking back at it, would've made the program a lot easier to make and probably be more efficient, but whatever, the code is still decently optimized.

This was mainly made as a test project for me to learn making a full on project in C with a build system and everything.

# Building

On Linux, you'll need the ncurses header files.

You can get these on Debian-based distros with this command:

    sudo apt-get install libncurses5-dev libncursesw5-dev

Then compile this kid with make:

    make

This will output a binary called kid in the build folder, to run it do this:

    cd build
    ./kid

Sick.

# How to run this thingy on windows

You can use Cygwin, which sort of emulates the linux terminal environment, I think. Ncurses doesn't work on windows so I can't compile my own binary directly for it.
