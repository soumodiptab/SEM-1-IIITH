
function matchStrings(str, regex){
    let matches = str.matchAll(regex)
    for (const match of matches){
        console.log(match)
    }
}

let testRegex = new RegExp("ba+b", "gi")

let testString = "Baaaaaaaaaaaaabaabaaaaaaaabdsdasdabadaab";


matchStrings(testString, testRegex)


let testRegex2 = new RegExp("([0-9]+)x([0-9]+)", "gi")
let testString2 = "4K corresponds to 3840x2160"

matchStrings(testString2, testRegex2)

let testRegex3 = new RegExp("^[aeiou]", "g")
let testString3 = "A wonderful evening"

matchStrings(testString3, testRegex3)


let dateRegex = new RegExp("^(0?[1-9]|[12][0-9]|3[01])[\/\-](0?[1-9]|1[012])[\/\-]\\d{4}$", "g")
let testDate = "01/01/1997"
matchStrings(testDate, dateRegex)

