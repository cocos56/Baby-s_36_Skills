exports.callback = function joinRoomCallback(msg, conn, room)
{
    let msgBack = {"event": 6}
    let nm = msg["nm"]
    let pw = msg["pw"]
    if(nm == ''){ msgBack['status'] = 620 }
    else{ joinRoom(conn, nm, pw, creator, msgBack, room) }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function joinRoom(conn, nm, pw, creator, msgBack, room)
{
    room["nm"] = nm
    room["creator"] = creator
    room["pw"] = pw
    msgBack['status'] = 531
    conn.send(JSON.stringify(msgBack))
    console.log(room)
}