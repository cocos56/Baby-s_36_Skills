var WebSocketServer = require('ws').Server,
wss = new WebSocketServer({ port: 56 })

wsDic = {}

wss.on('connection', function (ws) {
    wsDic[ws] = 1
    console.log('client connected', wsDic);
    
    ws.on('message', function (message) {
        console.log(message);
    });
});