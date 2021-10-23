var fs = require('fs');

fs.writeFile('output.txt', 'SSD is best!', function (err) {
  if (err) throw err;
  console.log('Saved!');
});