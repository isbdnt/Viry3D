/*
* Viry3D
* Copyright 2014-2019 by Stack - stackos@qq.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

let gl = null;
const Engine = {
    Init: null,
    Done: null,
    Update: null,
	MemoryAlloc: null,
	MemoryFree: null,
	OnLoadFileFromUrlComplete: null,
    events: new Array(),
    down: false,
    audio: null,
    audio_src: "",
    audio_paused: false,
};

const EventType = {
    MouseDown: 0,
    MouseMove: 1,
    MouseUp: 2,
    MouseWheel: 3,
    KeyDown: 4,
    KeyUp: 5,
    InputCharacter: 6,
};

function OnMouseDown(e) {
    const x = e.clientX - gl.canvas.offsetLeft;
    const y = e.clientY - gl.canvas.offsetTop;

    if (!Engine.down) {
        Engine.down = true;
        Engine.events.push({
            type: EventType.MouseDown,
            x: x,
            y: y,
        });
    }
}

function OnMouseMove(e) {
    const x = e.clientX - gl.canvas.offsetLeft;
    const y = e.clientY - gl.canvas.offsetTop;

    Engine.events.push({
        type: EventType.MouseMove,
        x: x,
        y: y,
    });
}

function OnMouseUp(e) {
    const x = e.clientX - gl.canvas.offsetLeft;
    const y = e.clientY - gl.canvas.offsetTop;

    if (Engine.down) {
        Engine.down = false;
        Engine.events.push({
            type: EventType.MouseUp,
            x: x,
            y: y,
        });
    }
}

function OnMouseWheel(e) {
    const delta = e.deltaY;

    Engine.events.push({
        type: EventType.MouseWheel,
        delta: delta,
    });
}

const KeyMap = {
    Escape: 27,
    ArrowLeft: 276,
    ArrowUp: 273,
    ArrowRight: 275,
    ArrowDown: 274,
    Backspace: 8,
    Tab: 9,
    Enter: 13,
};

function MapKey(e) {
    const key = e.key;
    const code = e.code;

    if (key.length === 1) {
        const char_code = key.charCodeAt(0);

        if (char_code >= 65 && char_code <= 90) {
            return 97 + char_code - 65;
        } else if (char_code >= 97 && char_code <= 122) {
            return char_code;
        } else if (char_code >= 48 && char_code <= 57) {
            return char_code;
        } else {
            if (key === " " ||
                key === "`" ||
                key === "-" ||
                key === "=" ||
                key === "[" ||
                key === "]" ||
                key === "\\" ||
                key === ";" ||
                key === "'" ||
                key === "," ||
                key === "." ||
                key === "/") {
                return char_code;
            }
        }
    } else {
        if (KeyMap.hasOwnProperty(key)) {
            return KeyMap[key];
        } else {
            if (key === "Shift") {
                if (code === "ShiftLeft") {
                    return 304;
                } else if (code === "ShiftRight") {
                    return 303;
                }
            } else if (key === "Control") {
                if (code === "ControlLeft") {
                    return 306;
                } else if (code === "ControlRight") {
                    return 305;
                }
            }
        }
    }

    return -1;
}

function InputCharacter(e) {
    const key = e.key;
    if (key.length === 1) {
        const char_code = key.charCodeAt(0);
        if (char_code >= 32 && char_code <= 126) {
            Engine.events.push({
                type: EventType.InputCharacter,
                key: char_code,
            });
        }
    }
}

function OnKeyDown(e) {
    Engine.events.push({
        type: EventType.KeyDown,
        key: MapKey(e),
    });

    InputCharacter(e);
}

function OnKeyUp(e) {
    Engine.events.push({
        type: EventType.KeyUp,
        key: MapKey(e),
    });
}

const Platform = {
    Android: 0,
    iOS: 1,
    Mac: 2,
    Windows: 3,
    Other: 4,
};

function GetPlatform() {
    const agent = navigator.userAgent;
    if (agent.indexOf("Android") >= 0) {
        return Platform.Android;
    } else if (agent.indexOf("iPhone") >= 0 || agent.indexOf("iPad") >= 0 || agent.indexOf("iPod") >= 0) {
        return Platform.iOS;
    } else if (agent.indexOf("Mac") >= 0) {
        return Platform.Mac;
    } else if (agent.indexOf("Windows") >= 0) {
        return Platform.Windows;
    } else {
        return Platform.Other;
    }
}

function Render() {
    const msg = {
        events: Engine.events,
    };

    Engine.Update(JSON.stringify(msg));

    // clear events
    Engine.events.splice(0, Engine.events.length);

    window.requestAnimationFrame(Render);
}

// functions for C call
function PlayAudio(msg) {
    const params = JSON.parse(msg);

    if (Engine.audio === null) {
        Engine.audio = document.createElement("audio");
        Engine.audio.autoplay = true;
    }

    if (Engine.audio_src === params.url && Engine.audio.loop === params.loop && Engine.audio_paused) {
        Engine.audio.play();
        Engine.audio_paused = false;
    } else {
        Engine.audio.src = params.url;
        Engine.audio.loop = params.loop;
        Engine.audio_src = params.url;
    }
}

function PauseAudio(msg) {
    if (Engine.audio !== null) {
        Engine.audio.pause();
        Engine.audio_paused = true;
    }
}

function StopAudio(msg) {
    if (Engine.audio !== null) {
        Engine.audio.pause();
        Engine.audio.currentTime = 0;
    }
}

function LoadFileFromUrlAsync(request_id, url) {
	console.log("LoadFileFromUrlAsync :" + request_id + " :" + url);

	const req = new XMLHttpRequest();
	req.open("GET", url, true);
	req.responseType = "arraybuffer";

	req.onload = function (event) {
        if (req.readyState === 4 && req.status === 200) {
            const buffer = req.response;
            if (buffer) {
			    const bytes = new Uint8Array(buffer);
			    const p = Engine.MemoryAlloc(bytes.length);
			    Module.HEAP8.set(bytes, p);
			    Engine.OnLoadFileFromUrlComplete(request_id, url, p, bytes.length);
			    Engine.MemoryFree(p);
		    }
        } else {
            console.log("readyState:" + req.readyState, "status:" + req.status);
        }
	};

	req.send(null);
}
//

function InitLoading() {
    const canvas = document.getElementById("canvas2d");
    const c = canvas.getContext("2d");

    const draw = function () {
        c.drawImage(img, 0, 0, img.width, img.height, 0, 0, canvas.width, canvas.height);
        c.font = "40px Arial";
        c.fillStyle = "#ffffff";
        c.textAlign = "center";
        c.fillText("Loading...", canvas.width / 2, canvas.height - 60);
    };

    SetCanvasSize(canvas, GetPlatform());

    const img = new Image();
    img.src = "texture/logo720p.png";
    if (img.complete) {
        draw();
    } else {
        img.onload = function () {
            draw();
        }
    }
}
InitLoading();

function RemoveLoading() {
    const canvas = document.getElementById("canvas2d");
    canvas.remove();
}

function SetCanvasSize(canvas, platform) {
    if (platform === Platform.Android || platform === Platform.iOS || document.body.clientWidth < 1280) {
        canvas.width = document.body.clientWidth;
        canvas.height = canvas.width * 720 / 1280;
    } else {
        canvas.width = 1280;
        canvas.height = 720;
    }
}

function Main() {
    Engine.Init = Module.cwrap("InitEngine", null, ["string"]);
    Engine.Done = Module.cwrap("DoneEngine", null, ["string"]);
    Engine.Update = Module.cwrap("UpdateEngine", null, ["string"]);
	Engine.MemoryAlloc = Module.cwrap("MemoryAlloc", "number", ["number"]);
	Engine.MemoryFree = Module.cwrap("MemoryFree", null, ["number"]);
	Engine.OnLoadFileFromUrlComplete = Module.cwrap("OnLoadFileFromUrlComplete", null, ["number", "string", "number", "number"]);

	let force_gles2 = true;
    let glesv3 = false;
    const canvas = Module.canvas;
    let context = 0;
	if (!force_gles2) {
		context = GL.createContext(canvas, {
			majorVersion: 2,
			minorVersion: 0,
			antialias: false,
			alpha: false
		});
	}
    if (context === 0) {
        context = GL.createContext(canvas, {
            majorVersion: 1,
            minorVersion: 0,
            antialias: false,
            alpha: false
        });
    } else {
        glesv3 = true;
    }
    GL.makeContextCurrent(context);
    gl = Module.ctx;

    const platform = GetPlatform();
    const has_touch = !!(('ontouchstart' in window) || (window.DocumentTouch && document instanceof DocumentTouch));

    console.log(navigator.userAgent);
    console.log("Has touch " + has_touch);

    SetCanvasSize(canvas, platform);

    if (has_touch) {
        canvas.addEventListener("touchstart", function(e) {
            e.preventDefault();
            const touches = e.changedTouches;
            if (touches.length > 0) {
                OnMouseDown(touches[0]);
            }
        });
        canvas.addEventListener("touchmove", function(e) {
            e.preventDefault();
            const touches = e.changedTouches;
            if (touches.length > 0) {
                OnMouseMove(touches[0]);
            }
        });
        canvas.addEventListener("touchend", function(e) {
            e.preventDefault();
            const touches = e.changedTouches;
            if (touches.length > 0) {
                OnMouseUp(touches[0]);
            }
        });
        canvas.addEventListener("touchcancel", function(e) {
            e.preventDefault();
            const touches = e.changedTouches;
            if (touches.length > 0) {
                OnMouseUp(touches[0]);
            }
        });
    } else {
        canvas.addEventListener("mousedown", OnMouseDown, false);
        canvas.addEventListener("mousemove", OnMouseMove, false);
        canvas.addEventListener("mouseup", OnMouseUp, false);
        canvas.addEventListener("wheel", OnMouseWheel, false);
    }

    document.addEventListener("keydown", OnKeyDown, false);
    document.addEventListener("keyup", OnKeyUp, false);

    const canvas_width = canvas.width;
    const canvas_height = canvas.height;

    const msg = {
        name: "Viry3D",
        width: canvas_width,
        height: canvas_height,
        glesv3: glesv3,
        platform: platform,
    };

    Engine.Init(JSON.stringify(msg));

    Render();

    RemoveLoading();
    canvas.style = "display: initial;";
}

var Module = {
    preRun: [],
    postRun: function () {
        Main();
    },
    print: (function () {
        return function (text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            console.log(text);
        };
    })(),
    printErr: function (text) {
        if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
        if (0) { // XXX disabled for safety typeof dump == 'function') {
            dump(text + '\n'); // fast, straight to the real console
        } else {
            console.error(text);
        }
    },
    canvas: (function () {
        var canvas = document.getElementById("canvas");

        // As a default initial behavior, pop up an alert when webgl context is lost. To make your
        // application robust, you may want to override this behavior before shipping!
        // See http://www.khronos.org/registry/webgl/specs/latest/1.0/#5.15.2
        canvas.addEventListener("webglcontextlost", function (e) {
            alert("WebGL context lost. You will need to reload the page.");
            e.preventDefault();
        }, false);

        return canvas;
    })()
};

window.onerror = function (event) {
    Module.setStatus = function (text) {
        if (text) Module.printErr("[post-exception status] " + text);
    };
};
