
var video = document.querySelector('video');
var text = document.getElementById('text');
var canvas1 = document.getElementById('qr-canvas');
var context1 = canvas1.getContext('2d');
var mediaStreamTrack;

// Compatible with the code
window.URL = (window.URL || window.webkitURL || window.mozURL || window.msURL);
if (navigator.mediaDevices === undefined) {
    navigator.mediaDevices = {};
}
if (navigator.mediaDevices.getUserMedia === undefined) {
    navigator.mediaDevices.getUserMedia = function(constraints) {
        var getUserMedia = navigator.webkitGetUserMedia || navigator.mozGetUserMedia || navigator.msGetUserMedia;
        if (!getUserMedia) {
            return Promise.reject(new Error('getUserMedia is not implemented in this browser'));
        }
        return new Promise(function(resolve, reject) {
            getUserMedia.call(navigator, constraints, resolve, reject);
        });
    }
}

//Camera call configuration
var mediaOpts = {
    audio: false,
    video: true,
    video: { facingMode: "environment"} // or "user"
    // video: { width: 1280, height: 720 }
    // video: { facingMode: { exact: "environment" } }// or "user"
}

// The callback
function successFunc(stream) {
    mediaStreamTrack = stream;
    video = document.querySelector('video');
    if ("srcObject" in video) {
        video.srcObject = stream
    } else {
        video.src = window.URL && window.URL.createObjectURL(stream) || stream
    }
    video.play();
}
function errorFunc(err) {
    alert(err.name);
}

// Officially start the camera
function openMedia(){
    navigator.mediaDevices.getUserMedia(mediaOpts).then(successFunc).catch(errorFunc);
}

//Officially start the camera
function closeMedia(){
    mediaStreamTrack.getVideoTracks().forEach(function (track) {
        track.stop();
        context1.clearRect(0, 0,context1.width, context1.height);//Remove the canvas
    });
}

//Capture video
function drawMedia(){
    canvas1.setAttribute("width", video.videoWidth);
    canvas1.setAttribute("height", video.videoHeight);
    context1.drawImage(video, 0, 0, video.videoWidth, video.videoHeight);
}