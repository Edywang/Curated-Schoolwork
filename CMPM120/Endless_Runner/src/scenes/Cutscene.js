class Cutscene extends Phaser.Scene {
    constructor(){
        super("cutScene");
    }

    preload() {
        // 1280x758 Football sprite (Transparent background)
        this.load.image('football', './assets/footballfullres.png');
        
    }
    create(){
        //Animation Required
        //Starts the next scene
        this.scene.start("playScene");
    }
    update() {
    }
}