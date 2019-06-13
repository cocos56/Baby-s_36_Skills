var db = require("./db")

exports.callback = function signUpCallback(msg, conn)
{
    let key = conn["key"]
    let msgBack = {"msgT": 3}
    let un = msg["un"]
    let nn = msg["nn"]
    let pw = msg["pw"]
    if(un == ''){ msgBack["msg"] = 320 }
    else if(!isNaN(un)){ msgBack["msg"] = 330}
    else if(nn == ''){ msgBack["msg"] = 340}
    else if(pw == ''){ msgBack["msg"] = 350}
    else{ signUp(conn, un, nn, pw, key, msgBack) }
    if("msg" in msgBack){conn.send(JSON.stringify(msgBack))}
    
}

function signUp(conn, un, nn, pw, key, msgBack)
{
    db.q("SELECT * FROM accounts where `username` = '" + escape(un) +  "' OR  + nickname = '" + escape(nn) + "'"
    , function(data){
        console.log(data.length, data)
        if(data.length==0){ insertSignUpData(conn, un, nn, pw, key, msgBack) }
        else{
            msgBack["msg"] = 360
            conn.send(JSON.stringify(msgBack))
        }
    }
    , function(err){
        console.log(err)
         msgBack["msg"] = 370
         conn.send(JSON.stringify(msgBack))
    }
    )
}

function insertSignUpData(conn, un, nn, pw, key, msgBack)
{
    db.q("INSERT INTO accounts VALUES (0, '" + escape(un) + "', '" + escape(nn) + "', '" + escape(pw) + "', '" + key +  "', 'Y')"
    , function(){
        msgBack["msg"] = 381
        conn.send(JSON.stringify(msgBack))
    }
    ,function(){
        msgBack["msg"] = 380
        conn.send(JSON.stringify(msgBack))
    }
    )
}