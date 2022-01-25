class Level1 extends Phaser.Scene {
    constructor(){
        super("level1");
    }
    preload() {
        this.load.image('teddybear',"assets/rsz_teddybear.png");
        this.load.image('frisbee',"assets/rsz_frisbee.png");
        this.load.image('tennisball',"assets/rsz_tennisball.png");
        this.load.image('chewtoy',"assets/rsz_chewtoy.png");
        this.load.image('ropetoy',"assets/rsz_ropetoy.png");
        this.load.image('doggo',"assets/rsz_doggo.png");
        this.load.audio('bark', './assets/bark.wav');
        this.load.audio('beep', './assets/beep.wav');
        this.load.image('mom', './assets/momSprite.png');
    }
    create() {
        //Config (self explanatory names)
        toRemove = [];
        toRemoveTemp = []
        toSwap = [];
        toAdd = [];
        tileSelected1 = null;
        tileSelected2 = null;
        offsetX = 60;
        offsetY = 100;
        spacing = 50;
        rollOver = false;
        canSelect = true;
        typeList = ['teddybear','frisbee','tennisball','chewtoy','ropetoy','doggo'];
        specialTiles = 1;
        //tileArray[height][length]
        tileArray = [
            [1,2,3,4,5,6],
            [2,2,3,4,5,6],
            [3,2,3,4,5,6],
            [4,2,3,4,5,6],
            [5,2,3,4,5,6],
            [6,2,3,4,5,6],
            [7,2,3,4,5,6],
            [8,2,3,4,5,6],  
            [9,2,3,4,5,6],
            [10,2,3,4,5,6],
        ];
        //Instructions
        let instructionConfig = {
            fontFamily: 'Courier',
            fontSize: '20px',
            color: '#FFFFFF',
            align: 'Left',
            padding: {
                top: 5,
                bottom: 5,
            },
        }
        this.instructions1 = this.add.text(20, 10, "Click a tile to select it.", instructionConfig);
        this.instructions2 = this.add.text(20, 30, "Click another tile to swap.", instructionConfig);
        this.instructions2 = this.add.text(20, 50, "Help the dog reach his owner.", instructionConfig);

        //place mom
        let momSprite = this.add.sprite(355, 350 , 'mom').setOrigin(0,0).setScale(0.4,0.4);
        //Skip button
        momSprite.setInteractive();
        momSprite.on('clicked',function(){this.scene.start("animation2Scene");},this);

        //Initialize
        //Length
        let playerTileX =  0;//Phaser.Math.Between(0,tileArray[0].length-1);
        let playerTileY =  0;//Phaser.Math.Between(0,4);
        let type;
        for(let i = 0; i < tileArray[0].length; i++){
            //Height
            for(let j = 0; j < tileArray.length; j++){
                //Choose random tile
                if(i == playerTileX && j == playerTileY){
                    type = typeList.length-1;
                }else{
                        type = Phaser.Math.Between(0,typeList.length-1 - specialTiles);
                }
                let tempTile = new Tile(this,spacing*i + offsetX,spacing*j + offsetY,typeList[type],0).setScale(1,1).setOrigin(0, 0);
                //Allow tile to be clickable
                tempTile.setInteractive();
                tempTile.on('clicked',this.selected,this);
                tileArray[j][i] = tempTile;
                //Hide tile
                tempTile.alpha = 0;
            }
        }
        updateDisplay(tileArray.length-1,70);
        //Add clicked action
        this.input.on('gameobjectup', function (pointer, gameObject){
            gameObject.emit('clicked', gameObject);
        }, this);
        
    }
    update() {
        if(tileSelected2 != null){
            //If adjacent swap tiles
            checkAdjacent();
            
        }
        if(tileArray[5][tileArray[0].length-1].texture.key == 'doggo')
        {
            //console.log("success");
            this.scene.start("animation2Scene");
        }   
    }
    //If you select the tile
    selected(tempTile){
        if(canSelect){
            //No previous selected tile
            //console.log((tempTile.y-offsetY)/spacing,(tempTile.x-offsetX)/spacing);
            if(tileSelected1 == null){
                //Store the array values of the tile
                tileSelected1 = [(tempTile.y-offsetY)/spacing,(tempTile.x-offsetX)/spacing];
                //Make the selected tile slightly bigger
                tileArray[tileSelected1[0]][tileSelected1[1]].setScale(1.2,1.2).setOrigin(0.1,0.1);
                game.sound.play('beep');
            }
            //Selected a tile previously
            else{
                //Store the array values of the tile
                tileSelected2 = [(tempTile.y-offsetY)/spacing,(tempTile.x-offsetX)/spacing];
                if(tileSelected2[0] == tileSelected1[0] && tileSelected2[1] == tileSelected1[1]){
                    tileArray[tileSelected1[0]][tileSelected1[1]].setScale(1,1).setOrigin(0,0);
                    tileSelected1 = null;
                    tileSelected2 = null;
                }
            }
        }
    }
}
// --------------------------
//Global Functions
//(Level functions that will be repetitivly used)
//--------------------------
//--------------------------
//--------------------------
// Updates the posisitions and alphas of all tiles
async function updateDisplay(y, delay) {
    for(let row = y;row >= 0;row--){
        await sleep(delay);
        for(let col = 0;col <= tileArray[0].length-1;col++){
            tileArray[row][col].y = spacing*row + offsetY;
            tileArray[row][col].x = spacing*col + offsetX;
            if(tileArray[row][col].alpha == 0){
                //console.log('last');
                tileArray[row][col].alpha = 1;
            }else{
                //console.log("run me");
            }
        }
    }
}
// Check if adjacent tile is different type
function checkAdjacent() {
    canSelect = false;
    // Check if adjacent
    if(Math.abs(tileSelected1[0]-tileSelected2[0])+Math.abs(tileSelected1[1]-tileSelected2[1]) == 1){
        //Stuff
        //Temp the tiles
        let holdTile = tileArray[tileSelected1[0]][tileSelected1[1]];
        let holdTile2 = tileArray[tileSelected2[0]][tileSelected2[1]];
        //Adjust the tiles
        holdTile.y = spacing*tileSelected2[0] + offsetY;
        holdTile.x = spacing*tileSelected2[1] + offsetX;
        holdTile2.y = spacing*tileSelected1[0] + offsetY;
        holdTile2.x = spacing*tileSelected1[1] + offsetX;
        //Array
        tileArray[tileSelected1[0]][tileSelected1[1]] = holdTile2;
        tileArray[tileSelected2[0]][tileSelected2[1]] = holdTile;
        holdTile.setScale(1,1).setOrigin(0,0);
        //console.log(tileSelected2[0],tileSelected2[1]);
        checkInARow(tileSelected2[0],tileSelected2[1]);
        //console.log(tileSelected1[0],tileSelected1[1]);
        checkInARow(tileSelected1[0],tileSelected1[1]);
        if(toRemove.length == 0){
            holdTile2.y = spacing*tileSelected2[0] + offsetY;
            holdTile2.x = spacing*tileSelected2[1] + offsetX;
            holdTile.y = spacing*tileSelected1[0] + offsetY;
            holdTile.x = spacing*tileSelected1[1] + offsetX;
            tileArray[tileSelected1[0]][tileSelected1[1]] = holdTile;
            tileArray[tileSelected2[0]][tileSelected2[1]] = holdTile2;
            //holdTile2.setScale(1.1,1.1).setOrigin(0,0);
        }
        //for(let m=0;m<toRemove.length-1;m++){
        //    console.log(toRemove[m]);
        //}   
        //Reset tiles selected
        removeTile();
        tileSelected1 = null;
        tileSelected2 = null;
        holdTile = null;
        holdTile2 = null;
        
    }else{
        //Else reset 2nd tile
        tileSelected1 = null;
        tileSelected2 = null;
        canSelect=true;
        tileSelected2 = null;
    }
}
//Check if tiles are in a row
function checkInARow(y1,x1){
    //console.log(tileArray[y1][x1].texture.key);
    if((checkDown(y1,x1) + checkUp(y1,x1)) >= 2 && (checkRight(y1,x1) + checkLeft(y1,x1)) >= 2){
        toRemoveTemp.push([y1,x1]);
        //console.log("Length: " + toRemoveTemp.length);
        game.sound.play('bark');
        while(toRemoveTemp.length > 0){
            let temp = toRemoveTemp.pop();
            //console.log("Temp: " + temp);
            toRemove.push(temp);
        }
        //console.log("remove verticle and horizontal");
        return;
    } else {
        toRemoveTemp = [];
    }
    //Check Verticle
    if((checkDown(y1,x1) + checkUp(y1,x1)) >= 2){
        toRemoveTemp.push([y1,x1]);
        //console.log("Length: " + toRemoveTemp.length);
        game.sound.play('bark');
        while(toRemoveTemp.length > 0){
            let temp = toRemoveTemp.pop();
            //console.log("Temp: " + temp);
            toRemove.push(temp);
        }
        //console.log("remove vertical");
        return;
    } else {
        toRemoveTemp = [];
    }
    //Check Horizontal
    if((checkRight(y1,x1) + checkLeft(y1,x1)) >= 2){
        toRemoveTemp.push([y1,x1]);
        //console.log("Length: " + toRemoveTemp.length);
        game.sound.play('bark');
        while(toRemoveTemp.length > 0){
            let temp = toRemoveTemp.pop();
            //console.log("Temp: " + temp);
            toRemove.push(temp);
        }   
        //console.log("remove horizontal");
        return;
    } else {
        toRemoveTemp = [];
    }
}
//Helper function
function checkDown(y1,x1){
    if(y1+1 <= tileArray.length-1 && (tileArray[y1][x1].texture.key == tileArray[y1+1][x1].texture.key)){
        //console.log("Push: " + [y1+1,x1]);
        toRemoveTemp.push([y1+1,x1]);   
        return checkDown(y1+1,x1) + 1;
    }
    return 0;
}
//Helper function
function checkUp(y1,x1){
    if(y1-1 >= 0 && (tileArray[y1][x1].texture.key == tileArray[y1-1][x1].texture.key)){
        //console.log("Push: " + [y1-1,x1]);
        toRemoveTemp.push([y1-1,x1]);
        return checkUp(y1-1,x1) + 1;
    }
    return 0;
}
//Helper function
function checkRight(y1,x1){
    if(x1+1 <= tileArray[y1].length-1&& (tileArray[y1][x1].texture.key == tileArray[y1][x1+1].texture.key)){
        //console.log("Push: " + [y1,x1+1]);
        toRemoveTemp.push([y1,x1+1]);
        return checkRight(y1,x1+1) + 1;
    }
    return 0;
}
//Helper function
function checkLeft(y1,x1){
    if(x1-1 >= 0 && (tileArray[y1][x1].texture.key == tileArray[y1][x1-1].texture.key)){
        //console.log("Push: " + [y1,x1-1]);
        toRemoveTemp.push([y1,x1-1]);
        return checkLeft(y1,x1-1) + 1;
    }
    return 0;
}
//Helper function
async function removeTile(){
    let tempRemove;
    while(toRemove.length>0){
        tempRemove = toRemove.pop()
        tileArray[tempRemove[0]][tempRemove[1]].alpha = 0;
    }
    await reorganize();
    //console.log("running check player");
    if(checkPlayer()){
        reorganize()
    }
    canSelect = true;
}
//Reorganizes tiles so they fall down
async function reorganize(){
    let swapRow = -1;
    //Length
    for(let length = tileArray[0].length-1; length >= 0; length--){
        //Height
        for(let height = tileArray.length-1; height >= 0; height--){
            //If invisible
            if(tileArray[height][length].alpha == 0){
                if(height > swapRow){
                    swapRow = height;
                }
                for(let heightInvisible = height; heightInvisible >= 0; heightInvisible--){
                    //Find nearest visible block
                    if(tileArray[heightInvisible][length].alpha != 0){
                        //Drop all blocks
                        for(let visible=heightInvisible;visible>=0;visible--){
                            toSwap.push([visible,visible+(height-heightInvisible),length]);
                        }      
                        break;
                    }else{
                        let type = Phaser.Math.Between(0,typeList.length - 1 - specialTiles);
                        if (tileArray[heightInvisible][length].texture.key!='doggo'){
                            tileArray[heightInvisible][length].setTexture(typeList[type]);
                            //console.log("changed type");
                        }
                    }
                }
                break; 
            }
        }
    }
    //console.log("Done reorganize, about to start reorganize2")
    //await sleep(delay);
    while(toSwap.length > 0){
        let swapTemp = toSwap.shift();
        let holdTile = tileArray[swapTemp[0]][swapTemp[2]];
        let holdTile2 = tileArray[swapTemp[1]][swapTemp[2]];
        //Changes position in array
        tileArray[swapTemp[1]][swapTemp[2]] = holdTile;
        tileArray[swapTemp[0]][swapTemp[2]] = holdTile2;
    }
    //console.log("Done reorganize2, about to start updateDisplay")
    //console.log("Reorganizing from " + swapRow);
    await updateDisplay(swapRow,70);
    //console.log("Done updateDisplay")
}
// Checks if player has reached the bottom
function checkPlayer(){
    for(let i = 0; i< tileArray[0].length; i++){         
        if(tileArray[tileArray.length-1][i].texture.key == 'doggo') {
            tileArray[tileArray.length-1][i].alpha = 0;
            //console.log("bottom reached");
            return true;
        } 
     }
     return false;
}
function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
