/// <reference path="../../cocos2d-typescript-definitions/cocos2d/cocos2d-lib.d.ts" />

var xc = xc || {};
xc.sortitlevel6Layer = cc.Layer.extend({
        counterLevel6 : 1,
        level6SpriteScaleX : 0.9, 
        level6SpriteScaleY : 0.9,
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
                   
               
                if (self.counterLevel6 == 6) {
                    
                 
                    
                    cc.director.runScene(new sortitlevel1Scene());
                    
                }
                //console.log('touche po oe: ' + targetSize);   
                return true;
            }

        }, this);

        // this.audioEngine = cc.audioEngine;
        // this.audioEngine.playEffect(res.explosive_mp3);

        

        var size = cc.winSize;

         this.bg = ccs.load(SortIt.level6bg_json);
         this.bg.setAnchorPoint(0.5, 0.5 );
         this.bg.setPosition(size.width / 2, size.height / 2); 
         this.addChild(this.bg);
         cc.eventManager.addListener(eventListener.clone(), this.bg);



         ///////////////////////////for transparent
         
         this.at = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/at.png"));
         this.at.setAnchorPoint(0.5, 0.5 );
         this.at.setPosition(size.width*0.43 , size.height*0.69);
         this.at.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY); 
         this.addChild(this.at);
         
         

         this.bt = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/bt.png"));
         this.bt.setAnchorPoint(0.5, 0.5 );
         this.bt.setPosition(size.width*0.52 , size.height*0.72);
         this.bt.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY); 
         this.addChild(this.bt);
        

         this.ct = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/ct.png"));
         this.ct.setAnchorPoint(0.5, 0.5 );
         this.ct.setPosition(size.width*0.61 , size.height*0.69);
         this.ct.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY); 
         this.addChild(this.ct);
         

            
         this.dt = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/dt.png"));
         this.dt.setAnchorPoint(0.5, 0.5 );
         this.dt.setPosition(size.width*0.71 , size.height*0.67);
         this.dt.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY); 
         this.addChild(this.dt);
         
             

         this.et = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/et.png"));
         this.et.setAnchorPoint(0.5, 0.5 );
         this.et.setPosition(size.width*0.78 , size.height*0.71);
         this.et.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY); 
         this.addChild(this.et);
         

         this.a = new MovableItem6(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/a.png"), this.at, this);
         this.a.setAnchorPoint(0.5, 0.5);
         this.a.setPosition(size.width*0.70 , size.height*0.19);
         this.a.xP = this.a.getPosition().x;
         this.a.yP = this.a.getPosition().y;
         this.a.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY);
         this.a.id = 1;
         this.addChild(this.a);
         

         this.b = new MovableItem6(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/b.png"), this.bt, this);
         this.b.setAnchorPoint(0.5, 0.5);
         this.b.setPosition(size.width*0.31 , size.height*0.14);
         this.b.xP = this.b.getPosition().x;
         this.b.yP = this.b.getPosition().y;
         this.b.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY);
         this.b.id = 2;
         this.addChild(this.b);
         

         this.c = new MovableItem6(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/c.png"), this.ct, this);
         this.c.setAnchorPoint(0.5, 0.5);
         this.c.setPosition(size.width*0.46 , size.height*0.10);
         this.c.xP = this.c.getPosition().x;
         this.c.yP = this.c.getPosition().y;
         this.c.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY);
         this.c.id = 3;
         this.addChild(this.c);
         
   
         this.d = new MovableItem6(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/d.png"), this.dt, this);
         this.d.setAnchorPoint(0.5, 0.5);
         this.d.setPosition(size.width*0.62 , size.height*0.10);
         this.d.xP = this.d.getPosition().x;
         this.d.yP = this.d.getPosition().y;
         this.d.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY);
         this.d.id = 4;
         this.addChild(this.d);
        
         

         this.e = new MovableItem6(cc.spriteFrameCache.getSpriteFrame("sortit/sortittwo/e.png"), this.et, this);
         this.e.setAnchorPoint(0.5, 0.5);
         this.e.setPosition(size.width*0.07 , size.height*0.12);
         this.e.xP = this.e.getPosition().x;
         this.e.yP = this.e.getPosition().y;
         this.e.setScale(this.level6SpriteScaleX, this.level6SpriteScaleY);
         this.e.id = 5;
         this.addChild(this.e);
        

        return true;
    }


});

var sortitlevel6Scene = cc.Scene.extend({
    onEnter:function () {
        this._super();
        var layer = new xc.sortitlevel6Layer();
        this.addChild(layer);
    }
});



xc.sortitlevel6Layer.res = {
    
}
