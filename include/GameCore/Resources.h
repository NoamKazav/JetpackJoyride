#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include "Utils/GameConstants.h"
#include "Utils/ObjectType.h"

class Resources {
public:
    static Resources& getInstance();

    const sf::Texture& getObjectTexture(ObjectType type) const;
    const sf::Texture& getButtonTexture(const std::string& key) const;
    const sf::Texture& getBackgroundTexture(const std::string& key) const;

    const sf::Font& getFont() const;
    const std::vector<sf::IntRect>* getAnimationFrames(const std::string& key) const;
    const sf::SoundBuffer& getSoundBuffer(SoundType type) const;
    void playSound(SoundType type);
    void stopSound(SoundType type);
    void loadBestScores();
    void saveBestScore(float score, const std::string& name);
    void playBackgroundMusic();
    void stopBackgroundMusic();

    std::vector<std::pair<std::string, float>> getBestScores() const;
    float getBestScore() const;
private:
    Resources();
    Resources(const Resources&) = delete;
    Resources& operator=(const Resources&) = delete;

    void loadTextures();
    void loadFont();
    void setupAnimationFrames();
    void loadSoundBuffers();

    std::unordered_map<ObjectType, sf::Texture> m_objectTextures;
    std::unordered_map<std::string, sf::Texture> m_buttonTextures;
    std::unordered_map<std::string, sf::Texture> m_backgroundTextures;
    std::unordered_map<SoundType, sf::SoundBuffer> m_soundBuffers;

    sf::Font m_font;
    std::unordered_map<std::string, std::vector<sf::IntRect>> m_animationMap;

    std::list<sf::Sound> m_activeSounds;
    void cleanUpSounds(); 
    sf::Music m_backgroundMusic;
    std::vector<std::pair<std::string, float>> m_bestScores;
    const std::string m_scoresFile = GameConstants::SCORES_FILE_NAME;


};
