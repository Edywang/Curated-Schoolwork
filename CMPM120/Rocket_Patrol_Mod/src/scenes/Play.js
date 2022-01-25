class Play extends Phaser.Scene{
    constructor(){
        super("playScene");
    }

    preload(){
        // Load images/tile sprites
        // Preload an image for this called rocket located at ./assets/rocket.png 
        this.load.spritesheet('explosion', './assets/explosion.png', {frameWidth: 64, frameHeight: 32, startFrame: 0, endFrame: 9});
        this.load.image('rocket', './assets/rocket.png');
        this.load.image('spaceship', './assets/spaceship.png');
        this.load.image('starfield', './assets/starfield.png');
    }

    create(){
        // Place tile sprite
        this.starfield = this.add.tileSprite(0, 0, 640, 480, 'starfield').setOrigin(0, 0);

        // White rectangle borders
        this.add.rectangle(5, 5, 630, 32, 0xFFFFFF).setOrigin(0, 0);
        this.add.rectangle(5, 443, 630, 32, 0xFFFFFF).setOrigin(0, 0);
        this.add.rectangle(5, 5, 32, 455, 0xFFFFFF).setOrigin(0, 0);
        this.add.rectangle(603, 5, 32, 455, 0xFFFFFF).setOrigin(0, 0);

        // Green UI background
        this.add.rectangle(37, 42, 566, 64, 0x00FF00).setOrigin(0, 0);

        // Logging this
        console.log(this);

        // Add rocket (player 1)
        this.p1Rocket = new Rocket(this, game.config.width/3, 431, 'rocket').setScale(0.5, 0.5).setOrigin(0, 0);
        this.p2Rocket = new Rocket2(this, game.config.width*2/3, 431, 'rocket').setScale(0.5, 0.5).setOrigin(0, 0);

        // Add spaceship (x3)
        // Adding the top ship (Ship 01)
        this.ship01 = new Spaceship(this, game.config.width + 192, 132, 'spaceship', 0, 30).setOrigin(0, 0);
        this.ship02 = new Spaceship(this, game.config.width + 96, 196, 'spaceship', 0, 30).setOrigin(0, 0);
        this.ship03 = new Spaceship(this, game.config.width, 260, 'spaceship', 0, 30).setOrigin(0, 0);

        // Define keyboard keys
        keyF = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.F);
        keyLEFT = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);
        keyRIGHT = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.RIGHT);
        key4 = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.NUMPAD_FOUR);
        key6 = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.NUMPAD_SIX);
        keyADD = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.NUMPAD_ADD);

        // Animation config
        this.anims.create({
            key: 'explode',
            frames: this.anims.generateFrameNumbers('explosion', {start: 0, end: 9, first: 0}),
            frameRate: 30
        });

        // Keeping score in this variable (Cooperative score so the var name is misleading)
        this.p1Score = 0;

        // Displaying the score
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
        }
        this.scoreLeft = this.add.text(69, 54, this.p1Score, scoreConfig);

        game.settings.currentTimer = game.settings.gameTimer;
        game.settings.timeLeft = this.add.text(320, 54, game.settings.currentTimer, scoreConfig);

        this.gameOver = false;

        scoreConfig.fixedWidth = 0;
        
        // Update play clock
        this.timer = this.time.addEvent({
            delay: 100,                // ms
            callback: this.reduceTime,
            loop: true
        });

        this.gameOverText = this.add.text(game.config.width/2, game.config.height/2, 'GAME OVER', scoreConfig).setOrigin(0.5);
        this.restartText = this.add.text(game.config.width/2, game.config.height/2 + 64, '(F)ire to Restart or ← for Menu', scoreConfig).setOrigin(0.5);
        this.creditText = this.add.text(game.config.width/2, game.config.height/2 + 128, 'Background music by Kent Kercher', scoreConfig).setOrigin(0.5);
        this.creditLink = this.add.text(game.config.width/2, game.config.height/2 + 192, 'https://www.kentkercher.com/', scoreConfig).setOrigin(0.5);
        this.gameOverText.setVisible(false);
        this.restartText.setVisible(false);
        this.creditText.setVisible(false);
        this.creditLink.setVisible(false);

        game.music.play();
    }

    update(){
        // Check key input for restart
        if(this.gameOver && Phaser.Input.Keyboard.JustDown(keyF)){
            this.restartGame();
        }
        if(this.gameOver && Phaser.Input.Keyboard.JustDown(keyLEFT)){
            this.scene.start("menuScene");
        }

        // Scroll starfield
        this.starfield.tilePositionX -= 4;
        // this.starfield.tilePositionY -= 4;

        // If the game isn't over, keep updating
        if(!this.gameOver){
            // Update rockets
            this.p1Rocket.update();
            this.p2Rocket.update();
            // Update spaceship
            this.ship01.update();
            this.ship02.update();
            this.ship03.update();
        }

        // Collision checking between p1Rocket and Ships
        if(this.checkCollision(this.p1Rocket, this.ship03)) {
            this.p1Rocket.reset();
            this.shipExplode(this.ship03);
            game.settings.currentTimer += 0.1;
          }
          if (this.checkCollision(this.p1Rocket, this.ship02)) {
            this.p1Rocket.reset();
            this.shipExplode(this.ship02);
            game.settings.currentTimer += 0.1;
          }
          if (this.checkCollision(this.p1Rocket, this.ship01)) {
            this.p1Rocket.reset();
            this.shipExplode(this.ship01);
            game.settings.currentTimer += 0.1;
          }

          // Collision checking between p2Rocket and Ships
        if(this.checkCollision(this.p2Rocket, this.ship03)) {
            this.p2Rocket.reset();
            this.shipExplode(this.ship03);
            game.settings.currentTimer += 0.1;
          }
          if (this.checkCollision(this.p2Rocket, this.ship02)) {
            this.p2Rocket.reset();
            this.shipExplode(this.ship02);
            game.settings.currentTimer += 0.1;
          }
          if (this.checkCollision(this.p2Rocket, this.ship01)) {
            this.p2Rocket.reset();
            this.shipExplode(this.ship01);
            game.settings.currentTimer += 0.1;
          }
        
        if(game.settings.currentTimer <= 0){
            this.endGame();
        }
    }

    checkCollision(rocket, ship) {
        // simple AABB checking
        if (rocket.x < ship.x + ship.width && 
            rocket.x + rocket.width > ship.x && 
            rocket.y < ship.y + ship.height &&
            rocket.height + rocket.y > ship.y) {
                return true;
        } else {
            return false;
        }
    }

    shipExplode(ship) {
        ship.alpha = 0; // Temporarily hiding the ship
        // Create the explosion sprite at the ship's position
        let boom = this.add.sprite(ship.x, ship.y, 'explosion').setOrigin(0, 0);
        boom.anims.play('explode');
        boom.on('animationcomplete', () => {
            ship.reset();
            ship.alpha = 1;
            boom.destroy();
        });
        // Score increment and repaint
        this.p1Score += ship.points;
        this.scoreLeft.text = this.p1Score;
        this.sound.play('sfx_explosion');
    }

    endGame() {
        this.gameOverText.setVisible(true);
        this.restartText.setVisible(true);
        this.creditText.setVisible(true);
        this.creditLink.setVisible(true);
        this.gameOver = true;
        this.timer.paused = true;
        game.music.pause();
        game.settings.timeLeft.text = 0
    }

    restartGame() {
        this.p1Rocket.x = game.config.width/3;
        this.p2Rocket.x = game.config.width*2/3;
        this.p1Rocket.reset();
        this.p2Rocket.reset();
        this.gameOverText.setVisible(false);
        this.restartText.setVisible(false);
        this.creditText.setVisible(false);
        this.creditLink.setVisible(false);
        game.music.resume();
        this.gameOver = false;
        this.timer.paused = false;
        game.settings.currentTimer = game.settings.gameTimer;
        game.settings.timeLeft.text = game.settings.currentTimer;
        this.p1Score = 0;
        this.scoreLeft.text = this.p1Score;
        this.ship01.x = game.config.width + 192;
        this.ship02.x = game.config.width + 96;
        this.ship03.x = game.config.width;
    }

    reduceTime() {
        game.settings.currentTimer -= 0.1;
        game.settings.timeLeft.text = game.settings.currentTimer;
    }
}