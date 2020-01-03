exports.callback = function getRoomsCallback(conn, room)
{
    let msgBack = {"event": 4}
    if('nm' in room){msgBack['nm'] = room["nm"]
        msgBack['creator'] = room["creator"]
        msgBack['status'] = 411
    }
    else{ msgBack['status'] = 420 }
    conn.send(JSON.stringify(msgBack))
}