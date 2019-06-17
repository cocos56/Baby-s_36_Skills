var db = require("./db")

exports.callback = function createRoomCallback(msg, conn, room)
{
    let msgBack = {"event": 5}
    let nm = msg["nm"]
    let pw = msg["pw"]
    if(nm == ''){ msgBack['status'] = 520 }
    else{ createRoom(conn, nm, pw, msgBack, room) }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function createRoom(conn, nm, pw, msgBack, room)
{
    room['id'] = 1
    room["nm"] = nm
    room["creater"] = "2"
    room["pw"] = pw
    console.log(room)
    
    //insertCreateRoomData(conn, nm, pw, msgBack)
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