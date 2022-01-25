class Credits extends Phaser.Scene {
    constructor(){
        super("creditsScene");
    }

    preload() {
        //580 x 220 Back Button
        this.load.image('back','./assets/Back.png');
    }
    create(){
        let creditsConfig = {
            fontFamily: 'Arial',
            fontSize: '20px',
            backgroundColor: '#000000',
            color: '#FFFFFF',
            align: 'right',
            padding: {
                top: 5,
                bottom: 5,
            },
        }
        this.credits = this.add.text(320, 100, "Code by Eric Shen, Edwin Wang, and Vincent Cheng", creditsConfig);
        this.credits.x = 320 - this.credits.width/2;
        this.credits2 = this.add.text(320, 180, "Art by Eric Shen, Vincent Cheng, and Simanek on Openclipart", creditsConfig);
        this.credits2.x = 320 - this.credits2.width/2;
        this.credits3 = this.add.text(320, 260, "Music by Kent Kercher and SFX by Sergenious on Freesound.org", creditsConfig);
        this.credits3.x = 320 - this.credits2.width/2;
        //Back Button
        var button = this.add.sprite(175,350,`back`).setScale(0.5,0.5).setOrigin(0,0).setInteractive();
        //Mouse Hover Button
        button.on('pointerover',function(){
            console.log('button over');
        });
        //Mouse Leaves Button
        button.on('pointerout',function(){
            console.log('button out');
        });
        //Mouse Clicks Button
        button.on('pointerup',function(){
            console.log('changed scene');
            this.sound.play('blip');
            this.scene.start("menuScene");
        },this);
    }
    update() {
    }
}