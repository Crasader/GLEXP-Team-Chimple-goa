import Texture from './Texture.js';
import TileTexture from './TileTexture.js';
import Surface from './Surface.js';
import SpecialAttribute from './SpecialAttribute.js';
import EnableInputs from './EnableInputs.js';
import AttributesChangedSignal from '../../storybuilder/objects/AttributesChangedSignal.js'
import SpecialAttributesChangedSignal from '../../storybuilder/objects/SpecialAttributesChangedSignal.js'
import UpdateAttributesSignal from '../../storybuilder/objects/UpdateAttributesSignal.js'
import RecordInfo from '../../storybuilder/objects/RecordInfo.js';
import EnableAttributeEditorSignal from '../../storybuilder/objects/EnableAttributeEditorSignal.js';
import ShowAttributeEditorSignal from '../../storybuilder/objects/ShowAttributeEditorSignal.js';
import PlayPauseSignal from '../../storybuilder/objects/PlayPauseSignal.js';
import PlayResumeSignal from '../../storybuilder/objects/PlayResumeSignal.js';
import TextData from '../../storybuilder/objects/TextData.js';

var _ = require('lodash');


export default class Item extends EnableInputs(Phaser.Sprite) {
    constructor(game, x, y, key, frame, modifiedBit) {
        super(game, x, y, key, frame);
        game.physics.enable(this);
        this.anchor.set(0.5, 1);
        this.modifiedBit = modifiedBit;
        //Any Attribute Changes then dispatch signal        
        this.onAttributesChanged = new AttributesChangedSignal();

        //Special Attribute Changes
        this._specialAttributeChangedSignal = new SpecialAttributesChangedSignal();

        this.onUpdateAttributesSignal = new UpdateAttributesSignal();
        this.onUpdateAttributesSignal.add(this.changeAttributes, this);

        //Allow item to invoke ShowAttributeEditorSignal()
        this._showAttributeEditorSignal = new ShowAttributeEditorSignal(game);
        //added for testing purpose, will be replaced by Special Attribute Class later...
        this._userGeneratedText = null;

        this._specialAttribute = new SpecialAttribute(game);

        this._playPauseSignal = new PlayPauseSignal();
        this._playResumeSignal = new PlayResumeSignal();
    }

    enableInputs(instance, iterateInside) {
        super.enableInputs(instance, iterateInside);
        this.input.priorityID = 2;
    }
    
    
    addText(textData) {
        this._specialAttribute.addText(textData); 
    }
    
    applyText(whichTextIndex, apply) {
        this._specialAttribute.applyText(whichTextIndex, apply);
        let appliedTextData = this._specialAttribute.getText(whichTextIndex);
        let text = appliedTextData.text;
        //later you should get text, fontColor, backgroundColor, style 
        if (game._inRecordingMode) {
            this._specialAttributeChangedSignal.dispatch({ uniquename: this._uniquename, x: this.x, y: this.y, scaleX: this.scale.x, scaleY: this.scale.y, angle: this.angle, recordingAttributeKind: RecordInfo.TEXT_RECORDING_TYPE, userGeneratedText: text});
        }        
    }

    // set text(text) {
    //     this._userGeneratedText = text;
    //     if (game._inRecordingMode) {
    //         this._specialAttributeChangedSignal.dispatch({ uniquename: this._uniquename, x: this.x, y: this.y, scaleX: this.scale.x, scaleY: this.scale.y, angle: this.angle, recordingAttributeKind: RecordInfo.TEXT_RECORDING_TYPE, userGeneratedText: this._userGeneratedText });
    //     }
    // }

    drawBoundingBox(color) {
        let box = this.addChild(new Phaser.Graphics(this.game, -this.offsetX, -this.offsetY));
        box.lineStyle(1, color);
        box.beginFill(0x000000, 0);
        box.drawRect(0, 0, this.width, this.height);
        box.endFill();
        return box;
    }

    set uniquename(name) {
        this._uniquename = name;
    }

    get uniquename() {
        return this._uniquename;
    }


    overlapHandler(obj1, obj2) {
        // console.log(obj2);
        if (obj2 instanceof TileTexture) {
            return;
        }
        let CollideObject = obj2.parent.toGlobal(obj2.parent.position);
        //let distance = obj1.game.physics.arcade.distanceBetween(obj1.parent, obj2);
        let distance = Math.abs(obj1.y - CollideObject.y);
        if (!this.closestDistance || this.closestDistance > distance) {
            this.closestDistance = distance;
            this.closestObject = obj2;
        }
    }

    update() {
        var self = this;
        if (game._inRecordingMode) {
            console.log('in recording mode');
            this.onAttributesChanged.dispatch({ uniquename: this._uniquename, x: this.x, y: this.y, scaleX: this.scale.x, scaleY: this.scale.y, angle: this.angle, recordingAttributeKind: RecordInfo.DEFAULT_RECORDING_TYPE });
        } else if (game._inPlayMode) {
            console.log('in play mode');
            if (this._changeAttributes != null && this._changeAttributes.size > 0) {
                let json = this._changeAttributes.get(this.uniquename);
                var recordedInfo = RecordInfo.fromJSON(json);
                console.log('this.x: ' + this.x + " this.y:" + this.y);
                this.x = recordedInfo.x;
                this.y = recordedInfo.y;
                this.scale.x = recordedInfo.scaleX;
                this.scale.y = recordedInfo.scaleY;
                this.angle = recordedInfo.angle;
                console.log('recordedInfo.x:' + recordedInfo.x + "recordedInfo.y:" + recordedInfo.y);

                //if we have received TEXT KIND data
                if (recordedInfo.recordingAttributeKind == RecordInfo.TEXT_RECORDING_TYPE) {
                    //send an signal to show Text PopUp to User
                    console.log('show text popup to User' + recordedInfo.userGeneratedText);
                    $('#element_to_pop_up').bPopup({onClose: function() {
                        console.log('closing pop up');
                        self._playResumeSignal.dispatch();
                    }});

                    var url = "make" + '.json';
                    console.log('url ' + url);
                    var meaning = '';
                    $.getJSON(url, function(jd) {
                        meaning = jd.meaning;
                        meaning = $(meaning).text();
                        $("#word").text(url);
                        $("#meaning_content").text(meaning);
                        $("#example_content").text(jd.exmaples);
                        $("#image_content").attr("src", jd.image);
                    });
                    
                    this._playPauseSignal.dispatch();
                }
            }
        }
    }

    changeAttributes(data) {
        this._changeAttributes = data;
    }

    toJSON() {
        let json = {
            _class: "Item",
            x: this.x,
            y: this.y,
            key: this.key,
            frame: this.frameName,
            uniquename: this.uniquename,
            modifiedBit: this.modifiedBit,
            specialAttributes : this._specialAttribute
        }
        return json;
    }

    static fromJSON(game, j) {
        let val = new Item(game, j.x, j.y, j.key, j.frame, j.modifiedBit);
        val.uniquename = j.uniquename;
        return val;
    }

}