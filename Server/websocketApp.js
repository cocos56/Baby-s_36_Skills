var ws = require("nodejs-websocket")

console.log("creating server ...")

{
    let port = 56
    var server = ws.createServer(serverCallbackFunction).listen(port)
}

var connection

function serverCallbackFunction(conn)
{
    connection = conn

    //console.log("a new connection come", conn)
    console.log("a new connection come, it's key is", conn["key"])
    //console.log("Sever Connections", server.connections)
    console.log("Sever connections = ", server.connections.length)

    //when a connection has been created
    conn.on("text", connectOnTextCallbackFunction)

    //when a connection has been closed
    conn.on("close", connectOnCloseCallbackFunction)

    //when a connection meet error
    conn.on("error", connectOnErrorCallbackFunction)

    setTimeout(function(){
        conn.sendText("success");
    }, 3000)
}

function connectOnTextCallbackFunction(str)
{
    console.log("get message:"+str)
    connection.sendText('Hello, I am Node.js')
}

function connectOnCloseCallbackFunction(code, reason)
{
    //console.log("a connection close", conn)
    //console.log("Sever Connections", server.connections)
    console.log("a connection close", code, reason)
    console.log("Sever connections = ", server.connections.length)
}

function connectOnErrorCallbackFunction(code, reason)
{
    console.log("a connection on error:", code , reason)
    console.log("Sever connections = ", server.connections.length)
}

console.log("the server of websocket has been created successfully.")