#pragma once
#include <SFML/System.hpp>
#include <string>
#include <vector>
#include <utility>
#include "Utils/ObjectType.h"

namespace GameConstants {
    inline const float SCREEN_WIDTH = 1300.f;
    inline const float SCREEN_HEIGHT = 600.f;
    inline const  float GROUND_Y = 550.f;
    inline const float GRAVITY = 500.f;
    inline const int MUSIC_VOLUME = 10;
    inline const int SOUND_VOLUME = 20;
    inline const int MISSILE_SPEED = 500;
    inline const int MARGIN = static_cast<int>(SCREEN_HEIGHT / 12.f);
    inline const int DEFAULT_START_POINT = static_cast<int>(SCREEN_HEIGHT - MARGIN);
    inline const float SCROLL_SPEED = 300.f;
    inline const char* SCORES_FILE_NAME = "scores.txt";
    inline const std::vector<std::string> HELP_SLIDES = {
    "help1", "help2", "help3"
    };
    const float STEP = 100.f;
    const int NUMLASERS = 1;
    const float MINANGLE = -60.f;
    const float MAXANGLE = 60.f;
    inline const float INTRO_FRAME_TIME = 0.15f;
    inline const float LOADING_DURATION = 5.0f;
    inline const float DEFAULT_BUTTON_SCALE = 0.5f;
    inline const unsigned int STATUSBAR_TEXT_SIZE = 24;
    inline const sf::Vector2f SCIENTIST_INITIAL_VELOCITY = { -100.f, 0.f };
    inline const float PI = 3.14159265f;
    inline const float TWO_PI = 2.f * PI;
    inline const float DEG_TO_RAD = GameConstants::PI / 180.f;
    inline const float LASER_MIN_ROTATION = -90.f;
    inline const float LASER_MAX_ROTATION = 90.f;
    inline const float ARC_PATTERN_TOTAL_ANGLE = 1.0f;
    inline const float ARC_PATTERN_LAYER_RADIUS_STEP = 20.f;
    inline const float ARC_PATTERN_LAYER_HEIGHT_STEP = 60.f;
    inline const int ARC_PATTERN_MIN_COINS_PER_LAYER = 2;
    inline const float DEATH_SCROLL_DAMPING = 0.97f;
    inline const float MAX_SCROLL_SPEED = 600.f;
    inline const float SCROLL_ACCELERATION = 2.f;
    inline const float MIN_SCROLL_SPEED = 1.f;
    inline const float INTRO_BACKGROUND_FADEOUT_X = 200.f;
    inline const float COMMAND_BUTTON_SCALE = 0.8f;
    inline const int EXTRA_BACKGROUND_TILES = 2;
    inline const float DISTANCE_SCALING_FACTOR = 100.f;
    inline const unsigned int GAME_OVER_TITLE_SIZE = 60;
    inline const unsigned int GAME_OVER_INSTRUCTION_SIZE = 30;
    inline const char* GAME_OVER_TITLE_TEXT = "Game Over";
    inline const char* GAME_OVER_INSTRUCTION_TEXT = "Press Enter to return to menu";
    inline const sf::Vector2f GAME_OVER_TITLE_POSITION = { 500.f, 200.f };
    inline const sf::Vector2f GAME_OVER_INSTRUCTION_POSITION = { 430.f, 300.f };
    inline const float SCORES_START_Y = 150.f;
    inline const float SCORES_LINE_SPACING = 60.f;
    inline const float SCORES_TEXT_X = 200.f;
    inline const unsigned int SCORES_TEXT_SIZE = 40;
    inline const float SCORES_BUTTON_MARGIN = 20.f;
    inline const float INSTRUCTIONS_BUTTON_Y_OFFSET = 100.f;
    inline const float INSTRUCTIONS_BUTTON_SIDE_MARGIN = 30.f;
    inline const float INTRO_DURATION = 1.0f;
    inline const unsigned int LOADING_TEXT_SIZE = 50;
    inline const float LOADING_TEXT_Y_OFFSET = 60.f;
    inline const float PERCENTAGE_MAX = 100.f;
    inline const unsigned int MAX_NAME_LENGTH = 20;
    inline const std::string FONT_PATH = "C:/Windows/Fonts/arial.ttf";
    inline const char* NEW_HIGHSCORE_PROMPT_TEXT = "New High Score! Enter your name:";
    inline const unsigned int PROMPT_TEXT_SIZE = 32;
    inline const unsigned int NAME_TEXT_SIZE = 30;
    inline const sf::Vector2f NAME_INPUT_BOX_SIZE = { 400.f, 40.f };
    inline const float PROMPT_Y = 150.f;
    inline const float INPUT_TEXT_Y = 220.f;
    inline const float INPUT_BOX_POS_X = 95.f;
    inline const float INPUT_BOX_POS_Y = 215.f;
    inline const sf::Color NAME_INPUT_BOX_FILL_COLOR = sf::Color(0, 0, 0, 150);
    inline const float NAME_INPUT_BOX_OUTLINE_THICKNESS = 2.f;
    inline const float PAUSE_BUTTON_OFFSET_X = 100.f;
    inline const float PAUSE_BUTTON_POS_Y = 20.f;
    inline const float DEFAULT_GIFT_DURATION = 10.f;
    inline const float MENU_TITLE_SCALE_X = 0.4f;
    inline const float MENU_TITLE_SCALE_Y = MENU_TITLE_SCALE_X * 1.3f;
    inline const float MENU_TITLE_Y_OFFSET = 30.f;
    inline const float MENU_TITLE_EXTRA_Y_SHIFT = 50.f;
    inline const float MENU_BUTTONS_CENTER_Y = 400.f;
    inline const float MENU_BUTTONS_SPACING = 30.f;
    inline const sf::Vector2f STATUSBAR_SIZE = { 250.f, 110.f };
    inline const sf::Vector2f STATUSBAR_POSITION = { 10.f, 10.f };
    inline const sf::Vector2f STATUSBAR_DISTANCE_LABEL_POS = { 20.f, 20.f };
    inline const sf::Vector2f STATUSBAR_DISTANCE_TEXT_POS = { 160.f, 20.f };
    inline const sf::Vector2f STATUSBAR_BEST_TEXT_POS = { 20.f, 50.f };
    inline const sf::Vector2f STATUSBAR_COIN_LABEL_POS = { 20.f, 80.f };
    inline const sf::Vector2f STATUSBAR_COIN_TEXT_POS = { 130.f, 80.f };
    inline const sf::Vector2f STATUSBAR_COIN_ICON_POSITION = { 200.f, 80.f };
    inline const float MISSILE_FIXED_Y = 400.f;
    inline const float MISSILE_WARNING_OFFSET_X = 80.f;
    inline const float PLAYER_INITIAL_X = 400.f;
    inline const float PLAYER_INITIAL_Y = 450.f;
    inline const float PLAYER_MIN_Y = 0.f;
    inline const float PLAYER_ANCHOR_LEFT_OFFSET = 70.f;
    inline const sf::Vector2f SCIENTIST_VELOCITY_RIGHT = { 50.f, 0.f };
    inline const float COIN_SPAWN_OFFSET_X = 100.f;
    inline const float COIN_BASE_Y = 250.f;
    inline const float COIN_Y_RANDOM_RANGE = 100.f;

