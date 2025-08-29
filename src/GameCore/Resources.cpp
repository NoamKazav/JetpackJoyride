#include "GameCore/Resources.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

using namespace GameConstants;

Resources::Resources() {
    loadTextures();
    loadFont(); 
    setupAnimationFrames();
    loadBestScores();
    loadSoundBuffers();
}

Resources& Resources::getInstance() {
    static Resources instance;
    return instance;
}

void Resources::loadTextures() {
    for (const auto& [type, filename] : OBJECT_TEXTURES) {
        sf::Texture tex;
        if (!tex.loadFromFile(filename))
            throw std::runtime_error("Failed to load object texture: " + filename);
        m_objectTextures[type] = std::move(tex);
    }

    for (const auto& [key, filename] : BUTTON_TEXTURES) {
        sf::Texture tex;
        if (!tex.loadFromFile(filename))
            throw std::runtime_error("Failed to load button texture: " + filename);
        m_buttonTextures[key] = std::move(tex);
    }

    for (const auto& [key, filename] : BACKGROUND_TEXTURES) {
        sf::Texture tex;
        if (!tex.loadFromFile(filename))
            throw std::runtime_error("Failed to load background texture: " + filename);
        m_backgroundTextures[key] = std::move(tex);
    }
}

void Resources::loadFont() {
    if (!m_font.loadFromFile(FONT_FILE_NAME))
        throw std::runtime_error("Failed to load font");
}

const sf::Texture& Resources::getObjectTexture(ObjectType type) const {
    auto it = m_objectTextures.find(type);
    if (it == m_objectTextures.end())
        throw std::runtime_error("Texture not found for ObjectType");
    return it->second;
}

const sf::Texture& Resources::getButtonTexture(const std::string& key) const {
    auto it = m_buttonTextures.find(key);
    if (it == m_buttonTextures.end())
        throw std::runtime_error("Button texture not found: " + key);
    return it->second;
}

const sf::Texture& Resources::getBackgroundTexture(const std::string& key) const {
    auto it = m_backgroundTextures.find(key);
    if (it == m_backgroundTextures.end())
        throw std::runtime_error("Background texture not found: " + key);
    return it->second;
}

const sf::Font& Resources::getFont() const {
    return m_font;
}

const std::vector<sf::IntRect>* Resources::getAnimationFrames(const std::string& key) const {
    auto it = m_animationMap.find(key);
    return (it != m_animationMap.end()) ? &it->second : nullptr;
}

const sf::SoundBuffer& Resources::getSoundBuffer(SoundType type) const {
    auto it = m_soundBuffers.find(type);
    if (it == m_soundBuffers.end())
        throw std::runtime_error("Sound buffer not found for type");
    return it->second;
}


void Resources::setupAnimationFrames() {
    auto append = [&](const std::string& key, int middleGap, sf::Vector2i size, int num, int loc = 0) {
        sf::Vector2i start{ size.x * loc + middleGap * loc, 0 };
        for (int i = 0; i < num; ++i) {
            m_animationMap[key].emplace_back(start, size);
            start.x += size.x + middleGap;
        }
        };

    append("walking berry", 0, { 75, 100 }, 3);
    append("jumping berry", 0, { 75, 100 }, 1, 3);
    append("walking tank", 23, { 135, 100 }, 3);
    append("jumping tank", 0, { 135, 125 }, 1);
    append("Fall", 0, { 107, 100 }, 4);
    append("Dead", 0, { 107, 100 }, 5);
    append("Laser", 0, { 101, 420 }, 4);
    append("Light", 0, { 300, 236 }, 6);
    append("coin", 0, { 40, 40 }, 8);
    append("Scientists", 8, { 45, 67 }, 3);
    append("Missile", 0, { 100, 64 }, 7);
    append("FirstWarning", 0, { 65, 100 }, 4);
    append("SecondWarning", 0, { 100, 100 }, 2);
    append("Exhaust", 0, { 26, 45 }, 6);
    append("Intro", 0, { 649, 240 }, 10);
    append("Intro", 0, { 59, 60 }, 1);
    append("Bubble", 0, { 150, 150 }, 1);
}

void Resources::loadSoundBuffers() {
    for (const auto& [type, filename] : GameConstants::SOUND_FILES) {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(filename))
            throw std::runtime_error("Failed to load sound file: " + filename);
        m_soundBuffers[type] = std::move(buffer);
    }
}

void Resources::playSound(SoundType type) {
    cleanUpSounds();

    auto it = m_soundBuffers.find(type);
    if (it == m_soundBuffers.end())
        throw std::runtime_error("Sound buffer not found for type");

    sf::Sound sound;
    sound.setBuffer(it->second);
    sound.setVolume(GameConstants::SOUND_VOLUME);
    if (sound.getStatus() != sf::Sound::Stopped) {
        std::cerr << "Warning: sf::Sound is invalid or already playing before play(). Skipping.\n";
        return;
    }
    m_activeSounds.push_back(std::move(sound));
    m_activeSounds.back().play(); 
}

void Resources::stopSound(SoundType type)
{
    const auto& buffer = getSoundBuffer(type);

    for (auto& sound : m_activeSounds) {
        if (sound.getBuffer() == &buffer && sound.getStatus() == sf::Sound::Playing) {
            sound.stop();
            break; 
        }
    }
}

void Resources::cleanUpSounds() {
    m_activeSounds.remove_if([](const sf::Sound& s) {
        return s.getStatus() == sf::Sound::Stopped;
        });
}

void Resources::loadBestScores() {
    std::ifstream file(m_scoresFile);
    if (!file) {
        std::ofstream createFile(m_scoresFile);
        if (!createFile)
            throw std::runtime_error("Failed to create best scores file: " + m_scoresFile);

        m_bestScores.clear();
        return;
    }

    m_bestScores.clear();
    std::string name;
    float score;
    while (file >> name >> score)
        m_bestScores.emplace_back(name, score);
}


void Resources::saveBestScore(float score, const std::string& name) {
    m_bestScores.emplace_back(name, score);

    std::sort(m_bestScores.begin(), m_bestScores.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    if (m_bestScores.size() > 5)
        m_bestScores.resize(5);

    std::ofstream file(m_scoresFile);
    if (!file)
        throw std::runtime_error("Failed to open best scores file for writing: " + m_scoresFile);

    for (const auto& [n, s] : m_bestScores)
        file << n << " " << static_cast<int>(s) << '\n';
}



void Resources::playBackgroundMusic() {
    if (!m_backgroundMusic.openFromFile("JetpackJoyrideMusic.wav")) {
        throw std::runtime_error("Failed to open background music");
    }

    m_backgroundMusic.setLoop(true);
    m_backgroundMusic.setVolume(GameConstants::MUSIC_VOLUME);
    m_backgroundMusic.play();
}

void Resources::stopBackgroundMusic() {
    if (m_backgroundMusic.getStatus() == sf::Music::Playing) {
        m_backgroundMusic.stop();
    }
}

std::vector<std::pair<std::string, float>> Resources::getBestScores() const {
    return m_bestScores;
}

float Resources::getBestScore() const {
    return m_bestScores.empty() ? 0.f : m_bestScores.front().second;
}
