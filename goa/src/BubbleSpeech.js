var xc = xc || {};
xc.BubbleSpeech = cc.Layer.extend({
    ctor: function (jsonNode, width, height, position, existingText, callback, audiocallback, callbackContext) {
        this._super(width, height);
        this.callback = callback;
        this.audiocallback = audiocallback;
        this._callbackContext = callbackContext;
        this._text = existingText;
        this._nodeJSON = jsonNode;

        this._constructedScene = ccs.load(this._nodeJSON,xc.path);
        this._constructedScene.node.retain();
        
        if (this._constructedScene.node) {
            this.addChild(this._constructedScene.node,0);
        }                        

        this._constructedScene.node.setPosition(cc.director.getWinSize().width/2, cc.director.getWinSize().height/2);
        this._constructedScene.node.setAnchorPoint(cc.p(0.5,0.5));


        var closeButton = this._constructedScene.node.getChildByName("Button_1");
        closeButton.setTitleText("");
        closeButton.addTouchEventListener(this.close, this);

        var soundButton = this._constructedScene.node.getChildByName("sound");
        soundButton.setTitleText("");
        var autoSoundEnabled = cc.sys.localStorage.getItem("autoSoundEnabled");
        if(autoSoundEnabled == "true") {
            soundButton.setHighlighted(true);
            this.audiocallback.call(this._callbackContext, true);
        } else {
            soundButton.setHighlighted(false);
        }
        soundButton.addTouchEventListener(this.toggleButton, this);
        
        this._textField = this._constructedScene.node.getChildByName("TextField_2");
        this._textField.setFontName(xc.storyFontName)
        this._textField.setTextColor(xc.storyFontColor);
        this._textField.setFontSize(xc.storyFontSize);
        this._textField.setAnchorPoint(0.5, 0.5);
        this._textField.setPlaceHolder("");
        this._textField.ignoreContentAdaptWithSize(false);
        this._textField.setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT);
        this._textField.setTextVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
        if (this._text) {
            this._textField.setString(this._text);
        }
        this._textField.setTouchEnabled(false);
    },

    configAutoSound: function() {
        var autoSoundEnabled = cc.sys.localStorage.getItem("autoSoundEnabled");
        if(autoSoundEnabled == "true") {            
            autoSoundEnabled = "false";
        } else {
            autoSoundEnabled = "true";
        }
        cc.sys.localStorage.setItem("autoSoundEnabled", autoSoundEnabled);
    },

    toggleButton: function(sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_ENDED:  
                //replace Button
                var soundButton = this._constructedScene.node.getChildByName("sound");
                soundButton.setVisible(false);

                if(this._item) {
                    this._item.removeFromParent();

                }
                //toggle value
                this.configAutoSound();

                var autoEnabled = cc.sys.localStorage.getItem("autoSoundEnabled") == "true"? true : false;
                if(autoEnabled) {
                    this._item = new ccui.Button('template/click_sound_button.png', 'template/sound_button.png', null, ccui.Widget.PLIST_TEXTURE);
                    this._item.setPosition(soundButton.getPosition());
                    this._item.addTouchEventListener(this.toggleButton, this);
                    this.audiocallback.call(this._callbackContext, true);                                    
                } else {
                    this._item = new ccui.Button('template/sound_button.png', 'template/sound_button.png', null, ccui.Widget.PLIST_TEXTURE);
                    this._item.setPosition(soundButton.getPosition());
                    this._item.addTouchEventListener(this.toggleButton, this);
                    this.audiocallback.call(this._callbackContext, false);
                }
                
                this._constructedScene.node.addChild(this._item);
                    
                break;
        }        
    },


    close: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_ENDED:
                var contents = this._text;
                this._textField.cleanup();
                this.parent.removeChild(this, true);
                if (this.callback != null && this._callbackContext != null) {
                    this.callback.call(this._callbackContext, contents);
                }
                break;
        }
    },
});
