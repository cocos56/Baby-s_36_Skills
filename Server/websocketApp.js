var ws = require("nodejs-websocket")

var signUp = require("./signUp")
var signIn = require("./signIn")


console.log("creating server ...")

{
    let port = 56
    var server = ws.createServer(serverCallbackFunction).listen(port)
}

function serverCallbackFunction(conn)
{
    console.log("a new connection come, it's key is", conn["key"])
    console.log("Sever connections = ", server.connections.length)

    //when a new message has been received.
    conn.on("text", function(str){ onMesage(str, conn) })

    //when a connection has been closed.
    conn.on("close", function(code, reason){ onClose(code, reason) })

    //when a connection meet error.
    conn.on("error", function(code, reason){ onError(code, reason, conn) })
}

function onMesage(msg, conn)
{
    msg = JSON.parse(msg)
    console.log("收到信息：", msg)
    if(2 == msg["event"]){signIn.callback(msg, conn)}
    else if(3 == msg["event"]){signUp.callback(msg, conn)}
}

function onClose(code, reason, conn)
{
    console.log("a connection close", code, reason)
    console.log("Sever connections = ", server.connections.length)
}

function onError(code, reason, conn)
{
    console.log("a connection on error:", code , reason)
    console.log("Sever connections = ", server.connections.length)
}

console.log("the server of websocket has been created successfully.")