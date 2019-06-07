var ws = require("nodejs-websocket")

console.log("开始建立连接...")

var server = ws.createServer(function(conn){
    //console.log("a New Connection", conn)
    //console.log("Sever Connections", server.connections)
    console.log("Sever Connections", server.connections.length)

    conn.on("text", function (str) {
        //
        console.log("收到的信息为:"+str)
        conn.sendText('Hello, I am Node.js')
    })

    conn.on("close", function (code, reason) {
        console.log("关闭连接")
    });

    conn.on("error", function (code, reason) {
        console.log("异常关闭")
    })

    setTimeout(function(){
        conn.sendText("success");
    }, 3000)

}).listen(56)

console.log("WebSocket建立完毕")