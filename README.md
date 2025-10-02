# Snake Game in C

A simple console-based implementation of the classic Snake game written in pure C. This project is ideal for learning C fundamentals like loops, conditionals, arrays, manual input handling, and cross-platform compatibility without relying on C++ features like enums or classes.

## Features
- Cross-platform: Compatible with Windows, macOS, and Linux using standard C compilers.
- Non-blocking keyboard input for responsive controls.
- Random fruit generation with collision avoidance on borders.
- Growing snake tail on eating fruit.
- Score tracking and game over detection.
- Direction lock to prevent 180° reversals.

## Requirements
- C compiler (e.g., GCC, Clang, or MSVC).
- Standard libraries only—no external dependencies.
- On macOS: Xcode Command Line Tools (install via `xcode-select --install`).
- On Linux: Build essentials (e.g., `sudo apt install build-essential` on Ubuntu).
- On Windows: Visual Studio or MinGW.

## Building the Game
1. Clone or download the repository (or save `snake.c`).
2. Open a terminal/command prompt in the project folder.
3. Compile the code:
gcc snake.c -o snake
text- On Windows, if using MinGW: Same command.
- If using Visual Studio: Open Developer Command Prompt and run `cl snake.c`.

## Running the Game
1. In the terminal:
./snake
text- On Windows: `snake.exe`.
2. The game board will appear. The snake starts in the center and is initially stopped.
3. Use keys to move (case-insensitive):
- `w`: Up
- `s`: Down
- `a`: Left
- `d`: Right
- `x`: Quit
4. Eat the fruit (`*`) to grow and score 10 points each time.
5. Avoid hitting the walls or your own tail (`o` segments; head is `O`).
6. The game speed is fixed (adjustable in code via delay functions).

## Code Structure
- **snake.c**: The single source file with all logic.
- `setup()`: Initializes game variables and positions.
- `draw()`: Clears the screen and renders the board.
- `input()`: Handles keyboard input (cross-platform).
- `logic()`: Updates movement, checks collisions, and handles fruit eating.
- `main()`: Sets up the game loop with delay.

## Customization
- Board size: Change `WIDTH` and `HEIGHT` defines.
- Speed: Modify the delay in `main()` (e.g., `usleep(100000)` for 100ms on Unix; lower = faster).
- Enhancements: Add wrap-around borders, variable speed based on score, or high-score saving with file I/O (using `fopen`/`fprintf`).

## Troubleshooting
- **No input response**: Ensure your terminal supports the input mode. On macOS/Linux, the code sets and resets terminal modes automatically.
- **Compilation errors**: Add `-std=c99` or `-std=c11` if needed (e.g., `gcc -std=c11 snake.c -o snake`).
- **Screen not clearing**: Verify `system("clear")` or `system("cls")` matches your OS.
- **Fruit on snake**: Rare, but add a loop in `logic()` to regenerate if it overlaps.

## License
This project is open-source under the MIT License. Feel free to fork and modify!

For questions or improvements, open an issue or pull request. Enjoy learning C! 🐍