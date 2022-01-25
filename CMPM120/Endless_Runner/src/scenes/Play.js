class Play extends Phaser.Scene{
    constructor(){
        super("playScene");
    }

    preload(){
        // Load images/tile sprites
        // Preload an image for this called rocket located at ./assets/rocket.png 
        // Tile Sprite
        // this.load.spritesheet('explosion', './assets/explosion.png', {frameWidth: 64, frameHeight: 32, startFrame: 0, endFrame: 9});
        this.load.image('football', './assets/football.png');
        // this.load.image('goal', './assets/goalposttrans.png');
        this.load.image('portal', './assets/portaltrans.png');
        this.load.image('tree', './assets/tree1trans.png');
        this.load.atlas('bird','./assets/bird.png', './assets/bird.json');
        this.load.image('bird', './assets/birdtrans1.png');
        this.load.image('background', './assets/Background.png');
        this.load.audio('portalnoise','./assets/portal.wav');
        this.load.image('blue',"./assets/Particle.png")
    }

    create(){
        /* Place tile sprite
        // this.starfield = this.add.tileSprite(0, 0, 640, 480, 'starfield').setOrigin(0, 0);

        // Adding rectangle
        this.add.rectangle(5, 5, 630, 32, 0xFFFFFF).setOrigin(0, 0);

        // Green UI background
        this.add.rectangle(37, 42, 566, 64, 0x00FF00).setOrigin(0, 0);

        // Logging this
        console.log(this);

        // Adding prefab syntax
        this.name = new Prefab(this, x, y, 'asset').setScale(0.5, 0.5).setOrigin(0, 0);

        // Define keyboard keys
        keyF = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.F);
        keyLEFT = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.LEFT);

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
            backgroundColor: '#F3B141',t
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

        scoreConfig.fixedWidth = 0;
        */

        // background music
        game.music.play(); 
        // Background
        this.field = this.add.tileSprite(0,0,960,480,'background').setOrigin(0,0);

        // Player
        this.footballPlayer = new Football(this,50,480/2 - 758/40,'football',0).setScale(0.05, 0.05).setOrigin(0, 0);

        // Enemy
        // this.sanicEnemy = new Sanic(this,1150,100,'sanic',0,10).setScale(0.05, 0.05).setOrigin(0, 0);
        this.treeEnemy = new Tree(this, game.config.width + Math.random() * 1000, (Math.random() * (game.config.height-300)) + 150,'tree',0, 10).setScale(0.5, 0.5).setOrigin(0, 0);
        this.birdEnemy = new Bird(this, game.config.width + Math.random() * 1000, (Math.random() * (game.config.height-300)) + 150,'bird',0, 10).setScale(0.5, 0.5).setOrigin(0, 0);
        this.birdEnemy.play('everything');
        //Bonus
        this.portalBonus = new Portal(this, game.config.width + Math.random() * 1000, (Math.random() * (game.config.height-300)) + 150,'portal', 0, 10).setScale(0.5, 0.5).setOrigin(0, 0);
        // this.goalpostBonus = new Goalpost(this,1250,200,'goal',0,10).setScale(0.05, 0.05).setOrigin(0, 0);

        //Particle
        let particles = this.add.particles('blue');
        emitter = particles.createEmitter();
        emitter.setSpeed(200);
        emitter.setBlendMode(Phaser.BlendModes.ADD);
        emitter.setPosition(this.portalBonus.x+40,this.portalBonus.y+70);

        // Keeping score in this variable
        distance = 0;
        this.gameOver = false;
        keyUP = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.UP);
        keyDOWN = this.input.keyboard.addKey(Phaser.Input.Keyboard.KeyCodes.DOWN);
        
        // Displaying the score
        this.scoreLeft = this.add.text(529, 54, 'yds', scoreConfig);
        this.scoreLeft = this.add.text(469, 54, distance, scoreConfig);

        //Speed of 10m/s
        this.delay = 100
        this.time.delayedCall(this.delay, this.distanceIncrease, [], this);
    }

    update(){
        if(this.gameOver){
            game.music.pause();
            this.scene.start("deathScene");
        }
        else{
            // Distance
            // console.log(distance);
            // Scroll Background
            this.field.tilePositionX += 1;
            // Player
            this.footballPlayer.update();
            // Enemy
            // this.sanicEnemy.update();
            this.treeEnemy.update();
            this.birdEnemy.update();
            // Bonus
            this.portalBonus.update();
            emitter.setPosition(this.portalBonus.x+40,this.portalBonus.y+70);
            // this.goalpostBonus.update();
            // Enemy
            // if(this.checkCollision(this.footballPlayer,this.sanicEnemy)){ this.gameOver = true; }
            if(this.checkCollision(this.footballPlayer,this.treeEnemy)){
                this.gameOver = true;
            }
            if(this.checkCollision(this.footballPlayer,this.birdEnemy)){
                this.gameOver = true;
            }
            // Bonus
            if(this.checkCollision(this.footballPlayer,this.portalBonus)){
                console.log("Collision between football and portal detected")
                this.portalBonus.x = -this.portalBonus.width;
                this.sound.play('portalnoise');
                distance += 100;
                this.field.tilePositionX += 100;
                this.birdEnemy.x = -this.birdEnemy.width;
                this.treeEnemy.x = -this.treeEnemy.width;
                this.scoreLeft.text = distance;
            }
            // if(this.checkCollision(this.footballPlayer,this.goalpostBonus)){ }
        }
    }
    
    checkCollision(player,other){

        // console.log(other.x);
        // collision
        if(player.x < other.x + other.width*other.scale && 
            player.x + player.width*player.scale > other.x &&
            player.y < other.y + other.height*other.scale &&
            player.height*player.scale + player.y > other.y){
                return true;
        }
        else{
            return false;
        }
    }

    distanceIncrease(){
        distance++;
        this.scoreLeft.text = distance;
        this.time.delayedCall(this.delay, this.distanceIncrease, [], this);
    }

    /*
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
    } */
}