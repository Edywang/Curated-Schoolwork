// Portal Prefab
class Portal extends Phaser.GameObjects.Sprite{
    constructor(scene, x, y, texture, frame, speedValue){
        super(scene, x, y, texture, frame);
        // Add this object to existing scene
        scene.add.existing(this);
        this.speed = speedValue;
    }
    update(){
        //Move Left
        this.x -= this.speed;
        //Wraparound
        if(this.x <= 0 - this.width){
            this.x = game.config.width +  2000 + Math.random() * 5000;
            this.y = Math.random() * (game.config.height - this.height*this.scale - 20) + 10;
            //Change speed
            //this.speed = Math.random()*10;
        }
    
    }
}