// Football Prefab
class Football extends Phaser.GameObjects.Sprite{
    constructor(scene, x, y, texture, frame){
        super(scene, x, y, texture, frame);
        // Add this object to existing scene
        scene.add.existing(this);
    }
    
    update(){
        //Moves down
        if(keyUP.isDown && this.y > 0 + 20){
            this.y -= 5;
        }
        //Moves up
        else if(keyDOWN.isDown && this.y < 480 - this.height/20 - 20){
            this.y += 5;
        }
    }
}