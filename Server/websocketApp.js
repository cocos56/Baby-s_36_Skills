console.log("正在创建服务器")

var ws = require("nodejs-websocket")
var signUp = require("./signUp")
var signIn = require("./signIn")
var createRoom = require("./createRoom")
var getRooms = require("./getRooms")
var joinRoom = require("./joinRoom")
var selectRole = require("./selectRole")
var waiting = require("./waiting")
var dialog = require("./dialog")


{
    let port = 56
    var server = ws.createServer(function(conn){
        serverCallbackFunction(conn)
    }).listen(port)
}

function serverCallbackFunction(conn)
{
    console.log("A connection come")
    console.log("Sever connections = ", server.connections.length)
    //when a new message has been received.
    conn.on("text", function(str){ onMesage(str, conn) })

    //when a connection has been closed.
    conn.on("close", function(code, reason){ onClose(conn, code, reason) })

    //when a connection meet error.
    conn.on("error", function(code, reason){ onError(code, reason) })
}

var room = {}

function onMesage(msg, conn)
{
    msg = JSON.parse(msg)
    console.log("收到信息：", msg)
    if(2 == msg["event"]){signIn.callback(msg, conn)}
    else if(3 == msg["event"]){signUp.callback(msg, conn)}
    else if(4 == msg["event"]){getRooms.callback(conn, room)}
    else if(5 == msg["event"]){createRoom.callback(msg, conn, room)}
    else if(6 == msg["event"]){joinRoom.callback(msg, conn, room)}
    else if(7 == msg["event"]){selectRole.callback(msg, conn, room)}
    else if(8 == msg["event"]){waiting.callback(msg, conn, room)}
    else if(9 == msg["event"]){dialog.callback(msg, conn, room)}
    console.log("room：", room)
}

function onClose(conn, code, reason)
{
    waiting.closeCB(conn, room)
    console.log("a connection close", code, reason)
    console.log("Sever connections = ", server.connections.length)
}

function onError(code, reason)
{
    console.log("a connection on error:", code , reason)
    console.log("Sever connections = ", server.connections.length)
}

console.log("创建服务器完毕")