    inline const int COIN_LINE_COUNT_MIN = 5;
    inline const int COIN_LINE_COUNT_VARIATION = 4;
    inline const float COIN_LINE_SPACING = 45.f;
    inline const float COIN_DISTANCE = 1000.f;

    inline const float COIN_DOUBLE_ROW_SPACING = 40.f;

    inline const int ARC_PATTERN_NUM_COINS = 10;
    inline const int ARC_PATTERN_NUM_LAYERS = 3;
    inline const float ARC_PATTERN_RADIUS = 250.f;
    inline const float ARC_PATTERN_Y_OFFSET = 100.f;

    inline const int CIRCLE_PATTERN_NUM_COINS = 10;
    inline const float CIRCLE_PATTERN_RADIUS = 60.f;
    inline const float CIRCLE_PATTERN_X_OFFSET = 100.f;

    inline const int WAVE_PATTERN_NUM_COINS = 15;
    inline const float WAVE_PATTERN_AMPLITUDE = 35.f;
    inline const float WAVE_PATTERN_WAVELENGTH = 60.f;
    inline const float WAVE_PATTERN_SPIRAL_FACTOR = 0.5f;

    inline const float GIFT_SPAWN_OFFSET_X = 100.f;
    inline const float GIFT_BASE_Y = 100.f;
    inline const float GIFT_Y_RANDOM_RANGE = 300.f;
    inline const float GIFT_SPAWN_INTERVAL_MIN = 13.f;
    inline const int GIFT_SPAWN_INTERVAL_RANGE = 6;  
    inline const int NUM_GIFT_TYPES = 2;

