import express from 'express'
import http from 'http'
import fs from 'fs'

import draw from './graph'

const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);


app.get('*', function (req, res) {
  res.send(`
    <head>
      <title>Binary Tree Visualizer</title>
    </head>
    <body>
      <h1 style="margin:auto">Binary Tree Visualizer</h1>
      <img id="tree" src="${draw().toDataURL()}" style="display:block;margin-left:auto;margin-right:auto">
      <script src="/socket.io/socket.io.js"></script>
      <script>
      const socket = io();
      socket.on('fileChanged', (png) => {
          document.getElementById("tree").src=png;
      });
      </script>
    </body>
    `);
});

io.on('connection', () => {});
server.listen(3000);

fs.watchFile('src/treeBuild.json', { interval: 500 }, (curr, prev) => {
  io.emit('fileChanged', draw().toDataURL());
});