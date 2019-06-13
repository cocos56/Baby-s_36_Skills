const http=require('http')
const querystring=require('querystring')
const urlLib=require('url')

var server=http.createServer(function (req, res){
  //GET
  var obj=urlLib.parse(req.url, true);

  var url=obj.pathname;
  const GET=obj.query;

  //POST
  var str='';
  req.on('data', function (data){
    str+=data;
  });
  req.on('end', function (){
      console.log(str)
      res.write('h')
      res.end()
  });
});

server.listen(8080);
