var port = 80
var io = require('socket.io').listen(port)
console.log('Server on port ' + port.toString() + '.')
var idList = []

io.sockets.on('connection', function (socket){
    idList.push(socket.id)
    console.log(idList)
	//向客户端发送消息
    socket.send('Hello Cocos2d-x, I am Node.js')

	//注册客户端消息
    socket.on('message', function (data){
        console.log("msg:", data)
        for(var i=0; i<idList.length; i++){
            io.to(idList[i]).send(data)
            //io.to(idList[i]).emit('callClientEvent', { message: data })
        }
    })
	
	//注册callServerEvent事件，便于客户端调用
    socket.on('callServerEvent', function (data){
        console.log(data)
		//向客户端发送消息，调用客户端的callClientEvent事件
        socket.emit('callClientEvent', { message: 'Hello Client.' })
        //socket.emit('callClientEvent', { message: 'Hello Client.' })
        //socket.emit('callClientEvent', { message: 'Hello Client.' })
    })

    //断开事件
    socket.on('disconnect', function(data) {
        console.log('断开',data)
        idList.splice(idList.indexOf(socket.id), 1)
        console.log(idList)
    })
})