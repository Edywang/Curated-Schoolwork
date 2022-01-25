class Menu extends Phaser.Scene {
    constructor(){
        super("menuScene");
    }
    preload() {
        //580 x 220 Start Button
        this.load.image('start','./assets/Start.png');
        this.load.image('doggoBig',"assets/doggo.png");
        this.load.bitmapFont('myfont', 'assets/font.png', 'assets/font.fnt');
    }
    
    create(){
        var titleText = this.add.bitmapText(40, 50, 'myfont', 'Animatch', 128); 
        var startText = this.add.bitmapText(180, 250, 'myfont', 'Start', 64).setOrigin(0,0).setInteractive(); 
        startText.on('pointerup', function () {
            this.scene.start("animation1Scene");
        },this);
        this.add.sprite(160,400, 'doggoBig').setOrigin(0,0);
    }
    update() { 
    }
}
