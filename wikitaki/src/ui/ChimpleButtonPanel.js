chimple.ButtonPanel = ccui.Layout.extend({
    ctor: function (position, size, numButtonsPerRow, numButtonsPerColumn, configuration, callBackFunction, callBackContext) {
        this._super();
        this._configuration = configuration;
        this.setBackGroundColorType(ccui.Layout.BG_COLOR_SOLID);
        this.setBackGroundColor(cc.color.GREEN);
        this.setPosition(position);
        this._currentSelectedItem = null;
        this._callBackFunction = callBackFunction;
        this._callBackContext = callBackContext;
        var index = 0;
        for (pageIndex = 0; pageIndex < configuration.length / (numButtonsPerRow * numButtonsPerColumn); pageIndex++) {
            for (var rowIndex = 0; rowIndex < numButtonsPerColumn; rowIndex++) {
                for (var colIndex = 0; colIndex < numButtonsPerRow; colIndex++) {
                    if (index < configuration.length) {
                        cc.log('configuration[index]:' + configuration[index]);
                        var item = new ccui.Button(configuration[index]['icon'], configuration[index]['cIcon']);
                        item.addTouchEventListener(this.itemSelected, this);
                        item.setPosition(pageIndex * size.width + (colIndex + 0.5) * size.width / numButtonsPerRow, size.height - (rowIndex + 0.5) * size.height / numButtonsPerColumn);
                        item.setName(configuration[index]['icon']);
                        item._configuration = configuration[index];
                        if (configuration[index].hasOwnProperty('json')) {
                            item._jsonFileToLoad = configuration[index]['json'];
                            item._configurationType = configuration[index].type;    
                            item.dataType = "json";                            
                        } else if (configuration[index].hasOwnProperty('png')) {
                            item._pngFileToLoad = configuration[index]['png'];                            
                            item.dataType = "png";
                        }
                        index++;
                        this.addChild(item);

                    }
                }
            }
        }
        this.setContentSize(cc.size(Math.ceil(configuration.length / (numButtonsPerRow * numButtonsPerColumn)) * size.width, size.height));        
    },
    
    
    itemSelected: function (sender, type) {
        switch (type) {
            case ccui.Widget.TOUCH_BEGAN:
                if (this._currentSelectedItem != null && this._currentSelectedItem != sender) {
                    this._currentSelectedItem.setHighlighted(false);
                }
                break;
            case ccui.Widget.TOUCH_ENDED:
                this.selectButton(sender);
                break;
        }
    },
    selectButton: function (button) {
        cc.log(button);
        this._currentSelectedItem = button;
        button.setHighlighted(true);
        if (this._callBackFunction != null && this._callBackContext != null) {
            this._callBackFunction.call(this._callBackContext, this._currentSelectedItem);
        }

    },
    getButtonByName: function(name) {
        return this.getChildByName(name);
    }
}); 