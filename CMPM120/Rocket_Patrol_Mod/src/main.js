/* Explanation of points
Starting Tier: Add your own (copyright-free) background music to the Play scene (10)
Novice Tier: Display the time remaining (in seconds) on the screen (15)
Intermediate Tier: Implement a new timing/scoring mechanism that adds time to the clock for successful hits (25)
S-Rank Tier: Implement a simultaneous two-player mode (50)
Design choices surrounding the two-player mode: I split the players' movable space in half and dedicated one half to each player.
I decided that if both players hit the same spaceship at the same time, both would reset and both hits would be counted (Kind of hard to replicate alone)
The spaceships do not collide with each other beyond being restricted in their own play spaces, I decided this would go against the cooperative nature.
*/


// Terminal command to start localhost web server: "python -m http.server"
console.log("JS File Loaded Successfully");
let config = {
    // Render type: OpenGL or Canvas; Choosing Canvas for our type of art
    type: Phaser.CANVAS,
    width: 640,
    height: 480,
    scene: [Menu, Play]
};
// Starting the Phaser game with the object config as a param
let game = new Phaser.Game(config);

// Reserve some keyboard variables
let keyF, keyLEFT, keyRIGHT, key4, key6, keyADD;