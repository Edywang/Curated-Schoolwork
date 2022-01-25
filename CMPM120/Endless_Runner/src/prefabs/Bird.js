// Bird Prefab
class Bird extends Phaser.GameObjects.Sprite{
    constructor(scene, x, y, texture, frame, speedValue){
        super(scene, x, y, texture, frame);
        // Add this object to existing scene
        scene.add.existing(this);
        this.speed = speedValue;   
        game.anims.create({ key: 'everything', frames: game.anims.generateFrameNames('bird'), repeat: -1 });             
    }
    
    update(){
        //animate
        //game.anims.create({ key: 'everything', frames: game.anims.generateFrameNames('bird'), repeat: -1 });

        //Move Left
        this.x -= this.speed;
        //Wraparound
        if(this.x <= 0 - this.width){
            this.x = game.config.width + Math.random() * 1000;
            this.y = Math.random() * (game.config.height - this.height*this.scale - 20) + 10;
            //Change speed
            //this.speed = Math.random()*10;
        }
    
    }
}