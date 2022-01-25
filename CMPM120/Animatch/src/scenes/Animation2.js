class Animation2 extends Phaser.Scene {
    constructor(){
        super("animation2Scene");
    }
    preload() {      
        //750x750 Animation
        this.load.image('playFrame0','./assets/playDog/frame_00_delay-0.08s.gif');
        this.load.image('playFrame1','./assets/playDog/frame_01_delay-0.08s.gif');
        this.load.image('playFrame2','./assets/playDog/frame_02_delay-0.08s.gif');
        this.load.image('playFrame3','./assets/playDog/frame_03_delay-0.08s.gif');
        this.load.image('playFrame4','./assets/playDog/frame_04_delay-0.08s.gif');
        this.load.image('playFrame5','./assets/playDog/frame_05_delay-0.08s.gif');
        this.load.image('playFrame6','./assets/playDog/frame_06_delay-0.08s.gif');
        this.load.image('playFrame7','./assets/playDog/frame_07_delay-0.08s.gif');
        this.load.image('playFrame8','./assets/playDog/frame_08_delay-0.08s.gif');
        this.load.image('playFrame9','./assets/playDog/frame_09_delay-0.08s.gif');
        this.load.image('playFrame10','./assets/playDog/frame_10_delay-0.08s.gif');
        this.load.image('playFrame11','./assets/playDog/frame_11_delay-0.08s.gif');
        this.load.image('playFrame12','./assets/playDog/frame_12_delay-0.08s.gif');
        this.load.image('playFrame13','./assets/playDog/frame_13_delay-0.08s.gif');
        this.load.image('playFrame14','./assets/playDog/frame_14_delay-0.08s.gif');
        this.load.image('playFrame15','./assets/playDog/frame_15_delay-0.08s.gif');
        this.load.image('playFrame16','./assets/playDog/frame_16_delay-0.08s.gif');
        this.load.image('playFrame17','./assets/playDog/frame_17_delay-0.08s.gif');
        this.load.image('playFrame18','./assets/playDog/frame_18_delay-0.08s.gif');
        this.load.image('playFrame19','./assets/playDog/frame_19_delay-0.08s.gif');
        this.load.image('playFrame20','./assets/playDog/frame_20_delay-0.08s.gif');
        this.load.image('playFrame21','./assets/playDog/frame_21_delay-0.08s.gif');
        this.load.image('playFrame22','./assets/playDog/frame_22_delay-0.08s.gif');
        this.load.image('playFrame23','./assets/playDog/frame_23_delay-0.08s.gif');
    }
    
    create(){
        this.anims.create({
            key: 'dogPlay',
            frames: [
                { key: 'playFrame0' },
                { key: 'playFrame1' },
                { key: 'playFrame2' },
                { key: 'playFrame3' },
                { key: 'playFrame4' },
                { key: 'playFrame5' },
                { key: 'playFrame6' },
                { key: 'playFrame7' },
                { key: 'playFrame8' },
                { key: 'playFrame9' },
                { key: 'playFrame10' },
                { key: 'playFrame11' },
                { key: 'playFrame12' },
                { key: 'playFrame13' },
                { key: 'playFrame14' },
                { key: 'playFrame15' },
                { key: 'playFrame16' },
                { key: 'playFrame17' },
                { key: 'playFrame18' },
                { key: 'playFrame19' },
                { key: 'playFrame20' },
                { key: 'playFrame21' },
                { key: 'playFrame22' },
                { key: 'playFrame23' },
            ],
            frameRate: 10,
            repeat: 0
        });
        var animation = this.add.sprite(52, 132, 'playFrame0').play('dogPlay').setOrigin(0,0).setScale(0.5,0.5);
        animation.on('animationcomplete', function (animation, frame){
            this.scene.start("creditScene"); //Goes to credits
        }, this);
    }
    update() {
        //
    }
}