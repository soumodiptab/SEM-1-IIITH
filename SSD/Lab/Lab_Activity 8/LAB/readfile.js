var http = require('http');
var fs = require('fs');


let port = 8080

http.createServer(function (req, res) {
  fs.readFile('reader.html', function(err, data) {
    res.writeHead(200, {'Content-Type': 'text/html'});
    res.write(data);
    return res.end();
  });
}).listen(port, () => {
  console.log(`Server is now lisning on port ${port}`)
});