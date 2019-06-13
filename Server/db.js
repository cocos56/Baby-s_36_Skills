const mysql = require('mysql')

console.log("连接数据库")

var db = mysql.createConnection({host:'localhost', user: 'root', password: '123123', database: 'baby\'s 36 skills'})

//1.connect
exports.q = function(cmd, callback, errcallback)
{
    data = db.query(cmd, function(err, data)
    {
        console.log(cmd)
        if(err)
        {
            console.log("err", err)
            errcallback(err)
            //return false
        }
        else
        {
            //console.log(data)
            callback(data)
        }
    })
}

// var id = '1'
// id = '1 OR 1=1'
// var cmd = 'SELECT * FROM account WHERE ID=' + id
// 查询(cmd)
// cmd = 'SELECT * FROM account WHERE ID=' + escape(id)
// 查询(cmd)

//db.end()
console.log("关闭数据库")