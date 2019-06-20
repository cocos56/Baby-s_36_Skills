exports.callback = function selectRoleCallback(msg, conn, room)
{
    let msgBack = {"event": 7}
    let type = msg["type"]

    if(type == 0){ msgBack['status'] = 720 }
    else if(type == 1){ if('child' in room){msgBack['status'] = 730} }
    else if(type == 2){ if('referee' in room){msgBack['status'] = 730} }
    else if(type == 3){ if('scoundrel' in room){msgBack['status'] = 730} }
    
    if(type == 1){ if('childWS' in room && room['childWS'] == conn){ msgBack['status'] = 731} }
    else if(type == 2){ if('refereeWS' in room && room['refereeWS'] == conn){ msgBack['status'] = 731} }
    else if(type == 3){ if('scoundrelWS' in room && room['scoundrelWS'] == conn){ msgBack['status'] = 731} }
    
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{
        let name = msg["un"]
        selectRole(conn, type, name, msgBack, room)
    }
}

function selectRole(conn, type, name, msgBack, room)
{
    if(type == 1){
        room['child'] = name
        room['childWS'] = conn
        msgBack['status'] = 731
    }
    else if(type == 2){
        room['referee'] = name
        room['refereeWS'] = conn
        msgBack['status'] = 731
    }
    else if(type == 3){
        room['scoundrel'] = name
        room['scoundrelWS'] = conn
        msgBack['status'] = 731
    }
    conn.send(JSON.stringify(msgBack))
}