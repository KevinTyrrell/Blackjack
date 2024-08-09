cmake_minimum_required(VERSION 3.28)
project(Blackjack)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/include)

add_executable(Blackjack
        src/include/Banner.h
        src/include/Card.h
        src/include/Deck.h
        src/include/InputOutput.h
        src/include/MainMenu.h
        src/include/Table.h
        src/include/TextboxStream.h
        src/Banner.cpp
        src/Card.cpp
        src/Deck.cpp
        src/Game.cpp
        src/InputOutput.cpp
        src/MainMenu.cpp
        src/Table.cpp
        src/TextboxStream.cpp)
