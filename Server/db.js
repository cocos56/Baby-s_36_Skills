const mysql = require('mysql')

console.log("\n正在初始化连接数据库")

var db = mysql.createConnection({host:'localhost', user: 'root', password: '123123', database: 'baby\'s 36 skills'})

exports.q = function q(cmd, callback, errcallback)
{
    data = db.query(cmd, function(err, data)
    {
        //console.log("cmd:",cmd)
        if(err)
        {
            console.log("err:", err)
            errcallback(err)
        }
        else
        {
            //console.log("data", data)
            callback(data)
        }
    })
}


exports.t = function truncateTable(tableName)
{
    q('TRUNCATE TABLE ' + tableName
    ,function(data){console.log('已清空' + tableName + '表')}
    , function(err){})
}

// var id = '1'
// id = '1 OR 1=1'
// var cmd = 'SELECT * FROM account WHERE ID=' + id
// cmd = 'SELECT * FROM account WHERE ID=' + escape(id)
//db.end()
console.log("初始化连接数据库完毕\n")