# How to play

The game is played on a grid. First player is X and the second player is O. Both of the players take turns writing their symbols in a cell. When a player writes their symbol in a cell, the neighbours are blocked and the other player is not able to play on the blocked cells (shown shaded in the following diagrams). The goal of the game is to block all the cells and leave no place for the other player to move. The first player unable to move loses.

For example, in the following game player X wins because O has nowhere to play:

![alt text](http://www.papg.com/images/Obstruction.gif)

# Build & Run

For a better experience use a terminal size of 80x24 and a font size of 12.

You will need a standards-compliant C compiler, the standard C library with header files, and make. On Debian GNU/Linux and derivatives, you can install these with

	$ apt install build-essential

After that clone the repository and cd into it

	$ git clone https://github.com/xemeds/obstruction-game.git

	$ cd obstruction-game

Build and run with

	$ make

	$ ./main

# References

Description and Images of the game: [papg.com](http://www.papg.com/)

# License

This project is under the [MIT](https://github.com/xemeds/obstruction-game/blob/master/LICENSE) license.
