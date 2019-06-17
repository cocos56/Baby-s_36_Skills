exports.callback = function joinRoomCallback(msg, conn, room)
{
    let msgBack = {"event": 6}
    let nm = msg["nm"]
    let pw = msg["pw"]
    if(nm == ''){ msgBack['status'] = 620 }
    else if(pw != room['pw']){msgBack['status'] = 630}
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{ joinRoom(conn, nm, pw, msgBack, room) }
    
    
}

function joinRoom(conn, nm, pw, msgBack, room)
{
    room["nm"] = nm
    room["pw"] = pw
    msgBack['status'] = 631
    conn.send(JSON.stringify(msgBack))
    console.log(room)
}