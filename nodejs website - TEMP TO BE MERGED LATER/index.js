const express = require('express');
const app = express();
const http = require('http');
const server = http.createServer(app);
const { Server } = require("socket.io");
const io = new Server(server);
const startRouter = require('./routers/page.js');
const {SERVER_PORT: port = 3000} = process.env;
const child = require('child_process');

app.use("/", startRouter);

io.on('connection', (socket) => {
    console.log('a user connected');

    let ffmpeg = child.spawn('ffmpeg', [
        "-re",
        "-y",
        "-i",
        "udp://192.168.7.1:1234",
        "-preset",
        "ultrafast",
        "-f",
        "mjpeg",
        "pipe:1"
    ]);

    ffmpeg.on('error', (err) => {
        console.log(err);
        throw err;
    });

    ffmpeg.on('close', (code) => {
        console.log(`ffmpeg exited with code ` + code);
    });

    ffmpeg.stderr.on('data', (data) => {

    });

    ffmpeg.stdout.on('data', (data) => {
        var frame = Buffer.from(data).toString('base64');
        io.sockets.emit('canvas', frame);
    });
});

server.listen(port, () => {
    console.log(`listening on *:${port}`);
});
