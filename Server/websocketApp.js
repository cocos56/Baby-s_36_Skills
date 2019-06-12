var ws = require("nodejs-websocket")
var db = require("./db")


console.log("creating server ...")

{
    let port = 56
    var server = ws.createServer(serverCallbackFunction).listen(port)
}

function serverCallbackFunction(conn)
{
    console.log("a new connection come, it's key is", conn["key"])
    console.log("Sever connections = ", server.connections.length)

    //when a new message has been received.
    conn.on("text", function(str)
        {onMesage(str, conn)}
    )

    //when a connection has been closed.
    conn.on("close", onClose)

    //when a connection meet error.
    conn.on("error", onError)
}

function onMesage(msg, conn)
{
    msg = JSON.parse(msg)
    console.log("收到信息：")
    console.log(msg)
    if(3 == msg["消息类型"])
    {
        signUpCallback(msg, conn)
    }
}

function signUpCallback(msg, conn)
{
    let key = conn["key"]
    let msgBack = {"消息类型": "注册响应"}
    let un = msg["用户名"]
    let nn = msg["昵称"]
    let pw = msg["密码"]
    if(un == ''){ msgBack["消息"] = "用户名不能为空，请重填。" }
    else if(!isNaN(un)){ msgBack["消息"] = "用户名不能全是数字，请重填。" }
    else if(nn == ''){ msgBack["消息"] = "昵称不能为空，请重填。" }
    else if(pw == ''){ msgBack["消息"] = "密码不能为空，请重填。" }
    else{ signUp(un, nn, pw, key, msgBack) }
    conn.send(JSON.stringify(msgBack))
}

function signUp(un, nn, pw, key, msgBack)
{
    db.q("SELECT * FROM accounts where `username` = '" + escape(un) +  "' OR `nickname` = '" + escape(nn) + "'"
    , function(data){
        console.log(data.length, data)
        if(data.length==0){
            db.q("INSERT INTO accounts VALUES (0, '" + escape(un) + "', '" + escape(nn) + "', '" + escape(pw) + "', '" + key +  "', 'Y')"
            , function(){msgBack["消息"] = "恭喜您注册成功，请返回登录。"}
            ,function(){msgBack["消息"] = "遇到未知错误，请联系开发维护人员"})
        }
        else{ msgBack["消息"] = "请重填用户名或昵称，因为您的用户名或昵称已被其他人占用" }
    }
    , function(err){ msgBack["消息"] = "您输入的信息包含非法字符，请重填，检查是否包含英文空格和分号" }
    )
}

function onClose(code, reason)
{
    console.log("a connection close", code, reason)
    console.log("Sever connections = ", server.connections.length)
}

function onError(code, reason)
{
    console.log("a connection on error:", code , reason)
    console.log("Sever connections = ", server.connections.length)
}

console.log("the server of websocket has been created successfully.")