    inline const float LASER_SPAWN_INTERVAL_MIN = 4.f;
    inline const int LASER_SPAWN_INTERVAL_VARIATION = 500;
    inline const float LASER_SCALE = 0.6f;
    inline const float LASER_ROTATION_HORIZONTAL = 0.f;
    inline const float LASER_ROTATION_VERTICAL = 90.f;
    inline const float LASER_VERTICAL_SCREEN_MARGIN = 50.f;
    inline const float LASER_SPAWN_OFFSET_X = 200.f;

    inline const float LIGHT_SPAWN_Y = 30.f;

    inline const float SCIENTIST_SPAWN_OFFSET_X = 100.f;
    inline const float SCIENTIST_SPAWN_MIN_INTERVAL = 0.25f;
    inline const float SCIENTIST_SPAWN_MAX_INTERVAL = 3.0f;

    inline const float MISSILE_SECOND_WARNING_TIME = 2.f;
    inline const float MISSILE_FIRE_TIME = 3.f;

    inline const float DEAD_STATE_GAME_OVER_DELAY = 2.0f;

    inline const float FALLING_SPEED = 300.f;

    inline const float JETTING_UPWARD_SPEED = -350.f;
    inline const float JET_FLAME_OFFSET_X = 12.f;
    inline const float JET_FLAME_OFFSET_Y = 90.f;
    inline const float SHIELD_MARGIN = 10.f;
    inline const sf::Color SHIELD_TEXTURE_COLOR = sf::Color(255, 255, 255, 200);
    inline const float SHIELD_RADIUS_OFFSET = 5.f;
    inline const float SHIELD_OUTLINE_THICKNESS = 3.f;
    inline const sf::Color SHIELD_FILL_COLOR = sf::Color(100, 200, 255, 50);
    inline const sf::Color SHIELD_OUTLINE_COLOR = sf::Color(0, 180, 255, 60);


    inline const std::vector<std::pair<std::string, std::string>> BACKGROUND_TEXTURES = {
        {"intro", "y_StartOfHallL.png"},
        { "menu", "GameMenu.png" },
        { "game", "Hall.png" },
        { "help1", "help1.png" },
        { "help2", "help2.png" },
        { "help3", "help3.png" },
        { "title", "Title.png" },
        {"loading", "loading.png"}
    };

    inline const std::vector<std::pair<std::string, std::string>> BUTTON_TEXTURES = {
        { "pause", "pause.png" },
        { "back", "back.png" },
        { "back1", "back1.png" },
        { "startGame", "startGame.png"},
        { "continue", "continue.png"},
        { "backToMenu", "backToMenu.png"},
        {"rules", "rules.png" },
        {"record", "record.png"},
        {"restart", "restart.png"}
    };

    inline const std::vector<std::pair<ObjectType, std::string>> OBJECT_TEXTURES = {
        { ObjectType::Scientists, "Scientist.png" },
        { ObjectType::Missile, "Missile.png" },
        { ObjectType::Laser, "Laser.png" },
        { ObjectType::Coin, "Coin.png" },
        { ObjectType::Light, "Lights.png" },
        { ObjectType::Player, "JetpackWalking.png" },
        { ObjectType::Tank, "SuperPowerTank2.png" },
        { ObjectType::JetTank, "SuperPowerFlyTank.png" },
        { ObjectType::FirstAlert, "MissileWarning.png" },
        { ObjectType::SecondAlert, "MissileIncoming.png" },
        { ObjectType::Dead, "PlayerDead.png" },
        { ObjectType::Exhaust, "Exhaust.png" },
        { ObjectType::Intro, "y_StartOfHall.png" },
        { ObjectType::Gift, "PowerUpBox.png" },
        { ObjectType::Bubble, "bubble.png" }
        
    };

    inline const char* FONT_FILE_NAME = "New Athletic M54.ttf";

   
    inline const std::vector<std::pair<SoundType, std::string>> SOUND_FILES = {
    { SoundType::Coin,          "coin.wav" },
    { SoundType::Power,         "getPowerSound.wav" },
    { SoundType::MissileHit,    "hitSound.wav" },
    { SoundType::MissileAlarm,  "MissileAlarm.wav" },
    { SoundType::MissileLaunch, "missileLaunch.wav" },
    { SoundType::LaserHit,      "ZapperSound.wav" },
    { SoundType::ShieldSpeed,   "ShieldSpeed.ogg" },
    {SoundType::Explosion,   "i_StartingExplosion.ogg"}
    };

}
