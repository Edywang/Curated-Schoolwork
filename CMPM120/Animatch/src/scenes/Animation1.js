class Animation1 extends Phaser.Scene {
    constructor(){
        super("animation1Scene");
    }
    preload() {
        //320x240 Animation
        this.load.image('frame0','./assets/pickupDog/frame_00_delay-0.1s.gif');
        this.load.image('frame1','./assets/pickupDog/frame_01_delay-0.1s.gif');
        this.load.image('frame2','./assets/pickupDog/frame_02_delay-0.1s.gif');
        this.load.image('frame3','./assets/pickupDog/frame_03_delay-0.1s.gif');
        this.load.image('frame4','./assets/pickupDog/frame_04_delay-0.1s.gif');
        this.load.image('frame5','./assets/pickupDog/frame_05_delay-0.1s.gif');
        this.load.image('frame6','./assets/pickupDog/frame_06_delay-0.1s.gif');
        this.load.image('frame7','./assets/pickupDog/frame_07_delay-0.1s.gif');
        this.load.image('frame8','./assets/pickupDog/frame_08_delay-0.1s.gif');
        this.load.image('frame9','./assets/pickupDog/frame_09_delay-0.1s.gif');
        this.load.image('frame10','./assets/pickupDog/frame_10_delay-0.1s.gif');
        this.load.image('frame11','./assets/pickupDog/frame_11_delay-0.1s.gif');
        this.load.image('frame12','./assets/pickupDog/frame_12_delay-0.1s.gif');
        this.load.image('frame13','./assets/pickupDog/frame_13_delay-0.1s.gif');
        this.load.image('frame14','./assets/pickupDog/frame_14_delay-0.1s.gif');
        this.load.image('frame15','./assets/pickupDog/frame_15_delay-0.1s.gif');
        this.load.image('frame16','./assets/pickupDog/frame_16_delay-0.1s.gif');
        this.load.image('frame17','./assets/pickupDog/frame_17_delay-0.1s.gif');
        this.load.image('frame18','./assets/pickupDog/frame_18_delay-0.1s.gif');
        this.load.image('frame19','./assets/pickupDog/frame_19_delay-0.1s.gif');
        this.load.image('frame20','./assets/pickupDog/frame_20_delay-0.1s.gif');
        this.load.image('frame21','./assets/pickupDog/frame_21_delay-0.1s.gif');
        this.load.image('frame22','./assets/pickupDog/frame_22_delay-0.1s.gif');
        this.load.image('frame23','./assets/pickupDog/frame_23_delay-0.1s.gif');
        this.load.image('frame24','./assets/pickupDog/frame_24_delay-0.1s.gif');
        this.load.image('frame25','./assets/pickupDog/frame_25_delay-0.1s.gif');
        this.load.image('frame26','./assets/pickupDog/frame_26_delay-0.1s.gif');
        this.load.image('frame27','./assets/pickupDog/frame_27_delay-0.1s.gif');
        this.load.image('frame28','./assets/pickupDog/frame_28_delay-0.1s.gif');
        this.load.image('frame29','./assets/pickupDog/frame_29_delay-0.1s.gif');
        this.load.image('frame30','./assets/pickupDog/frame_30_delay-0.1s.gif');
        this.load.image('frame31','./assets/pickupDog/frame_31_delay-0.1s.gif');
        this.load.image('frame32','./assets/pickupDog/frame_32_delay-0.1s.gif');
        this.load.image('frame33','./assets/pickupDog/frame_33_delay-0.1s.gif');
        this.load.image('frame34','./assets/pickupDog/frame_34_delay-0.1s.gif');
        this.load.image('frame35','./assets/pickupDog/frame_35_delay-0.1s.gif');
        this.load.image('frame36','./assets/pickupDog/frame_36_delay-0.1s.gif');

    }
    
    create(){
        this.anims.create({
            key: 'dogPickup',
            frames: [
                { key: 'frame0' },
                { key: 'frame1' },
                { key: 'frame2' },
                { key: 'frame3' },
                { key: 'frame4' },
                { key: 'frame5' },
                { key: 'frame6' },
                { key: 'frame7' },
                { key: 'frame8' },
                { key: 'frame9' },
                { key: 'frame10' },
                { key: 'frame11' },
                { key: 'frame12' },
                { key: 'frame13' },
                { key: 'frame14' },
                { key: 'frame15' },
                { key: 'frame16' },
                { key: 'frame17' },
                { key: 'frame18' },
                { key: 'frame19' },
                { key: 'frame20' },
                { key: 'frame21' },
                { key: 'frame22' },
                { key: 'frame23' },
                { key: 'frame24' },
                { key: 'frame25' },
                { key: 'frame26' },
                { key: 'frame27' },
                { key: 'frame28' },
                { key: 'frame29' },
                { key: 'frame30' },
                { key: 'frame31' },
                { key: 'frame32' },
                { key: 'frame33' },
                { key: 'frame34' },
                { key: 'frame35' },
                { key: 'frame36' },
            ],
            frameRate: 10,
            repeat: 0
        });
        var animation = this.add.sprite(80, 200, 'frame0').play('dogPickup').setOrigin(0,0);
        animation.on('animationcomplete', function (animation, frame){
            this.scene.start("level1"); //should lead to level 2 when that is made
        }, this);
    }
    update() {
        //
    }
}