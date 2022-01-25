// Phaser Scene Steps:
// 1. init() - Prepare data for scene (Specifically for little bits of data like variables passed between scenes)
// 2. preload() - Prepare assets for scene (Specifically for assets)
// 3. create() - Add assets to scene
// 4. update() - Loops continuously for duration of scene at chosen frame rate

class Menu extends Phaser.Scene {
    constructor(){
        super("menuScene");
    }

    preload() {
        // Load audio
        this.load.audio('sfx_select', './assets/blip_select12.wav');
        this.load.audio('sfx_explosion', './assets/explosion38.wav');
        this.load.audio('sfx_rocket', './assets/rocket_shot.wav');
        this.load.audio('bg_music', './assets/ArcadeEscapade.mp3');
    }

    create(){
        // Displaying the menu
        let menuConfig = {
            fontFamily: 'Courier',
            fontSize: '28px',
            backgroundColor: '#F3B141',
            color: '#843605',
            align: 'right',
            padding: {
                top: 5,
                bottom: 5,
            },
            fixedWidth: 0
        }
        // Show menu text
        let centerX = game.config.width/2;
        let centerY = game.config.height/2;
        let textSpacer = 64;

        this.add.text(centerX, centerY-textSpacer, 'ROCKET PATROL', menuConfig).setOrigin(0.5);
        this.add.text(centerX, centerY, '1 Use ⟷ to move & F to fire', menuConfig).setOrigin(0.5);
        this.add.text(centerX, centerY + textSpacer, '2 Use numpad 4 & 6 to move & + to fire', menuConfig).setOrigin(0.5);
        this.add.text(centerX, centerY + (textSpacer * 2), '0.1 extra seconds for each hit', menuConfig).setOrigin(0.5);
        menuConfig.backgroundColor = '#00FF00';
        menuConfig.color = '#000';
        this.add.text(centerX, centerY + (textSpacer * 3), 'Press ← for Easy or → for Hard', menuConfig).setOrigin(0.5);
        console.log(this);

        
        // Define keyboard keys
        keyLEFT = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
        keyRIGHT = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);

        // Change scenes
        // this.scene.start("playScene");
        
        game.music = this.sound.add('bg_music');
        game.music.setLoop(true);
    }

    update() {
        if(Phaser.Input.Keyboard.JustDown(keyLEFT)){
            // Easy mode
            game.settings = {
                spaceshipSpeed: 3,
                gameTimer: 60
            }
            this.sound.play('sfx_select');
            this.scene.start('playScene');
        }
        else if(Phaser.Input.Keyboard.JustDown(keyRIGHT)){
            // Hard mode
            game.settings = {
                spaceshipSpeed: 4,
                gameTimer: 15
            }
            this.sound.play('sfx_select');
            this.scene.start('playScene');
        }
    }
}