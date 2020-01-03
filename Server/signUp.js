var db = require("./db")

// db.t('accounts')
// db.t('players')
// db.t('rooms')

exports.callback = function signUpCallback(msg, conn)
{
    let msgBack = {"event": 3}
    let un = msg["un"]
    let pw = msg["pw"]
    if(un == ''){ msgBack['status'] = 320 }
    else if(pw == ''){ msgBack['status'] = 350}
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    else{ signUp(conn, un, pw, msgBack) }
}

function signUp(conn, un, pw, msgBack)
{
    db.q("SELECT * FROM accounts where `username` = '" + escape(un) + "'"
    , function(data){
        console.log(data.length, data)
        if(data.length==0){ insertSignUpData(conn, un, pw, msgBack) }
        else{
            msgBack['status'] = 360
            conn.send(JSON.stringify(msgBack))
        }
    }
    , function(err){
        console.log(err)
         msgBack['status'] = 370
         conn.send(JSON.stringify(msgBack))
    })
}

function insertSignUpData(conn, un, pw, msgBack)
{
    db.q("INSERT INTO accounts VALUES ('" + escape(un) + "', '" + escape(pw) + "')"
    , function(){
        msgBack['status'] = 381
        conn.send(JSON.stringify(msgBack))
    }
    ,function(){
        msgBack['status'] = 380
        conn.send(JSON.stringify(msgBack))
    }
    )
}