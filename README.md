# How to play

The game is played on a grid; 6 x 6 is a good size. One player is 'O' and the other is 'X'.
Players take turns in writing their symbol in a cell. The restriction is that you can only play in a cell if all its neighbours are empty (shown shaded in the following diagrams).
The first player unable to move loses.

For example, in the following game player 'X' wins because 'O' has nowhere to play:

![alt text](http://www.papg.com/images/Obstruction.gif)

# Build & Run

For a better experience use a terminal size of 88x25 and a font size of 12.

You will need a standards-compliant C compiler, the standard C library with header files, and make. On Debian GNU/Linux and derivatives, you can install these with

	$ apt-get install build-essential

After that, build and run with

	$ make obstruction

	$ ./obstruction

# Referances

Description and Images of the game: www.papg.com

# License

This project is under the [MIT](https://github.com/xemeds/obstruction-game/blob/master/LICENSE) license.
