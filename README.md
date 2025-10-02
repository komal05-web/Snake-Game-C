**🐍 Classic Snake Game in C Project Overview**
This is a complete, standalone implementation of the classic arcade game Snake, built using pure C.The game logic is focused on efficiency and simplicity, making it a great showcase for C programming fundamentals, including data structures, memory management, and game loop architecture. Depending on the version, it runs either in a terminal environment or utilizes the SDL library for basic graphics.
🕹️ **FeaturesClassic Gameplay:** Eat food, grow longer, and avoid walls and your own tail.Simple C Architecture: Minimal dependencies (or only a single major library like SDL/ncurses).Cross-Platform Ready: Easily compiled and run on Windows.
**How to Play Controls Action Key :** Move Up W or ↑ (Up Arrow)Move Down S or ↓ (Down Arrow)Move Left A or ← (Left Arrow)Move Right D or → (Right Arrow)Pause/ResumeP or Space bar Quit Q or Esc Building and Running LocallyTo run the game on your local machine, you need a C compiler (like GCC or Clang) installed.
1.Clone the Repository git clone (https://github.com/komal05-web/Snake-Game-C.git)
cd Snake-Game-C
2. Compile the Game (using GCC)Use the GCC compiler to build the executable.A. For Console/Terminal Version (e.g., using ncurses or simple I/O)# Example command (adjust for your specific libraries/source files)
gcc -o snake *.c -lncurses 
3. Run the GameOnce compiled, execute the program:./snake
LicenseThis project is licensed under the MIT License.
