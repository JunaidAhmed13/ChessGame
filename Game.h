#pragma once
#include "Board.h"
#include "AI.h"
#include <SFML/Graphics.hpp>
#include <string>

class Game {
public:
    Game();
    void run();
private:
    Board board;
    AI ai;
    int selectedX = -1, selectedY = -1;
    Color currentTurn;

    // Auth and menu state
    enum State { AUTH, SIGNUP, MENU, GAME };
    State state = AUTH;

    // Auth variables
    std::string loginUser, loginPass, signupUser, signupPass;
    bool loginActive = true;
    bool signupActive = true;
    std::string authMsg, signupMsg;

    // Menu/game state
    bool vsAI = false;
    bool gameOver = false;
    bool pieceSelected = false;
    bool isMuted = false;
    bool isPaused = false;

    // SFML window
    sf::RenderWindow window;

    // Helper functions for file-based user management
    bool checkUser(const std::string& username, const std::string& password);
    bool userExists(const std::string& username);
    void addUser(const std::string& username, const std::string& password);
};
