// Rocket Prefab
class Rocket extends Phaser.GameObjects.Sprite{
    constructor(scene, x, y, texture, frame){
        super(scene, x, y, texture, frame);
        // Add this object to existing scene
        scene.add.existing(this); // Add to existing, displayList, updateList
        this.isFiring = false;    // Track rocket's firing status
        this.sfxRocket = scene.sound.add('sfx_rocket'); // Add rocket SFX
    }
    
    update(){
        // Left/Right Movement
        if(!this.isFiring){
            if(keyLEFT.isDown && this.x >= 47){
                this.x -= 2;
            }
            else if(keyRIGHT.isDown && this.x <= 320){
                this.x += 2;
            }
        }

        // Fire button
        if(Phaser.Input.Keyboard.JustDown(keyF) && !this.isFiring){
            this.isFiring = true;
            this.sfxRocket.play();
        }

        // If firing, move up
        if(this.isFiring && this.y >= 108){
            this.y -= 2;
        }

        // Reset on miss
        if(this.y <= 108) {
            this.reset();
        }
    }

    reset(){
        this.isFiring = false;
        this.y = 431;
    }
}