<div align="center">
  
  <a href="" title="OS">![OS](https://img.shields.io/badge/os-Windows-blue?cacheSeconds=3600)</a>
  <a href="" title="GitHub Release">![GitHub Release](https://img.shields.io/github/v/release/ilvoron/SnakeGameC?cacheSeconds=300)</a>
  <a href="" title="GitHub License">![GitHub License](https://img.shields.io/github/license/ilvoron/SnakeGameC?cacheSeconds=3600)</a>
  <a href="" title="GitHub Downloads">![GitHub Downloads](https://img.shields.io/github/downloads/ilvoron/SnakeGameC/total?cacheSeconds=300)</a>
  
</div>

<div align="center">
 <picture>
   <source srcset="promo/snake_logo.png" width="128px" alt="Snake Game Logo" />
   <img src="promo/snake_logo.png" width="128px" alt="Snake Game Logo" />
 </picture>
</div>

<h1 align="center">snake-game-c-win</h1>

<p align="center">A console-based snake game for Windows, written in C.</p>

<p align="center">
  <picture>
    <source srcset="promo/snake_cover.png" height="539px"/>
    <img src="promo/snake_cover.png" height="539px" alt="Snake Game Cover" />
  </picture>
  <picture>
     <source srcset="promo/snake_screenshot_1.png" height="714px"/>
     <img src="promo/snake_screenshot_1.png" height="714px" alt="Snake Game Screenshot 1" />
  </picture>
  <picture>
     <source srcset="promo/snake_screenshot_2.png" height="357px"/>
     <img src="promo/snake_screenshot_2.png" height="357px" alt="Snake Game Screenshot 2" />
  </picture>
  <picture>
     <source srcset="promo/snake_screenshot_3.png" height="357px"/>
     <img src="promo/snake_screenshot_3.png" height="357px" alt="Snake Game Screenshot 3" />
  </picture>
</p>

## Overview

**snake-game-c-win** is a simple console-based snake game built for Windows, developed in C.  
This project was created as part of a university course, designed to teach students the fundamentals of **team-based modular programming**.  

Each team member was responsible for designing and implementing a separate module, which was later integrated into a single project.  
This approach allowed participants to work independently while also learning to collaborate in a structured software development environment.

## System Requirements
- **OS**: Windows XP or higher

## Build Requirements
To build the executable, you will need:
- **GCC 13.2.0** (Recommended: [MinGW-w64 (UCRT)](https://winlibs.com/))
- **GNU Make** (Recommended: [GnuWin Make](https://gnuwin32.sourceforge.net/packages/make.htm))

### Build Instructions
1. Clone the repository:
   ```sh
   git clone https://github.com/ilvoron/SnakeGameC.git
   cd SnakeGameC
   ```
2. Build the project using `make`:
   ```sh
   make
   ```
3. Run the compiled executable:
   ```sh
   ./snake.exe
   ```
4. To clean up temporary build files, use:
   ```sh
   make clean
   ```

## Developers

| Module | Developer |
| ------ | --------- |
| Interface | [ilvoron](https://github.com/ilvoron) |
| Controller | [Fazdo](https://github.com/Fazdo) |
| Board | [AlenaBls](https://github.com/AlenaBls) |
| Snake Logic | [entyziast](https://github.com/entyziast) |
