This C project, developed as part of an Advanced Programming course, revolves around the "Rick and Morty" series. It consists of four main files:

Jerry.h: This header file defines the structs used in the project, along with the function signatures. It also implements compilation guards to prevent code duplication during compilation.

Jerry.c: In this file, you'll find various functions that facilitate the program's functionality. These functions initialize Jerry characters, planets, physical characteristics, and origins. They also check for the existence of physical characteristics, add new characteristics, delete existing ones, and print the details of Jerry characters and planets.

Defs.h: This header file contains two enums used in various functions throughout the program.

ManageJerries: This file is split into two parts: one for reading data from a configuration file and the other for managing the functionalities that allow Morty to oversee all the Jerrys he has collected during his adventures.

The section for reading from the file begins by extracting the number of planets and Jerrys from the configuration file and initializing the necessary variables. It then parses the file content and separates values using delimiters like colons, commas, and tabs. It converts strings to doubles and sets up a menu system to interact with the user.

The menu options include printing all Jerrys, printing all planets, adding a new characteristic to a Jerry, deleting a characteristic, printing a Jerry by choosing a planet, and printing a Jerry by selecting a characteristic. Finally, option 7 cleans up and exits the program.

This project is well-organized and implements various features, including dynamic memory allocation and data manipulation. It offers Morty the tools he needs to manage his collection of Jerrys.
