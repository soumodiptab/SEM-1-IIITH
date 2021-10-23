var http = require('http');
var url = require('url');
var service = require('./service.js');
let port = 8080
//200 -status code
http.createServer(function (req, res) {
    res.writeHead(200, { 'Content-Type': 'application/json' });
    let params = url.parse(req.url, true).query;

    let query = params.query;
    if (query == 1) {
        let response = service.getHighestMarks();
        res.write(JSON.stringify(response));
    }
    else if (query == 2) {
        let i = params.index;
        let response = service.getSubject2Toppers(i);
        res.write(JSON.stringify(response));
    }
    else {
        res.write("Invalid query");
    }
    return res.end();
}).listen(port, () => {
    console.log("Server is now listening on port " + port);
});