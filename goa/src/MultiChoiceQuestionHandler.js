/// <reference path="cocos2d-typescript-definitions-master/cocos2d/cocos2d-lib.d.ts" />
var xc = xc || {};
xc.MultipleChoiceQuestionHandler = cc.Layer.extend({
    _textContentMargin: 100,
    _width:0,
    _height: 0,
    _nodeJSON: "",
    _textContentMargin: 0,
    _constructedScene: null,    
    _answers:[],
    _numberOfTimesInCorrectAnswered: 0,
    ctor: function (nodeJSON, width, height, question, callback, callbackContext) {
        this._super(width, height);
        this._width = width;
        this._height = height;
        this.callback = callback;
        this._callbackContext = callbackContext;
        this._question = question;
        this._nodeJSON = nodeJSON;
        this._textContentMargin = 100;
        this.init();
    },

    init: function() {
        this.showQuestionTemplate();
        this.configureQuestion();
        this.configureAnswers();
    },

    showQuestionTemplate: function() {
        this._constructedScene = ccs.load(this._nodeJSON,xc.path);
        this._constructedScene.node.retain();
        
        if (this._constructedScene.node) {
            this._callbackContext.addChild(this._constructedScene.node,0);
        }                        
    },

    configureQuestion: function() {
        //randomize array
        //find out question node

        var node = this._constructedScene.node.getChildByName("Q1");
        if(node) {
            node.setAnchorPoint(cc.p(0.5,0.5));
            node.setFontSize(xc.storyFontSize);
            node.setTextColor(xc.storyFontColor);
            node.setFontName(xc.storyFontName);
            node.setTextHorizontalAlignment(cc.TEXT_ALIGNMENT_LEFT);
            node.setTextVerticalAlignment(cc.VERTICAL_TEXT_ALIGNMENT_CENTER);
            node.setTouchEnabled(false);
            node.setString(this._question.question);
        }
    },    

    configureAnswers: function() {
        var context = this;
        this._answers = this._answers.concat(this._question.choices);
        this._answers = this._answers.concat([this._question.answer]);
        this._answers = this._answers.map(function(n){ return [Math.random(), n] })
             .sort().map(function(n){ return n[1] });

        this._answers.forEach(function(element, index) {
            var nodeName = "A"+(index+1);
            var node = this._constructedScene.node.getChildByName(nodeName);
            if(node) {
                node.setAnchorPoint(cc.p(0.5,0.5));
                node.setTitleFontSize(xc.storyFontSize);
                node.setTitleColor(xc.storyFontColor);
                node.setTitleFontName(xc.storyFontName);
                node.setTouchEnabled(true);
                var output = "";
                if(element.length > 30) {
                    var i = 30;
                    while(i != element.length && element.element(i) != " ")
                    {
                        i++;
                    }
                    output += element.substring(0,i);
                    output += "\n";
                    output += element.substring(i, element.length);
                } else {
                    output = element;
                }
                cc.log("output:" + output);
                node.setTitleText(output);
                node.addTouchEventListener(this.answerSelected, this);
                if(element == this._question.answer) {
                    context._correctAnswerNode = nodeName;
                } 
            }
        }, this);
    } ,

    answerSelected: function(sender, type)
    {
        switch (type)
        {
            case ccui.Widget.TOUCH_BEGAN:
                break;

            case ccui.Widget.TOUCH_MOVED:                
                break;

            case ccui.Widget.TOUCH_ENDED:
                cc.log('clicked' + sender.getTitleText());
                this.verifyAnswer(sender);
                break;

            case ccui.Widget.TOUCH_CANCELLED:
                
                break;                
            }
    },
    
    scaleAnimation: function(correctAnswerNode) {
        var increase = new cc.ScaleTo(0.5, 1.2);
        var decrease = new cc.ScaleTo(0.5, 1); 
        var delay = new cc.DelayTime(1);
        var repeatAction = new cc.Repeat(new cc.Sequence(increase, decrease, delay), 3);
        var sequenceAction = new cc.Sequence(repeatAction, new cc.CallFunc(this.resetNumberOfIncorrectAnswered, this));
        correctAnswerNode.runAction(sequenceAction);          
    },

    resetNumberOfIncorrectAnswered: function() {
        this._numberOfTimesInCorrectAnswered = 0;        
    },

    showHintAnimation: function() {
        if(this._numberOfTimesInCorrectAnswered > 2) {
            //glow correct answer            
            var correctAnswerNode = this._constructedScene.node.getChildByName(this._correctAnswerNode);
            if(correctAnswerNode) {
               this.scaleAnimation(correctAnswerNode);                           
            }
        }
    },

    hintForCorrectAnswer: function(sender, isCorrectAnswered) {
        if(!isCorrectAnswered) {
            this._numberOfTimesInCorrectAnswered++;
            var x = sender.getPosition().x;
            var y = sender.getPosition().y;
            var moveLeft = new cc.moveTo(0.1, cc.p(sender.getPosition().x - 20, sender.getPosition().y));
            var moveRight = new cc.moveTo(0.1, cc.p(sender.getPosition().x + 40, sender.getPosition().y));
            var moveOriginal = new cc.moveTo(0.1, cc.p(x, y));
            var repeatAction = new cc.Repeat(new cc.Sequence(moveLeft, moveRight), 3);
            var sequenceAction = new cc.Sequence(repeatAction, moveOriginal, new cc.CallFunc(this.showHintAnimation, this));
            sender.runAction(sequenceAction);          
            if(xc.NarrateStoryLayer.res.wrongAnswerSound_json) {
                cc.audioEngine.playEffect(xc.NarrateStoryLayer.res.wrongAnswerSound_json, false);
            }                                                                                    
        } else {
            this._numberOfTimesInCorrectAnswered = 0;
            if(xc.NarrateStoryLayer.res.correctAnswerSound_json) {
                cc.audioEngine.playEffect(xc.NarrateStoryLayer.res.correctAnswerSound_json, false);
            }                                                      
        }

    },

    verifyAnswer: function(sender) {
        var isCorrectAnswered = sender.getTitleText().toLowerCase() === this._question.answer.toLowerCase();
        this.hintForCorrectAnswer(sender, isCorrectAnswered);        
        this.callback.call(this._callbackContext, sender, isCorrectAnswered, isCorrectAnswered);        
    }
});
