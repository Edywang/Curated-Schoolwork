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
let keyF, keyLEFT, keyRIGHT;