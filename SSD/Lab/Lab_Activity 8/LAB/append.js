var fs = require('fs');
fs.appendFile('output.txt', ' This is my LAB.', function (err) {
  if (err) throw err;
  console.log('Updated!');
});