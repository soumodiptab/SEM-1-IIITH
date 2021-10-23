var fs = require('fs');
var students;

fs.readFile('./data.json', "utf-8", function (err, data) {
    students = JSON.parse(data);
});

exports.getStudents = function () {
    return students;
}
exports.getHighestMarks = function () {
    let max = 0;
    let highest_name;
    for (let name in students) {
        let marks = students[name];
        let sum = 0;
        for (let m of marks) {
            sum = sum + m;
        }
        if (max < sum) {
            highest_name = name;
            max = sum;
        }
    }
    return highest_name;
}
exports.getSubject2Toppers = function (index) {
    let studentlist = [];
    let index_count = Object.keys(students);
    if (index < -1 || index >= index_count)
        return studentlist;
    for (let student in students) {
        let record = [
            student,
            students[student][index]
        ];
        studentlist.push(record);
    }
    studentlist = studentlist.sort((x, y) => x[1] - y[1]);
    return studentlist;
}