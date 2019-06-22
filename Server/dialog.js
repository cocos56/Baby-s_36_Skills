var waiting = require("./waiting")

exports.callback = function selectRoleCallback(msg, conn, room)
{
    let msgBack = {"event": 9}
    if('result' in msg && 'refereeWS' in room && room['refereeWS'] == conn){
        msgBack['result'] = msg['result']
        msgBack['status'] = 951
        waiting.sendMsg(conn, room, msgBack)
        return
    }
    if('turn' in room){
        if('msg' in msg){
            msgBack['msg'] = msg['msg']
            transpond(conn, room, msgBack)
            return
         }
        else if('end' in msg){ room['turn'] = (room['turn'] + 1) % 3 }
    }
    else{ room['turn'] = 0 }
    if(room['turn'] == 0){ msgBack['status'] = 921 }
    else if(room['turn'] == 1){ msgBack['status'] = 931 }
    else if(room['turn'] == 2){ msgBack['status'] = 941 }
    waiting.sendMsg(conn, room, msgBack)
}

function transpond(conn, room, msgBack)
{
    if(room['turn'] == 0){ msgBack['status'] = 961 }
    else if(room['turn'] == 1){ msgBack['status'] = 971 }
    else if(room['turn'] == 2){ msgBack['status'] = 981 }
    waiting.sendMsg(conn, room, msgBack)

}