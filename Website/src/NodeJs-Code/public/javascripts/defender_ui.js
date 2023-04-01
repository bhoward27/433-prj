// Based off code provided by Dr. Fraser
"use strict";
// Client-side interactions with the browser.

// Make connection to server when web page is fully loaded.
var socket = io.connect();

$(document).ready(function() {

	$('#test').click(function(){
		sendCommandViaUDP("test");
	});

	$('#terminate').click(function(){
		sendCommandViaUDP("terminate");
	});

	socket.on('bbgNotRunning', function(result) {
		if ($('#error-box').is(":hidden")) {
			var newDiv = $('<code></code>')
				.text(result)
				.wrapInner("<div></div>");
			$('#error-box').show();
			$('#error-text').html(newDiv);
		}
	});

	socket.on('bbgRunning', function(result) {
		if ($('#error-box').is(":visible")) {
			$('#error-box').hide();
		}
	});
});

$(document).ready(function () {
    socket.on("canvas", function (data) {
        const canvas = $("#videostream");
        const ctx = canvas[0].getContext("2d");
        const img = new Image();
        img.src = "data:image/jpeg;base64," + data;
        img.onload = function () {
            ctx.height = img.height;
            ctx.width = img.width;
            ctx.drawImage(img, 0, 0, img.width, img.height);
        };
    });
});

function sendCommandViaUDP(message) {
	socket.emit('daUdpCommand', message);

	var flag = true;
	socket.on('commandReply', function(result) {
		flag = false;
	});
	socket.on('updateReply', function(result) {
		flag = false;
		result = result.split(' ');
		$('#water-level').text(result[1]);
	});

	setTimeout(function () {
		if (flag) {
			// Learned how to check if div is visible from this link: https://stackoverflow.com/questions/178325/how-do-i-check-if-an-element-is-hidden-in-jquery
			if ($('#error-box').is(":hidden")) {
				var newDiv = $('<code></code>')
				.text("NodeJs server is no longer responding, please check that it is running")
				.wrapInner("<div></div>");
				$('#error-box').show();
				$('#error-text').html(newDiv);
			}
		}
	}, 2000);
};

// Learned how to send a command every second from the link below
// https://stackoverflow.com/questions/45752698/periodically-call-node-js-function-every-second
setInterval(function() {
	sendCommandViaUDP("update")
}, 1000);