/* Explanation of points
Team: Eric Shen, Edwin Wang, Vincent Cheng
Title: Infinite Football
Completed: 5/3/2020
Creative tilt: The art (while not great) was mostly drawn ourselves, and for technically interesting, we used a particle emitter for the portal
*/


// Terminal command to start localhost web server: "python -m http.server"
console.log("JS File Loaded Successfully");
let config = {
    // Render type: OpenGL or Canvas; Choosing Canvas for our type of art
    type: Phaser.CANVAS,
    width: 640, // TODO: We might want to change this
    height: 480, // TODO: We might want to change this
    scene: [Menu,Play,Credits,Cutscene,Death],
};
// Starting the Phaser game with the object config as a param
let game = new Phaser.Game(config);

// Reserve some keyboard variables
let keyUP, keyDOWN, keyENTER;

//Score config
let scoreConfig = {
    fontFamily: 'Courier',
    fontSize: '28px',
    backgroundColor: '#F3B141',
    color: '#843605',
    align: 'right',
    padding: {
        top: 5,
        bottom: 5,
    },
    fixedWidth: 100
};
let distance;
let emitter;