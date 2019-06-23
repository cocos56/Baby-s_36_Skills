exports.callback = function joinRoomCallback(msg, conn, room)
{
    let msgBack = {"event": 6}
    let nm = msg["nm"]
    let pw = msg["pw"]
    if(nm == ''){ msgBack['status'] = 620 }
    else if(nm != room['nm']){msgBack['status'] = 630}
    else if(pw != room['pw']){msgBack['status'] = 640}
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{ joinRoom(conn, msgBack, room) }
}

function joinRoom(conn, msgBack, room)
{
    msgBack['status'] = 641
    conn.send(JSON.stringify(msgBack))
    console.log(room)
}