class Death extends Phaser.Scene {
    constructor(){
        super("deathScene");
    }

    preload() {
        //580 x 220 Play Again Button
        this.load.image('playagain','./assets/PlayAgain.png');
        //580 x 220 Menu Button
        this.load.image('menu','./assets/Menu.png');
        this.load.audio('blip', './assets/blip.wav');

    }
    create(){
        let titleConfig = {
            fontFamily: 'Courier',
            fontSize: '56px',
            backgroundColor: '#000000',
            color: '#FFFFFF',
            align: 'right',
            padding: {
                top: 5,
                bottom: 5,
            },
        }
        this.title = this.add.text(170, 100, "Game Over", titleConfig);
        titleConfig.fontSize = '28px';
        this.title2 = this.add.text(220, 200, "You Scored " + distance, titleConfig);
        //Play Again Button
        var button = this.add.sprite(175,260,`playagain`).setScale(0.5,0.5).setOrigin(0,0).setInteractive();
        //Mouse Hover Button
        button.on('pointerover',function(){
            // console.log('button over');
        });
        //Mouse Leaves Button
        button.on('pointerout',function(){
            // console.log('button out');
        });
        //Mouse Clicks Button
        button.on('pointerup',function(){
            console.log('changed scene');
            this.sound.play('blip');
            this.scene.start("cutScene");
        },this);

        //Menu Button
        var button = this.add.sprite(175,370,`menu`).setScale(0.5,0.5).setOrigin(0,0).setInteractive();
        //Mouse Hover Button
        button.on('pointerover',function(){
            // console.log('button over');
        });
        //Mouse Leaves Button
        button.on('pointerout',function(){
            // console.log('button out');
        });
        //Mouse Clicks Button
        button.on('pointerup',function(){
            console.log('changed scene');
            this.sound.play('blip');
            this.scene.start("menuScene");
        },this);

        //this.scoreLeft = this.add.text(469, 54, distance, scoreConfig);
    }
    update() {
    }
}