exports.callback = function createRoomCallback(msg, conn, room)
{
    let msgBack = {"event": 5}
    let nm = msg["nm"]
    let pw = msg["pw"]
    let creator = msg["creator"]
    if(nm == ''){ msgBack['status'] = 520 }
    else if("creator" in room) {msgBack['status'] = 530}
    else{ createRoom(conn, nm, pw, creator, msgBack, room) }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function createRoom(conn, nm, pw, creator, msgBack, room)
{
    room["nm"] = nm
    room["creator"] = creator
    room["pw"] = pw
    msgBack['status'] = 531
    conn.send(JSON.stringify(msgBack))
    console.log(room)
}