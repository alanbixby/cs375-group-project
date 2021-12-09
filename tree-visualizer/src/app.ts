import express from 'express'
import http from 'http'
import fs from 'fs'
import path from 'path'

import { draw, getDSA } from './visualizer'

const app = require('express')();
const server = require('http').createServer(app);
const io = require('socket.io')(server);


app.get('*', function (req, res) {
  // Why use a proper view engine like EJS when you can just abuse template literals? I hate myself too.
  res.send(`
    <head>
      <title>CS 375 Data Structure Visualizer</title>
    </head>
    <body>
      <h1 id="name" style="margin:auto">CS 375 Data Structure Visualizer</h1>
      <img id="tree" src="${draw().toDataURL()}" style="display:block;margin-left:auto;margin-right:auto;width=90%">
      <script src="/socket.io/socket.io.js"></script>
      <script>
      const socket = io();
      socket.on('fileChanged', ({png, name}) => {
          document.getElementById("tree").src=png;
          document.getElementById("name").innerHtml=name;
      });
      </script>
    </body>
    `);
});

io.on('connection', () => { });
server.listen(3000, () => {
  console.log("Listening on http://localhost:3000");
});

fs.watchFile(path.join(__dirname, '../treeBuild.json'), { interval: 500 }, (curr, prev) => {
  io.emit('fileChanged', { png: draw().toDataURL(), name: getDSA() });
});