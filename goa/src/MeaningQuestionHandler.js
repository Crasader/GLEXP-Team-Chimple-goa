/// <reference path="cocos2d-typescript-definitions-master/cocos2d/cocos2d-lib.d.ts" />
var xc = xc || {};
xc.MeaningQuestionHandler = cc.Layer.extend({
    _textContentMargin: 100,
    _width:0,
    _height: 0,
    _nodeJSON: "",
    _textContentMargin: 0,
    _constructedScene: null,    
    _answers:[],
    _numberOfTimesInCorrectAnswered: 0,
    _selectedQuestionForAnswer: null,
    _selectedAnswer: null,
    _totalCorrectAnswers: 0,
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
        this.configureQuestions();
        this.configureAnswers();
    },

    showQuestionTemplate: function() {
        this._constructedScene = ccs.load(this._nodeJSON,xc.path);
        this._constructedScene.node.retain();
        
        if (this._constructedScene.node) {
            this._callbackContext.addChild(this._constructedScene.node,0);
        }                        
    },

    configureQuestions: function() {
        //randomize array
        //find out question node
        this._questions = Object.getOwnPropertyNames(this._question).map(function(element) {
                if(element !== 'type') return element
            }
        );

        this._questions = this._questions.filter(function( element ) {
            return element !== undefined;
        });

        this._questions = this._questions.map(function(n){ return [Math.random(), n] })
             .sort().map(function(n){ return n[1] });
        
        this._questions.forEach(function(question, index) {
            var nodeName = "Q"+(index+1);
            var node = this._constructedScene.node.getChildByName(nodeName);
            if(node) {
                node.selectedIndex = index;
                node.setAnchorPoint(cc.p(0.5,0.5));
                node.setTitleFontSize(xc.storyFontSize);
                node.setTitleColor(xc.storyFontColor);
                node.setTitleFontName(xc.storyFontName);
                node.setTouchEnabled(true);
                node.setTitleText(question);
                node.addTouchEventListener(this.questionSelected, this);
            }
        }, this);
    },    

    configureAnswers: function() {
        var context = this;      
        context._answers = [];
        var obj = this._question;  
        Object.keys(context._question).forEach(function (key) {
            var val = context._question[key];
            context._answers.push(val);
    
        });
        
        this._answers = this._answers.filter(function(e) { return e !== "meanings" });

        var alreadySelectedAnswers = [];

        this._answers.forEach(function(element, index) {
            var oQuestion = this._questions[index];
            if(this._question.hasOwnProperty(oQuestion)) {
                var realAnswer = this._question[oQuestion];
                var remainingAnswers = this._answers.filter(function(e) { 
                        return e !== realAnswer &&  alreadySelectedAnswers.indexOf(e) < 0;
                    }
                );   

                if(remainingAnswers.length > 0) {
                    alreadySelectedAnswers.push(remainingAnswers[0]);
                    var nodeName = "A"+(index+1);
                    var node = this._constructedScene.node.getChildByName(nodeName);
                    if(node) {
                        node.setAnchorPoint(cc.p(0.5,0.5));
                        node.setTitleFontSize(xc.storyFontSize);
                        node.setTitleColor(xc.storyFontColor);
                        node.setTitleFontName(xc.storyFontName);
                        node.setTouchEnabled(true);
                        node.selectedIndex = index;
                        var result = [];
                        cc.log('remainingAnswers[0]:' + remainingAnswers[0]);
                        var qText = remainingAnswers[0];
                        remainingAnswers[0].replace(/(.{30}\w+)\s(.+)/, function(_,a,b) { result.push(a,b); });
                        if(result.length > 0) {
                           qText = result.join('\n');     
                        }
                        node.setTitleText(qText);
                        cc.log("qText setting:" + qText);
                        node.addTouchEventListener(this.answerSelected, this);
                    }                    
                }                             
            };
            
        }, this);
    },

    questionSelected:function(sender, type) {
        switch (type)
        {
            case ccui.Widget.TOUCH_BEGAN:
                if(this._selectedQuestionForAnswer != null) {
                    this._selectedQuestionForAnswer.setEnabled(true);
                    this._selectedQuestionForAnswer.setHighlighted(false);
                }                                      
                break;

            case ccui.Widget.TOUCH_ENDED:
                this._selectedQuestionForAnswer = sender;                   
                sender.setHighlighted(true);
                sender.setEnabled(false);
            break;
        }
    },

    answerSelected: function(sender, type)
    {
        switch (type)
        {
            case ccui.Widget.TOUCH_BEGAN:
                break;

            case ccui.Widget.TOUCH_MOVED:                
                break;

            case ccui.Widget.TOUCH_ENDED:
                if(this._selectedQuestionForAnswer != null) {
                    this.verifyAnswer(sender, this._selectedQuestionForAnswer);
                    this._selectedQuestionForAnswer.setEnabled(true);
                    this._selectedQuestionForAnswer.setHighlighted(false);                    
                }
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
        var sequenceAction = new cc.Sequence(repeatAction, new cc.CallFunc(this.updateSelectedQuestionForAnswer, this));
        correctAnswerNode.runAction(sequenceAction);          
    },

    updateSelectedQuestionForAnswer: function() {
        this._numberOfTimesInCorrectAnswered = 0;              
    },

    showHintAnimation: function() {
        if(this._numberOfTimesInCorrectAnswered > 2) {
            //glow correct question and answer      
            var aNode = null;      
            if(this._selectedQuestionForAnswer) {
               var aText = this._question[this._selectedQuestionForAnswer.getTitleText()];
               this._constructedScene.node.children.forEach(function(child) {                   
                  if(child.getName().startsWith("A"))
                  {                       
                      var str2 = child.getTitleText().replace(/\n|\r/g, " ");
                      if(str2.trim().toLowerCase() == aText.trim().toLowerCase()) {
                            aNode = child;
                      }                      
                  }
               });
               this.scaleAnimation(this._selectedQuestionForAnswer);
                if(aNode) {
                    this.scaleAnimation(aNode);
                    this._selectedQuestionForAnswer = null;
                }                                          
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
        } else {
            this._numberOfTimesInCorrectAnswered = 0;
        }

    },

    swipeAnswers: function(sender, questionNode) {
        cc.log('sender:' + sender.selectedIndex);
        cc.log('questionNode:' + questionNode.selectedIndex);

        //get node at index of questionNode

        var node2NewName = "A"+(questionNode.selectedIndex+1);
        var node1 = this._constructedScene.node.getChildByName(node2NewName);

        var node1NewName = "A"+(sender.selectedIndex+1);
        var node2 = this._constructedScene.node.getChildByName(node1NewName);

        var moveNode2Action = new cc.moveTo(1.5, cc.p(node1.getPosition().x, node1.getPosition().y));
        var moveNode1Action = new cc.moveTo(1.5, cc.p(node2.getPosition().x, node2.getPosition().y));
        node1.runAction(new cc.Sequence(moveNode1Action, new cc.CallFunc(this.updateNodeName, this, node1NewName)));        
        node2.runAction(new cc.Sequence(moveNode2Action, new cc.CallFunc(this.disableNodesForCorrectAnswer, this, questionNode, node2NewName)));
        node2.setName(node2NewName);
        cc.log('disabled name 111:' + node2NewName);

        node1.selectedIndex = sender.selectedIndex;
        node2.selectedIndex = questionNode.selectedIndex;
    },

    updateNodeName:function(sender, nodeName) {
        cc.log('updated name 111:' + nodeName);
        sender.setName(nodeName);
    },
    

    disableNodesForCorrectAnswer:function(sender, questionNode) {
        sender.setEnabled(false);
        questionNode.setEnabled(false);

        if(this._totalCorrectAnswers == 4) {
            this.callback.call(this._callbackContext, sender, true, true);
        } else {
            this.callback.call(this._callbackContext, sender, true, false);
        }                      
        
    },

    verifyAnswer: function(sender, questionNode) {
        var str2 = sender.getTitleText().replace(/\n|\r/g, " ");
        var isCorrectAnswered = str2.trim().toLowerCase() === this._question[questionNode.getTitleText().trim()].toLowerCase();
        if(isCorrectAnswered) {
            this._totalCorrectAnswers++;
            this.swipeAnswers(sender, questionNode);
        } else {
            this.hintForCorrectAnswer(sender, isCorrectAnswered);
        }
    }
});
