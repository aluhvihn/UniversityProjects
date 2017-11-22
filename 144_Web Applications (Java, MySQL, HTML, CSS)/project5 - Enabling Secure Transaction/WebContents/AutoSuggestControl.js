function AutoSuggestControl(text) {
    this.origText = "";
    this.cur = -1;
    this.layer = null;
    this.textBox = text;
    this.init();
}

AutoSuggestControl.prototype.init = function(){
    var that = this;
    this.textBox.onkeyup = function (evt) {
        evt = evt || window.event; 
        that.handleKeyUp(evt);
    };
    this.textBox.onkeydown = function (evt) {
        evt = evt || window.event;   
        that.handleKeyDown(evt);
    };
    this.textBox.onblur = function () {
        this.layer.style.visibility = "hidden";
    };
    this.createDropDown();
}

AutoSuggestControl.prototype.handleKeyUp = function(evt){        
    var key = evt.keyCode;

    if (key == 8 || key == 46) {
        this.requestSuggestions();
    } else if (key < 32 || (key >= 33 && key < 46) || (key >= 112 && key <= 123)) {
    } else {
      this.requestSuggestions();
    }
};

AutoSuggestControl.prototype.handleKeyDown = function(evt){        
    switch(evt.keyCode) {
        case 38: // Up
            this.cur--;
            if(this.cur < 0) {
                this.cur = this.layer.childNodes.length;
            }
            this.updateSuggestions();
            break;
        case 40: // Down
            this.cur++;
            if(this.cur > this.layer.childNodes.length) {
                this.cur = 0;
            }
            this.updateSuggestions();
            break;
        case 13: // Enter
            this.layer.style.visibility = "hidden";
            break;
    }
};


AutoSuggestControl.prototype.createDropDown = function() {
    this.layer = document.createElement("div");
    this.layer.className = "suggestions";
    this.layer.style.visibility = "hidden";
    this.layer.style.width = this.textBox.offsetWidth;

    var that = this;
    this.layer.onmouseup = 
    this.layer.onmousedown = 
    this.layer.onmouseover = function (evt) {
 
        evt = evt || window.event;
        var target = evt.target || evt.srcElement;
        
        if (evt.type == "mousedown") {
            that.textBox.value = target.firstChild.nodeValue;
            this.layer.style.visibility = "hidden";
        } else if (evt.type == "mouseover") {
            var target = evt.target || evt.srcElement;
            for (var i=0; i < that.layer.childNodes.length; i++) {
                var node = that.layer.childNodes[i];
                if (target == node) {
                    that.cur = i+1;
                }
            }
            that.updateSuggestions();
        } else {
            that.textBox.focus();
        }
    };

    document.body.appendChild(this.layer);
}

AutoSuggestControl.prototype.requestSuggestions = function(){
    this.origText = this.textBox.value;
    this.cur = 0;
    var that = this;
    requestSuggestions(this.origText, function(result){ 
        that.onSuggestComplete(result)
    });
}

AutoSuggestControl.prototype.updateSuggestions = function(){
    if (this.cur == 0){
        this.textBox.value = this.origText;  
        this.highlightSuggestion(null);
    } else if (this.layer.childNodes.length > 0 && this.cur > 0) {
        var node = this.layer.childNodes[this.cur-1];
        this.highlightSuggestion(node);
        this.textBox.value = node.firstChild.nodeValue;   
    }
}

AutoSuggestControl.prototype.highlightSuggestion = function(node){
    for (var i=0; i < this.layer.childNodes.length; i++) {
        var oNode = this.layer.childNodes[i];
        if (oNode == node) {
            oNode.className = "current"
        } else if (oNode.className == "current") {
            oNode.className = "";
        }
    }
}

AutoSuggestControl.prototype.onSuggestComplete = function(result){
    if (result.length > 0) {
        this.showSuggestions(result);
    } else {
        this.layer.style.visibility = "hidden";
    }
}


AutoSuggestControl.prototype.showSuggestions = function(result){        
    var div = null;
    this.layer.innerHTML = "";    
    for (var i=0; i < result.length; i++) {
        div = document.createElement("div");
        div.appendChild(document.createTextNode(result[i]));
        this.layer.appendChild(div);
    }
    var offset = this.getLeftAndTop();
    this.layer.style.left = offset[0] + "px";
    this.layer.style.top = (offset[1] + this.textBox.offsetHeight) + "px";
    this.layer.style.visibility = "visible";
};


AutoSuggestControl.prototype.getLeftAndTop = function(){ 
    var node = this.textBox;
    var left = 0, top =0;
    
    while(node.tagName != "BODY") {
        left += node.offsetLeft;
        top += node.offsetTop;
        node = node.offsetParent;
    }
    return [left, top];
}

              
function requestSuggestions(q, callback) {
    var result = [];
    console.l
    var xmlHttp = new XMLHttpRequest();
    if (xmlHttp == null) {
        alert("Your browser does not support AJAX!");
        callback([]);
        return;
    }

    var requestURL = "/eBay/suggest?q="+encodeURI(q);
    
    xmlHttp.open("GET", requestURL);
    xmlHttp.onreadystatechange = function(){
        if (xmlHttp.readyState == 4 && xmlHttp.status==200) {
            var xmlDoc = xmlHttp.responseText;
            
            var xmldom = (new DOMParser()).parseFromString(xmlDoc, 'text/xml');
            var resultList = xmldom.getElementsByTagName("suggestion");
            for (var i=0; i < resultList.length; i++) {
                result.push(resultList[i].attributes[0].nodeValue);
            }
            callback(result);

        }
    
    }
    xmlHttp.send(null);
}     

window.onload = function () {
    var textBox = new AutoSuggestControl(document.getElementById("searchText"));        
}

