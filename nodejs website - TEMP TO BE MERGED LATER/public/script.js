const socket = io();
socket.on("connect", (socket) => {
    console.log("Connected to server");
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