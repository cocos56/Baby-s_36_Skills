exports.callback = function selectRoleCallback(msg, conn, room)
{
    let msgBack = {"event": 7}
    let type = msg["type"]
    if(type == 1)
    {
        if('child' in room){msgBack['status'] = 720}
    }
    else if(type == 2)
    {
        if('scoundrel' in room){msgBack['status'] = 720}
    }
    else if(type == 3)
    {
        if('referee' in room){msgBack['status'] = 720}
    }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{}
}

function selectRole(conn, type, name, msgBack, room)
{
    room["nm"] = nm
    room["creator"] = creator
    room["pw"] = pw
    msgBack['status'] = 531
    conn.send(JSON.stringify(msgBack))
    console.log(room)
}