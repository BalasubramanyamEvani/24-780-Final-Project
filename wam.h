// Begin header guard to prevent multiple inclusions
#ifndef wam_h
#define wam_h

// Include necessary libraries
#include <string>

#include "yspng.h"
#include "yssimplesound.h"

// Define constant for PI
#define PI 3.1415926

// Base class for game objects in Whack-A-Mole game
class WamGameObject {
   public:
    // Constructor to initialize the object
    WamGameObject() {
        x = 0;
        y = 0;
        hitPoints = 0;
        prevhit = false;
    };
    // Virtual destructor for proper cleanup in derived classes
    virtual ~WamGameObject() = default;
    // Other member functions
    // Initialize the game object
    bool Initialize(void);
    // Function to draw the object
    void Draw(void);
    // Update the object's position
    void UpdatePos(int x, int y);
    // Function to handle hit event
    int Hit(double mouseX, double mouseY);

   protected:
    // Member variables
    int x, y;                                // Position of the game object
    bool prevhit;                            // Flag to check if it was hit previously
    const std::string hitMusic = "hit.wav";  // File name for hit sound
    std::string image;                       // File name for object's image
    YsRawPngDecoder png;                     // PNG decoder for the image
    int hitPoints;                           // Hit points of the object
    void playHitMusic(void);                 // Function to play hit sound
    YsSoundPlayer player;                    // Sound player for playing sounds
    YsSoundPlayer::SoundData wav;            // Sound data for hit sound
};

// Derived class for "Good Moles" in the game
class WamGoodMole : public WamGameObject {
   public:
    WamGoodMole(int x, int y);
    ~WamGoodMole() = default;
};

// Derived class for "Evil Moles" in the game
class WamEvilMole : public WamGameObject {
   public:
    WamEvilMole(int x, int y);
    ~WamEvilMole() = default;
};

// Class to represent the game scene
class WamGameScene {
   public:
    // Function to start playing the game
    int play(void);
    // Constructor to initialize the game scene
    WamGameScene() {
        points = 0;
        timer = 20;
    };
    // Default destructor
    ~WamGameScene() = default;

   private:
    // Member variables
    int points;                                               // Points scored in the game
    int timer;                                                // Timer for game duration
    const int numGoodMoles = 16;                              // Number of "Good Moles" in the game
    const int numEvilMoles = 4;                               // Number of "Evil Moles" in the game
    const std::string title = "Whack-A-Mole!";                // Title of the game
    const std::string timerTitle = "Timer: ";                 // Title for the timer
    std::vector<std::unique_ptr<WamGameObject>> gameObjects;  // Vector of game objects
    std::vector<int> x_values = {150, 250, 350, 450, 550};    // Predefined X positions
    std::vector<int> y_values = {200, 300, 400, 500};         // Predefined Y positions

    // Other member functions
    void Initialize(void);        // Function to initialize the game scene
    void RenderBackground(void);  // Render the background of the scene
    void RenderInfo(void);        // Render game information (score, timer)
    // Draws two ellipses (used for coins)
    void drawCoinEllipse(int cx, int cy, int rx, int ry, int num_segments);
};

#endif /* wam_h */
