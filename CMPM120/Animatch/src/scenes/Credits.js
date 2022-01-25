class Credits extends Phaser.Scene {
    constructor(){
        super("creditScene");
    }
    preload() {
        //580 x 220 Start Button
        this.load.image('start','./assets/Start.png');
    }
    
    create(){
        let creditsConfig = {
            fontFamily: 'Courier',
            fontSize: '40px',
            color: '#FFFFFF',
            align: 'Left',
            padding: {
                top: 5,
                bottom: 5,
            },
        }
        this.instructions1 = this.add.text(50, 120, "Animations:\nEdwin Wang", creditsConfig);
        this.instructions2 = this.add.text(50, 260, "Tile Sprites:\nVincent Cheng", creditsConfig);
        this.instructions2 = this.add.text(50, 400, "Programmer:\nEric Shen", creditsConfig);
    }

    update() { 
        //
    }   
}