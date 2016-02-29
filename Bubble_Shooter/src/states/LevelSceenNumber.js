
class LevelSceenNumber extends Phaser.State {

    preload(){
        
         this.game.load.image('BackgroundHome', 'assets/Background_Scene.png');
         this.game.load.image('lvl1', 'assets/lvl1.png');
         this.game.load.image('lvl2', 'assets/lvl2.png');
         this.game.load.image('lvl3', 'assets/lvl3.png');
         this.game.load.image('lvl4', 'assets/lvl4.png');
         this.game.load.image('lvl5', 'assets/lvl5.png');
         this.game.load.image('lvl6', 'assets/lvl6.png');
         this.game.load.image('lvl7', 'assets/lvl7.png');
         this.game.load.image('lvl8', 'assets/lvl8.png');
         
         this.game.load.image('Star0', 'assets/Star0.png');
         this.game.load.image('Star1', 'assets/Star1.png');
         this.game.load.image('Star2', 'assets/Star2.png');
         this.game.load.image('Star3', 'assets/Star3.png');
         
         this.game.load.image('OrangeLock', 'assets/Orange_LevelBall.png');
         this.game.load.image('RedLock', 'assets/Red_LevelBall.png');
         
    }


    create(){
        
         this.bg = this.game.add.image(0,0,'BackgroundHome');
       
       // ----- ODD BUBBLE RENDERING ----
         
         let dataDimension = this.getValueXY(10,18);
         this.self = this;
         this.LevelBox1button = this.game.add.button(dataDimension.X, dataDimension.Y, 'OrangeLock', this.LevelMethod1, this);
         this.Level1button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl1');
         this.Level1button.anchor.setTo(0.5);
         this.LevelBox1button.anchor.setTo(0.5);   
         
         dataDimension = this.getValueXY(10,31);
         this.LevelBox3button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod3, this);
         this.Level3button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl3');
         this.Level3button.anchor.setTo(0.5);
         this.LevelBox3button.anchor.setTo(0.5); 
         
         dataDimension = this.getValueXY(10,44);
         this.LevelBox5button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod5, this);
         this.Level5button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl5');
         this.Level5button.anchor.setTo(0.5);
         this.LevelBox5button.anchor.setTo(0.5); 
         
         dataDimension = this.getValueXY(10,57);
         this.LevelBox7button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod7, this);
         this.Level7button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl7');
         this.Level7button.anchor.setTo(0.5);
         this.LevelBox7button.anchor.setTo(0.5); 
         
         
         // ----- STARS RENDERING ----
         
         dataDimension = this.getValueXY(34,18);
         if(localStorage.getItem('NumberStarLevel1') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel1');
             this.Level1Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level1Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star1');  
         }        
         this.Level1Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(34,31);
         if(localStorage.getItem('NumberStarLevel3') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel3');
             this.Level3Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level3Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level3Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(34,44);
         if(localStorage.getItem('NumberStarLevel5') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel5');
             this.Level5Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level5Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level5Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(34,57);
         if(localStorage.getItem('NumberStarLevel7') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel7');
             this.Level7Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level7Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level7Star.anchor.setTo(0.5);
         
         
         
         dataDimension = this.getValueXY(84,18);
         if(localStorage.getItem('NumberStarLevel2') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel2');
             this.Level2Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level2Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level2Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(84,31);
         if(localStorage.getItem('NumberStarLevel4') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel4');
             this.Level4Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level4Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level4Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(84,44);
         if(localStorage.getItem('NumberStarLevel6') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel6');
             this.Level6Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level6Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level6Star.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(84,57);
         if(localStorage.getItem('NumberStarLevel8') > 0){
             let star = "Star"+localStorage.getItem('NumberStarLevel8');
             this.Level8Star = this.game.add.image(dataDimension.X,dataDimension.Y,star);             
         }else{
            this.Level8Star = this.game.add.image(dataDimension.X,dataDimension.Y,'Star0');  
         }        
         this.Level8Star.anchor.setTo(0.5);
         
         
        // ------ EVEN LEVEL BUBBLE RENDERING -----
        
         dataDimension = this.getValueXY(60,18);
         this.LevelBox2button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod2, this);
         this.Level2button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl2');
         this.Level2button.anchor.setTo(0.5);
         this.LevelBox2button.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(60,31);
         this.LevelBox2button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod4, this);
         this.Level2button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl4');
         this.Level2button.anchor.setTo(0.5);
         this.LevelBox2button.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(60,44);
         this.LevelBox2button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod6, this);
         this.Level2button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl6');
         this.Level2button.anchor.setTo(0.5);
         this.LevelBox2button.anchor.setTo(0.5);
         
         dataDimension = this.getValueXY(60,57);
         this.LevelBox2button = this.game.add.button(dataDimension.X, dataDimension.Y, 'RedLock', this.LevelMethod8, this);
         this.Level2button = this.game.add.sprite(dataDimension.X, dataDimension.Y, 'lvl8');
         this.Level2button.anchor.setTo(0.5);
         this.LevelBox2button.anchor.setTo(0.5);
        
    }
    
    getValueXY(widthPer , heightPer){
        
        let X=0 , Y=0;
        
        if(!(widthPer == 0 || heightPer == 0)){
            
        let widthRatio = 100 / widthPer;
        let heightRation = 100 / heightPer;
        
         X = ( this.bg.width / widthRatio ) ;
         Y = ( this.bg.height / heightRation ) ;
        
        }else{
            console.log(" please try again - Enter correct Value  ");
        }
        
        return {X,Y};
    }
    
    
    LevelMethod1(){
     console.log("enter levelOne button 1");
     
     this.game._LevelFlag = 1;
     this.state.start('Number');
     
    }LevelMethod2(){

     this.game._LevelFlag = 2;
     this.state.start('Number');

    }LevelMethod3(){
     console.log("enter levelOne button 3");
     this.game._LevelFlag = 3;
     this.state.start('Number');

    }LevelMethod4(){
     console.log("enter levelOne button 4");
     this.game._LevelFlag = 4;
     this.state.start('Number');

    }LevelMethod5(){
     console.log("enter levelOne button 5");
     this.game._LevelFlag = 5;
     this.state.start('Number');

    }LevelMethod6(){
     console.log("enter levelOne button 6");
     this.game._LevelFlag = 6;
     this.state.start('Number');

    }LevelMethod7(){
     console.log("enter levelOne button 7");
     this.game._LevelFlag = 7;
     this.state.start('Number');

    }LevelMethod8(){
     console.log("enter levelOne button 8");
     this.game._LevelFlag = 8;
     this.state.start('Number');

    }
}

export default LevelSceenNumber;