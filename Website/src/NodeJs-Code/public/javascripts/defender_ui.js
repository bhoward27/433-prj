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

	$('#panLeft').click(function(){
		sendCommandViaUDP("panLeft");
	});

	$('#panRight').click(function(){
		sendCommandViaUDP("panRight");
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

	socket.on('stopPanning', function(result) {
		alert("You have gone the maximum distance left or right");
	});

	socket.on('addAlert', function(result) {
		var newDiv = $('<code></code>')
			.text(result)
			.wrapInner("<div></div>");
		$('#messages').append(newDiv);
		$('#messages').scrollTop($('#messages').prop('scrollHeight'));
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
		var resultSplitSpace = result.split(' ');
		$('#water-level').text("~"+ resultSplitSpace[1] + " cm");
		$('#temperature').text(resultSplitSpace[2] + " °C");
		$('#alarm-level').text(resultSplitSpace[3]);
	});

	socket.on('alarmReply', function(result) {
		flag = false;
		result = result.split(' ');
		$('#alarm-level').text(result[1]);
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
	sendCommandViaUDP("alarm")
}, 1000);