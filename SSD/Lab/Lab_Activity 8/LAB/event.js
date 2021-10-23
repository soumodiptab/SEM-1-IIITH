var fs = require('fs');
var rs = fs.createReadStream('./logging.txt');

// Events

rs.on('open', function () {
  console.log('The file is open');
});


rs.on('close', function () {
  console.log("The file is now closed");
});


rs.close()