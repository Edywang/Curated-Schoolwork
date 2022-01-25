// Spaceship Prefab
class Spaceship extends Phaser.GameObjects.Sprite{
    constructor(scene, x, y, texture, frame, pointValue){
        super(scene, x, y, texture, frame);
        // Add this object to existing scene
        scene.add.existing(this); // Add to existing, displayList, updateList
        this.points = pointValue;
    }

    update(){
        // Move spaceship left
        this.x -= game.settings.spaceshipSpeed;
        // Wraparound screen bounds
        if(this.x <= 0 - this.width){
            this.x = game.config.width;
        }
    }

    reset(){
        this.x = game.config.width;
    }
}