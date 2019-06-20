function sendMsg(conn, room, msgBack){
    if('childWS' in room && room['childWS'] != conn){ room['childWS'].send(JSON.stringify(msgBack)) }
    if('scoundrelWS' in room && room['scoundrelWS'] != conn){ room['scoundrelWS'].send(JSON.stringify(msgBack)) }
    if('refereeWS' in room && room['refereeWS'] != conn){ room['refereeWS'].send(JSON.stringify(msgBack)) }
}

exports.closeCB = function waitingCloseCallback(conn, room)
{
    let msgBack = {"event": 8}
    if('childWS' in room && room['childWS'] == conn){
        msgBack['status'] = 820
        delete room['childWS']
    }
    else if('scoundrelWS' in room && room['scoundrelWS'] == conn){
        delete room['scoundrelWS']
        msgBack['status'] = 830
    }
    else if('refereeWS' in room && room['refereeWS'] == conn){
        delete room['refereeWS']
        msgBack['status'] = 840
    }
    sendMsg(room, msgBack)
}

exports.callback = function selectRoleCallback(msg, conn, room)
{
    if('quit' in msg){
        waitingCloseCallback(conn, room)
        return
    }

    let msgBack = {"event": 8}
    if('child' in room){
        msgBack['status'] = 821
        sendMsg(room, msgBack)
    }
    if('scoundrel' in room){
        msgBack['status'] = 831
        sendMsg(room, msgBack)
    }
    if('referee' in room){
        msgBack['status'] = 841
        sendMsg(conn, room, msgBack)
    }
}