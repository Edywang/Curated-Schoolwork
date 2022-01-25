// Terminal command to start localhost web server: "python -m http.server"
console.log("JS File Loaded Successfully");
let config = {
    // Render type: OpenGL or Canvas; Choosing Canvas for our type of art
    type: Phaser.CANVAS,
    width: 480, // TODO: We might want to change this
    height: 640, // TODO: We might want to change this
    scene: [Menu,Animation1,Level1,Animation2,Credits],
};
let gameConfig = {
    tileSize: 100,
};
// Starting the Phaser game with the object config as a param
let game = new Phaser.Game(config);
//Game level lists
let typeList, tileArray, toRemove, toRemoveTemp, toSwap, toAdd;
//Spacing for levels
let offsetX, offsetY, spacing, specialTiles;
//Tiles selected
let tileSelected1, tileSelected2;
//roll player tile over to top
let rollOver, playerPosX;
//moves remaining
let moves, movesLeft, canSelect;
