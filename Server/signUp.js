var db = require("./db")

// db.t('accounts')
// db.t('players')
// db.t('rooms')

exports.callback = function signUpCallback(msg, conn)
{
    let msgBack = {"event": 3}
    let un = msg["un"]
    let nn = msg["nn"]
    let pw = msg["pw"]
    if(un == ''){ msgBack['status'] = 320 }
    else if(!isNaN(un)){ msgBack['status'] = 330}
    else if(nn == ''){ msgBack['status'] = 340}
    else if(pw == ''){ msgBack['status'] = 350}
    else{ signUp(conn, un, nn, pw, msgBack) }
    if('status' in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function signUp(conn, un, nn, pw, msgBack)
{
    db.q("SELECT * FROM accounts where `username` = '" + escape(un) +  "' OR  + nickname = '" + escape(nn) + "'"
    , function(data){
        console.log(data.length, data)
        if(data.length==0){ insertSignUpData(conn, un, nn, pw, msgBack) }
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

function insertSignUpData(conn, un, nn, pw, msgBack)
{
    let key = conn["key"]
    db.q("INSERT INTO accounts VALUES (0, '" + escape(un) + "', '" + escape(nn) + "', '" + escape(pw) + "', '" + key +  "', 'Y')"
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