var db = require("./db")

exports.callback = function signUpCallback(msg, conn)
{
    let msgBack = {"event": 2}
    let un = msg["un"]
    let pw = msg["pw"]
    if(un == ''){ msgBack['status'] = 220 }
    else if(pw == ''){ msgBack['status'] = 230}
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{ signIn(conn, un, pw, msgBack) }
}

function signIn(conn, un, pw, msgBack)
{
    db.q("SELECT `password` FROM accounts where `username` = '" + escape(un) + "'"
    , function(data){
        if(data.length==1){
            if(data[0]['password'] == pw){msgBack['status'] = 271}
            else{msgBack['status'] = 270}
            conn.send(JSON.stringify(msgBack))
        }
        else{
            if(data.length==0){ msgBack['status'] = 240 }
            else{msgBack['status'] = 250}
            conn.send(JSON.stringify(msgBack))
        }
    }
    , function(err){
        msgBack['status'] = 260
        conn.send(JSON.stringify(msgBack))
    })
}