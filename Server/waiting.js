function sendMsg(conn, room, msgBack){
    if('childWS' in room){
        console.log("childWS", msgBack)
        room['childWS'].send(JSON.stringify(msgBack)) 
    }
    if('scoundrelWS' in room){
        console.log("scoundrelWS")
        room['scoundrelWS'].send(JSON.stringify(msgBack))
    }
    if('refereeWS' in room){
        console.log("refereeWS")
        room['refereeWS'].send(JSON.stringify(msgBack))
    }
}

exports.sendMsg = sendMsg

function waitingCloseCallback(conn, room)
{
    if('turn' in room){ room['turn'] = 0 }
    let msgBack = {"event": 8}
    if('childWS' in room && room['childWS'] == conn){
        msgBack['status'] = 820
        delete room['childWS']
        delete room['child']
    }
    else if('scoundrelWS' in room && room['scoundrelWS'] == conn){
        msgBack['status'] = 830
        delete room['scoundrelWS']
        delete room['scoundrel']
    }
    else if('refereeWS' in room && room['refereeWS'] == conn){
        msgBack['status'] = 840
        delete room['refereeWS']
        delete room['referee']
    }
    sendMsg(conn, room, msgBack)
}

exports.closeCB = waitingCloseCallback

exports.callback = function selectRoleCallback(msg, conn, room)
{
    if('quit' in msg){
        waitingCloseCallback(conn, room)
        return
    }

    let msgBack = {"event": 8}
    if('child' in room){
        msgBack['status'] = 821
        sendMsg(conn, room, msgBack)
    }
    if('scoundrel' in room){
        msgBack['status'] = 831
        sendMsg(conn, room, msgBack)
    }
    if('referee' in room){
        msgBack['status'] = 841
        sendMsg(conn, room, msgBack)
    }
}