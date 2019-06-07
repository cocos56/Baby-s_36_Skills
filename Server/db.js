const mysql = require('mysql')

var db = mysql.createConnection({host:'localhost', user: 'root', password: '123123', database: 'baby\'s 36 skills'})
//1.connect
function query(cmd)
{
    db.query(cmd, (err, data)=>{
        console.log(cmd)
        if(err){
            console.log("err")
        }else{
            console.log(data)
        }
    })
}

var id = '1'
id = '1 OR 1=1'
var cmd = 'SELECT * FROM account WHERE ID=' + id
query(cmd)

cmd = 'SELECT * FROM account WHERE ID=' + escape(id)
query(cmd)

db.end()
