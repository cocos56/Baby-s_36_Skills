var db = require("./db")

exports.callback = function createRoomCallback(msg, conn)
{
    let msgBack = {"event": 5}
    let nm = msg["nm"]
    let pw = msg["pw"]
    if(nm == ''){ msgBack['status'] = 520 }
    else{ createRoom(conn, nm, pw, msgBack) }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function createRoom(conn, nm, pw, msgBack)
{
    let key = conn["key"]
    
    insertCreateRoomData(conn, nm, pw, msgBack)
}

function insertCreateRoomData(conn, nm, pw, msgBack)
{
    db.q("INSERT INTO `rooms`(`name`, `password`) VALUES ('" + escape(nm) + "', '" + escape(pw) + "')"
    , function(){
        msgBack['status'] = 531
        conn.send(JSON.stringify(msgBack))
    }
    ,function(){
        msgBack['status'] = 530
        conn.send(JSON.stringify(msgBack))
    }
    )
}