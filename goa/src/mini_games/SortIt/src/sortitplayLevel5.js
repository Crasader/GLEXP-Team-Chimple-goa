/// <reference path="../../cocos2d-typescript-definitions/cocos2d/cocos2d-lib.d.ts" />

var xc = xc || {};
xc.sortitlevel5Layer = cc.Layer.extend({
    counterLevel5 : 1,
    level5SpriteScaleX : 0.9, 
    level5SpriteScaleY : 0.9,
    ctor:function () {
        
        this._super();

        var self = this;

        var eventListener = cc.eventManager.addListener({
            event: cc.EventListener.TOUCH_ONE_BY_ONE,
            swallowTouches: true,
            
            onTouchBegan: function (touch, event) {
                var target = event.getCurrentTarget();
                var location = target.convertToNodeSpace(touch.getLocation());
                var targetSize = target.getContentSize();
                var targetRectangle = cc.rect(0, 0, targetSize.width, targetSize.height);
               
                if (self.counterLevel5 == 6) {
                    
                
                    cc.director.runScene(new sortitlevel6Scene());
                    
                }
                 
                return true;
            }

        }, this);

        // this.audioEngine = cc.audioEngine;
        // this.audioEngine.playEffect(res.explosive_mp3);

    


        var size = cc.winSize;

         
         this.bg = ccs.load(SortIt.level5bg_json);
         this.bg.setAnchorPoint(0.5, 0.5);
         this.bg.setPosition(size.width / 2, size.height / 2); 
         this.addChild(this.bg);
         cc.eventManager.addListener(eventListener.clone(), this.bg);
        

         this.character = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/charcterfive.png"));
         this.character.setAnchorPoint(0.5, 0.5);
         this.character.setPosition(size.width*0.78 , size.height*0.46);
         this.character.setScale(0.8, 0.8); 
         this.addChild(this.character);






         ///////////////////////////for transparent
       
         this.num1t = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num1t.png"));
         this.num1t.setAnchorPoint(0.5, 0.5 );
         this.num1t.setPosition(size.width*0.39 , size.height*0.24);
         this.num1t.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY); 
         this.addChild(this.num1t);
         

         this.num2t = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num2t.png"));
         this.num2t.setAnchorPoint(0.5, 0.5 );
         this.num2t.setPosition(size.width*0.39 , size.height*0.36);
         this.num2t.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY); 
         this.addChild(this.num2t);
        


         this.num3t = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num3t.png"));
         this.num3t.setAnchorPoint(0.5, 0.5 );
         this.num3t.setPosition(size.width*0.39 , size.height*0.47);
         this.num3t.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY); 
         this.addChild(this.num3t);
         
         

         this.num4t = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num4t.png"));
         this.num4t.setAnchorPoint(0.5, 0.5 );
         this.num4t.setPosition(size.width*0.39 , size.height*0.57);
         this.num4t.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY); 
         this.addChild(this.num4t);
         
      
         this.num5t = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num5t.png"));
         this.num5t.setAnchorPoint(0.5, 0.5 );
         this.num5t.setPosition(size.width*0.39 , size.height*0.68);
         this.num5t.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY); 
         this.addChild(this.num5t);
         


         this.num1 = new MovableItem5(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num1.png"), this.num1t, this);
         this.num1.setAnchorPoint(0.5, 0.5);
         this.num1.setPosition(size.width*0.23 , size.height*0.23);
         this.num1.xP = this.num1.getPosition().x;
         this.num1.yP = this.num1.getPosition().y;
         this.num1.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY);
         this.num1.id = 1;
         this.addChild(this.num1);
         

         this.num2 = new MovableItem5(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num2.png"), this.num2t, this);
         this.num2.setAnchorPoint(0.5, 0.5);
         this.num2.setPosition(size.width*0.54 , size.height*0.23);
         this.num2.xP = this.num2.getPosition().x;
         this.num2.yP = this.num2.getPosition().y;
         this.num2.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY);
         this.num2.id = 2;
         this.addChild(this.num2);
         

         this.num3 = new MovableItem5(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num3.png"), this.num3t, this);
         this.num3.setAnchorPoint(0.5, 0.5);
         this.num3.setPosition(size.width*0.07 , size.height*0.23);
         this.num3.xP = this.num3.getPosition().x;
         this.num3.yP = this.num3.getPosition().y;
         this.num3.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY);
         this.num3.id = 3;
         this.addChild(this.num3);
         

         this.num4 = new MovableItem5(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num4.png"), this.num4t, this);
         this.num4.setAnchorPoint(0.5, 0.5);
         this.num4.setPosition(size.width*0.70 , size.height*0.23);
         this.num4.xP = this.num4.getPosition().x;
         this.num4.yP = this.num4.getPosition().y;
         this.num4.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY);
         this.num4.id = 4;
         this.addChild(this.num4);
         

         this.num5 = new MovableItem5(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/num5.png"), this.num5t, this);
         this.num5.setAnchorPoint(0.5, 0.5);
         this.num5.setPosition(size.width*0.42 , size.height*0.13);
         this.num5.xP = this.num5.getPosition().x;
         this.num5.yP = this.num5.getPosition().y;
         this.num5.setScale(this.level5SpriteScaleX, this.level5SpriteScaleY);
         this.num5.id = 5;
         this.addChild(this.num5);
        


        return true;
    }


});

var sortitlevel5Scene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new xc.sortitlevel5Layer();
        this.addChild(layer);
    }
});


xc.sortitlevel5Layer.res = {
    
}

